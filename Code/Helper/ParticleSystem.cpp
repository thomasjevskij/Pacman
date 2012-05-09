#include "ParticleSystem.hpp"

namespace Helper
{
	ParticleSystem::ParticleSystem(ID3D10Device *device,const D3DXVECTOR3& pos,const std::string& file,const D3DXCOLOR& color,const float& radie,const bool& Acceleration,const bool& Gravity,const bool& RandomStart):
	mDevice(device),mPosition(pos), mColor(color), mGravityOn(Gravity),mAccelerationOn(Acceleration),mRandomStart(RandomStart),mRadie(radie)
	{
		
		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load(file);
		Framework::InputLayoutVector ParticleLayout;
		ParticleLayout.push_back(Framework::InputLayoutElement("POSITION",DXGI_FORMAT_R32G32B32_FLOAT));
		ParticleLayout.push_back(Framework::InputLayoutElement("VELOCITY",DXGI_FORMAT_R32G32B32_FLOAT));
		ParticleLayout.push_back(Framework::InputLayoutElement("ACCELERATION",DXGI_FORMAT_R32G32B32_FLOAT));
		ParticleLayout.push_back(Framework::InputLayoutElement("TIMELIVED",DXGI_FORMAT_R32_FLOAT));
		ParticleLayout.push_back(Framework::InputLayoutElement("TIMETOLIVE",DXGI_FORMAT_R32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(ParticleLayout);
		ID3D10ShaderResourceView* ParticleTexRV;
		D3DX10CreateShaderResourceViewFromFile( device, "Resources/Effects/star.jpg", NULL, NULL, &ParticleTexRV, NULL );
		mEffect->SetVariable("Color",D3DXVECTOR4(mColor));
		mEffect->SetVariable("Texture",ParticleTexRV);

		Particle p;
		p.Position = mPosition;
		p.Acceleration = RandVec(5);
		p.Velocity = RandVec(10);
		p.TimeToLive = rand() % 3 + 2;
		p.TimeLived = 0;
				
		mParticles.push_back(p);
	}

	void ParticleSystem::SetPosition(const D3DXVECTOR3& pos)
	{
		mPosition = pos;
	}

	void ParticleSystem::Draw(float dt,const Camera& cam)
	{
		Update(dt);

		Framework::VertexBuffer::Description particleBuffer;
		particleBuffer.Topology = Framework::Topology::PointList;
		particleBuffer.Usage = Framework::Usage::Default;
		particleBuffer.ElementSize = sizeof(Particle);
		particleBuffer.ElementCount = mParticles.size();
		particleBuffer.FirstElementPointer = &mParticles[0];

		Framework::VertexBuffer buffer(mDevice);
		buffer.SetData(particleBuffer,NULL);

		buffer.Bind();

		mEffect->SetVariable("WorldViewProj",cam.GetViewProjection());
		D3DXMATRIX InvView;
		D3DXMatrixInverse( &InvView, NULL, &cam.GetView() );
		mEffect->SetVariable("InvView",InvView);
		
		

		for( UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p )
		{
			mEffect->GetTechniqueByIndex( 0 ).GetPassByIndex( p ).Apply(mDevice);
			mDevice->Draw(buffer.GetElementCount(), 0);
		}

		float blendFactor[] = {0,0,0,0};
		mDevice->OMSetBlendState(NULL,blendFactor,0xffffffff);
	}

	void ParticleSystem::Update(float dt)
	{
		for(int i = 0;i < mParticles.size();)
		{
			
			mParticles[i].Velocity += mParticles[i].Acceleration*dt;

			if(mGravityOn)
				mParticles[i].Acceleration.y -= C_GRAVITY * dt;

			mParticles[i].Position += mParticles[i].Velocity*dt;
			mParticles[i].TimeLived += dt;

			if(mParticles[i].TimeLived >= mParticles[i].TimeToLive)
				mParticles.erase(mParticles.begin()+i);
			else
				i++;
		}
		if(mParticles.size() < C_PARTICLE_COUNT)
		{
			for(int i = 0;i < (C_PARTICLE_COUNT/3)*dt ;i++)
			{
				if(mParticles.size() >= C_PARTICLE_COUNT)
					break;
				
				Particle p;
				if(mRandomStart)
					p.Position = mPosition + RandVec(mRadie);
				else
					p.Position = mPosition;

				if(mAccelerationOn)
					p.Acceleration = RandVec(5);
				else
					p.Acceleration = D3DXVECTOR3(0,0,0);

				p.Velocity = RandVec(10);
				p.TimeToLive = rand() % 3 + 2;
				p.TimeLived = 0;
				
				mParticles.push_back(p);
			}
		}
	}

	D3DXVECTOR3 ParticleSystem::RandVec(int radius)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3( rand() % 20 - 10,rand() % 20 - 10,rand() % 20 - 10);
		D3DXVec3Normalize(&temp,&temp);
		temp *= rand() % radius;
		return temp;
	}

}