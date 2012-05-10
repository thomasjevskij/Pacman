#ifndef GROUND_HPP
#define GROUND_HPP

#include <vector>

#include "Level.hpp"
#include "ModelObj.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"
#include "Camera.hpp"

namespace View
{
	class Environment
	{
	public:
		static const int C_CELL_SIZE = 10;

		Environment(ID3D10Device* device, Model::Level level);
		~Environment() throw();

		void Draw(const Helper::Camera& camera);

	private:
		struct Vertex
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR2	UV;
		};

		ID3D10Device* mDevice;
		Framework::VertexBuffer* mBuffer;
		Framework::Effect* mEffect;
		std::vector<D3DXVECTOR3> mWallPositions;
		Resources::ModelObj mWallObject;

		Environment(const Environment&);
		Environment& operator=(const Environment&);

		void CreateGround(int width, int depth);
		void CreateWalls(const Model::Level& level);
	};
}
#endif