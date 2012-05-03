#include "MorphAnimation.hpp"

namespace Helper
{

	MorphAnimation::MorphAnimation(ID3D10Device* device)
		: mBuf1(device)
		, mBuf2(device)
		, mTime(0.0f)
		, mTimeSpan(3.0f)
		, mDevice(device)
	{
		struct AVertex
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 nor;
			D3DXVECTOR2 uv;
		};
		AVertex frame1[] = {
			{D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)}
		};
		AVertex frame2[] = {
			{D3DXVECTOR3(-1.0f, -1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(1.0f, -1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(1.0f, 1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)},
			{D3DXVECTOR3(-1.0f, 1.0f, 10.0f), D3DXVECTOR3(0,0,1), D3DXVECTOR2(0,0)}
		};
		Framework::VertexBuffer::Description desc;
		desc.ElementCount = 4;
		desc.ElementSize = sizeof(AVertex);
		desc.FirstElementPointer = frame1;
		desc.Topology = Framework::Topology::TriangleStrip;
		desc.Usage = Framework::Usage::Default;

		//desc.
		mBuf1.SetData(desc, NULL);
		desc.FirstElementPointer = frame2;
		mBuf2.SetData(desc, NULL);

		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Animation.fx");
		Framework::InputLayoutVector vec;
		vec.push_back(Framework::InputLayoutElement("POSITION1", DXGI_FORMAT_R32G32B32_FLOAT, 0));
		vec.push_back(Framework::InputLayoutElement("NORMAL1", DXGI_FORMAT_R32G32B32_FLOAT, 0));
		vec.push_back(Framework::InputLayoutElement("UV1", DXGI_FORMAT_R32G32_FLOAT, 0));
		vec.push_back(Framework::InputLayoutElement("POSITION2", DXGI_FORMAT_R32G32B32_FLOAT, 1));
		vec.push_back(Framework::InputLayoutElement("NORMAL2", DXGI_FORMAT_R32G32B32_FLOAT, 1));
		vec.push_back(Framework::InputLayoutElement("UV2", DXGI_FORMAT_R32G32_FLOAT, 1));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(vec);
	}

	void MorphAnimation::Update(float dt)
	{
		mTime += dt;
		if (mTime > mTimeSpan)
			mTime = mTimeSpan;

		mEffect->SetVariable("g_t", mTime / mTimeSpan);
	}

	void MorphAnimation::Draw(const Camera& camera, D3DXVECTOR3 position)
	{
		D3DXMATRIX w;
		D3DXMATRIX wvp;
		D3DXMatrixTranslation(&w, position.x, position.y, position.z);
		wvp = w * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", w);
		mEffect->SetVariable("g_matWVP", wvp);

		mBuf1.Bind(0);
		mBuf2.Bind(1);

		for (int p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			//mBuf1.Draw();   :-( / Lars
			mBuf2.Draw();
		}

	}
}