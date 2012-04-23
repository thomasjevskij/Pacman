#include "ParticleSystem.hpp"

namespace Helper
{
	ParticleSystem::ParticleSystem(ID3D10Device *device,const D3DXVECTOR3& pos,const std::string& file,const D3DXCOLOR& color):
	mDevice(device), mColor(color)
	{
		mEffect = Resources::EffectResourceManager::Instance().Load(file);
	}

	void ParticleSystem::SetPosition(const D3DXVECTOR3& pos)
	{
		mPosition = pos;
	}

	void ParticleSystem::Draw(float dt,const Camera& cam)
	{
		Update(dt);

		D3D::VertexBuffer::Description particleBuffer;
		particleBuffer.Topology = D3D::Topology::PointList;
		particleBuffer.Usage = D3D::Usage::Default;
		particleBuffer.ElementSize = sizeof(Particle);
		particleBuffer.ElementCount = mParticles.size();
		particleBuffer.FirstElementPointer = &mParticles[0];

		D3D::VertexBuffer buffer(mDevice);
		buffer.SetData(particleBuffer,NULL);

		buffer.Bind();

		for( UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p )
		{
			mEffect->GetTechniqueByIndex( 0 ).GetPassByIndex( p ).Apply(mDevice);
			buffer.Draw();
		}
	}

	D3DXVECTOR3 RandVec(int radius)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3( rand() % 20 - 10,rand() % 20 - 10,rand() % 20 - 10);
		D3DXVec3Normalize(&temp,&temp);
		temp *= rand() % radius;
		return temp;
	}

	void ParticleSystem::Update(float dt)
	{
		for(int i = 0;i < mParticles.size();)
		{
			mParticles[i].Velocity += mParticles[i].Acceleration*dt;
			mParticles[i].Position += mParticles[i].Velocity*dt;
			mParticles[i].TimeLived += dt;

			if(mParticles[i].TimeLived >= mParticles[i].TimeToLive)
				mParticles.erase(mParticles.begin()+i);
			else
				i++;
		}
		if(mParticles.size() < C_PARTICLE_COUNT)
		{
			for(int i = 0;i < 300*dt ;i++)
			{
				if(mParticles.size() >= C_PARTICLE_COUNT)
					break;
				
				Particle p;
				p.Position = RandVec(100);
				p.Acceleration = RandVec(5);
				p.Velocity = RandVec(10);
				p.TimeToLive = rand() % 3 + 2;
				p.TimeLived = 0;
				
				mParticles.push_back(p);
			}
		}
	}


}