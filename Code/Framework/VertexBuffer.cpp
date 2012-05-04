#include "VertexBuffer.hpp"
#include <cassert>

namespace Framework
{
	VertexBuffer::VertexBuffer(ID3D10Device* device) :
		mDevice(device), 
		mVertexBuffer(NULL),
		mIndexBuffer(NULL),
		mTopology(Topology::PointList),
		mElementSize(0),
		mElementCount(0),
		mIndexCount(0)
	{}

	VertexBuffer::~VertexBuffer() throw()
	{
		SafeRelease(mVertexBuffer);
		SafeRelease(mIndexBuffer);
	}

	bool VertexBuffer::SetData(const Description& description, IndexVector* indices)
	{
		// Release all old buffers
		SafeRelease(mVertexBuffer);
		SafeRelease(mIndexBuffer);
		mIndexCount = 0;

		// Setup index buffer
		if (indices != NULL)
		{
			if (!SetupIndexBuffer(indices, description.Usage))
			{
				MessageBox(NULL, "Failed to create index buffer", "Error", MB_OK | MB_ICONERROR);
				return false;
			}
		}

		// Setup vertex buffer
		if (!CreateBuffer(&mVertexBuffer, description, D3D10_BIND_VERTEX_BUFFER))
		{
			MessageBox(NULL, "Failed to create vertex buffer", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Set new buffer description
		mElementCount = description.ElementCount;
		mElementSize = description.ElementSize;
		mTopology = description.Topology;

		return true;
	}

	void VertexBuffer::Bind(unsigned int slot)
	{
		// Don't bind unless we've set the buffer data
		if (mVertexBuffer == NULL)
			return;

		// Bind the index buffer if it exists
		if (mIndexBuffer != NULL)
			mDevice->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
		// Bind the vertex buffer and set the topology state
		unsigned int offset = 0;
		mDevice->IASetVertexBuffers(slot, 1, &mVertexBuffer, &mElementSize, &offset);
		mDevice->IASetPrimitiveTopology(GetTopologyFlag(mTopology));
	}

	void VertexBuffer::Draw()
	{
		if (mIndexBuffer != NULL)
		{
			mDevice->DrawIndexed(mIndexCount, 0, 0);
		}
		else
		{
			mDevice->Draw(mElementCount, 0);
		}
	}

	bool VertexBuffer::SetupIndexBuffer(IndexVector* indices, Usage::Usage usage)
	{
		assert(!indices->empty());

		VertexBuffer::Description description;
		description.ElementCount = indices->size();
		description.ElementSize = sizeof(unsigned int);
		description.Usage = usage;
		description.FirstElementPointer = &(indices->front());

		if (!CreateBuffer(&mIndexBuffer, description, D3D10_BIND_INDEX_BUFFER))
			return false;

		mIndexCount = indices->size();

		return true;
	}

	bool VertexBuffer::CreateBuffer(ID3D10Buffer** buffer, const Description& description, UINT bindFlags)
	{
		D3D10_BUFFER_DESC d3dBufferDescription;
		d3dBufferDescription.BindFlags = bindFlags;
		d3dBufferDescription.ByteWidth = description.ElementSize * description.ElementCount;
		d3dBufferDescription.MiscFlags = 0;
		SetAccessAndUsageFlags(d3dBufferDescription, description.Usage);

		D3D10_SUBRESOURCE_DATA d3dData;
		d3dData.pSysMem = description.FirstElementPointer;
		d3dData.SysMemPitch = 0;
		d3dData.SysMemSlicePitch = 0;

		HRESULT result = mDevice->CreateBuffer(&d3dBufferDescription, &d3dData, buffer);
		if (FAILED(result))
			return false;
		return true;
	}

	void VertexBuffer::SetAccessAndUsageFlags(D3D10_BUFFER_DESC& description, Usage::Usage usage)
	{
		switch (usage)
		{
			case Usage::Immutable:
				description.Usage = D3D10_USAGE_IMMUTABLE;
				description.CPUAccessFlags = 0;
				break;
			case Usage::CPURead:
				description.Usage = D3D10_USAGE_DYNAMIC;
				description.CPUAccessFlags = D3D10_CPU_ACCESS_READ;
				break;
			case Usage::CPUWrite:
				description.Usage = D3D10_USAGE_STAGING;
				description.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
				break;
			case Usage::Default:
			default:
				description.Usage = D3D10_USAGE_DEFAULT;
				description.CPUAccessFlags = 0;
		}
	}

	D3D10_PRIMITIVE_TOPOLOGY VertexBuffer::GetTopologyFlag(Topology::Topology topology)
	{
		D3D10_PRIMITIVE_TOPOLOGY result;
		switch (topology)
		{
			case Topology::PointList:
				result = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case Topology::LineStrip:
				result = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
				break;
			case Topology::LineList:
				result = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case Topology::TriangleStrip:
				result = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				break;
			case Topology::TriangleList:
				result = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			default:
				result = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
		}

		return result;
	}
}

