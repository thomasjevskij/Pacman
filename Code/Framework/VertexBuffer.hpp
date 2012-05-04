#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "Global.hpp"
#include <vector>

namespace Framework
{
	// Determine what access will be given to the buffer from the CPU/GPU.
	// 
	// Default - GPU can read/write. CPU can not read or write.
	// Immutable - GPU can read. CPU can only write at creation time. CPU can not read.
	// CPURead - GPU can read, CPU can read.
	// CPUWrite - GPU can read, CPU can write.
	namespace Usage
	{
		enum Usage { Default, Immutable, CPURead, CPUWrite };
	}

	// Determine how to interpret the vertices as primitives.
	// 
	// PointList - Every vertex is rendered as a point.
	// LineStrip - A line is drawn between each consequtive vertex.
	// LineList - A line is drawn between every consequtive pair of vertices.
	// TriangleStrip - A triangle is drawn between a vertex and the last two vertices.
	// TriangleList - A triangle is drawn between every consequtive three vertices.
	namespace Topology
	{
		enum Topology { PointList, LineStrip, LineList, TriangleStrip, TriangleList };
	}

	// A vector for holding an index buffer
	typedef std::vector<unsigned int> IndexVector;

	// A class for holding vertex buffer data. To create a buffer, first call the constructor, then call
	// the SetData() method.
	class VertexBuffer
	{
	public:
		// A struct for defining the data inside a vertex buffer, and how it should be interpreted.
		struct Description
		{
			Description() : ElementSize(0), ElementCount(0), FirstElementPointer(NULL), Usage(Usage::Default) {}

			unsigned int ElementSize;
			unsigned int ElementCount;
			void* FirstElementPointer;
			Usage::Usage Usage;
			Topology::Topology Topology;
		};

		VertexBuffer(ID3D10Device* device);
		~VertexBuffer() throw();

		// Set the actual data of the buffer and decide how it should be interpreted
		bool SetData(const Description& description, IndexVector* indices);

		// Bind the buffer(s) to an input slot.
		void Bind(unsigned int slot = 0);

		// Draw the vertices in the buffer - an effect pass should have been applied 
		// before this one is called.
		// Should deprecate - move responsibility to context.
		void Draw();

	private:
		ID3D10Device* mDevice;
		ID3D10Buffer* mVertexBuffer;
		ID3D10Buffer* mIndexBuffer;
		Topology::Topology mTopology;
		unsigned int mElementSize;
		unsigned int mElementCount;
		unsigned int mIndexCount;

		bool SetupIndexBuffer(IndexVector* indices, Usage::Usage usage);
		bool CreateBuffer(ID3D10Buffer** buffer, const Description& description, UINT bindFlags);

		static void SetAccessAndUsageFlags(D3D10_BUFFER_DESC& description, Usage::Usage usage);
		static D3D10_PRIMITIVE_TOPOLOGY GetTopologyFlag(Topology::Topology topology);

		// Vertex buffers should not be copied. Immutable resource (at this point, since
		// no methods for modifying them are present).
		VertexBuffer(const VertexBuffer& copy);
		VertexBuffer& operator=(const VertexBuffer& copy);
	};
}

#endif

