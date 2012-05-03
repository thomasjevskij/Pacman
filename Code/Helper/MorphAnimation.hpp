#ifndef MORPH_ANIMATION_HPP
#define MORPH_ANIMATION_HPP

#include <vector>
#include "Global.hpp"
#include "Camera.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"
#include "D3DResourceManager.hpp"

namespace Helper
{
	class MorphAnimation
	{
	public:
		MorphAnimation(ID3D10Device* device);

		void Update(float dt);
		void Draw(const Camera& camera, D3DXVECTOR3 position);
	private:
		Framework::VertexBuffer mBuf1;
		Framework::VertexBuffer mBuf2;
		Framework::Effect* mEffect;
		float mTime;
		float mTimeSpan;

		//DEBUG
		ID3D10Device* mDevice;
	};
}

#endif