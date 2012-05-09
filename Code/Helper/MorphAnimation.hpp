#ifndef MORPH_ANIMATION_HPP
#define MORPH_ANIMATION_HPP

#include <vector>
#include "Global.hpp"
#include "Camera.hpp"
#include "StaticModelData.hpp"
#include "Effect.hpp"
#include "D3DResourceManager.hpp"

namespace Helper
{
	class MorphAnimation
	{
	public:
		MorphAnimation(ID3D10Device* device, const std::vector<std::string>& keyFrameFilenames,
					   const std::vector<float> timeSpans);
		~MorphAnimation() throw();

		void Update(float dt);
		void Draw(const Camera& camera, D3DXMATRIX modelMatrix);
	private:
		struct AnimationVertex
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Normal;
			D3DXVECTOR2 UV;
		};
		struct KeyFrame
		{
			KeyFrame(Resources::StaticModelData* data, float timeSpan);

			Resources::StaticModelData* Data;
			float TimeSpan;
		};

		void HandleTime(float dt);
		

		std::vector<KeyFrame> mKeyFrames;

		Framework::Effect* mEffect;

		bool mLooping;
		bool mForwards;
		int mCurrentFrame;
		float mTime;

		//DEBUG
		ID3D10Device* mDevice;
	};
}

#endif