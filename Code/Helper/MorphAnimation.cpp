#include "MorphAnimation.hpp"
#include <cassert>

namespace Helper
{

	MorphAnimation::MorphAnimation(ID3D10Device* device, const std::vector<std::string>& keyFrameFilenames,
								   const std::vector<float> timeSpans)
		: mTime(0.0f)
		, mDevice(device)
		, mCurrentFrame(0)
		, mLooping(true)
		, mForwards(true)
	{
		//AnimationVertex frame1[] = {
		//	{D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)}
		//};
		//AnimationVertex frame2[] = {
		//	{D3DXVECTOR3(-10.0f, -1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(1.0f, -1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(1.0f, 1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
		//	{D3DXVECTOR3(-10.0f, 1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)}
		//};
		//Framework::VertexBuffer::Description desc;
		//desc.ElementCount = 4;
		//desc.ElementSize = sizeof(AnimationVertex);
		//desc.FirstElementPointer = frame1;
		//desc.Topology = Framework::Topology::TriangleStrip;
		//desc.Usage = Framework::Usage::Default;

		////desc.
		//Framework::VertexBuffer* buf = new Framework::VertexBuffer(mDevice);
		//buf->SetData(desc, NULL);
		//mKeyFrames.push_back(KeyFrame(buf, 5.0f));
		//desc.FirstElementPointer = frame2;
		//buf = new Framework::VertexBuffer(mDevice);
		//buf->SetData(desc, NULL);
		//mKeyFrames.push_back(KeyFrame(buf, -1.0f));

		assert(keyFrameFilenames.size() == timeSpans.size());
		for (int i = 0; i < keyFrameFilenames.size(); ++i)
		{
			//mKeyFrames.push_back(KeyFrame(Resources::ModelResourceManager::Instance().Load(keyFrameFilenames[i]), timeSpans[i]));
			mKeyFrames.push_back(
				KeyFrame(Resources::D3DResourceManager<Resources::StaticModelData>::Instance().Load(keyFrameFilenames[i])
				, timeSpans[i]));
		}

		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Animation.fx");
		Framework::InputLayoutVector vec;
		vec.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 0, 0));
		vec.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT, 0, 0));
		vec.push_back(Framework::InputLayoutElement("UV", DXGI_FORMAT_R32G32_FLOAT, 0, 0));
		vec.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 1, 1));
		vec.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT, 1, 1));
		vec.push_back(Framework::InputLayoutElement("UV", DXGI_FORMAT_R32G32_FLOAT, 1, 1));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(vec);
		mEffect->SetVariable("g_t", 0.0f);
		mEffect->SetVariable("g_modelTexture", mKeyFrames[0].Data->MaterialData->GetMaterial(mKeyFrames[0].Data->MaterialName)->MainTexture->GetShaderResoureceView());
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(50, 50, 0, 0));
	}

	MorphAnimation::KeyFrame::KeyFrame(Resources::StaticModelData* data, float timeSpan)
		: Data(data), TimeSpan(timeSpan)
	{}

	MorphAnimation::~MorphAnimation() throw()
	{}

	void MorphAnimation::Update(float dt)
	{
		/*mTime += dt;
		if (mTime > mKeyFrames[mCurrentFrame].TimeSpan)
		{
			if (mCurrentFrame < mKeyFrames.size() - 2)
			{
				mCurrentFrame++;
				mTime = 0.0f;
			}
			else
				mTime = mKeyFrames[mCurrentFrame].TimeSpan;
		}*/
		HandleTime(dt);

		mEffect->SetVariable("g_t", mTime / mKeyFrames[mCurrentFrame].TimeSpan);
	}

	void MorphAnimation::Draw(const Camera& camera, D3DXMATRIX modelMatrix)
	{
		D3DXMATRIX wvp;
		wvp = modelMatrix * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", modelMatrix);
		mEffect->SetVariable("g_matWVP", wvp);

		mKeyFrames[mCurrentFrame].Data->VertexData.Bind(0);
		mKeyFrames[mCurrentFrame + 1].Data->VertexData.Bind(1);

		for (int p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mKeyFrames[mCurrentFrame].Data->VertexData.GetElementCount(), 0);
		}

	}

	void MorphAnimation::HandleTime(float dt)
	{
		if (mForwards) // If animation is going forwards
		{
			mTime += dt;

			if (mTime > mKeyFrames[mCurrentFrame].TimeSpan) // This key frame is over
			{
				if (mCurrentFrame < mKeyFrames.size() - 2) // This key frame isn't the last one (don't turn the animation around)
				{
					mTime = 0.0f;
					mCurrentFrame++;
				}
				else // This key frame is the last one, turn backward or stop.
				{
					if (mLooping)
					{
						mForwards = false;
					}
					
					// Set time to largest possible for this frame.
					mTime = mKeyFrames[mCurrentFrame].TimeSpan;
					
				}
			}
		}
		else // The animation is going backwards
		{
			mTime -= dt;

			if (mTime < 0.0f) // This key frame is over
			{
				if (mCurrentFrame > 0) // This key frame isn't the first one (don't turn the animation around)
				{
					mCurrentFrame--;
					mTime = mKeyFrames[mCurrentFrame].TimeSpan;
				}
				else // This key frame is the first one, turn forward.
				{
					mForwards = true;

					// Set time to smallest possible for this frame.
					mTime = 0.0f;
				}
			}
		}
	}
}