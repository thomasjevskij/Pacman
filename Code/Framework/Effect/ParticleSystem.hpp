#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "Global.hpp"
#include <string>
#include "Effect.hpp"
#include "Camera.hpp"
#include <vector>
#include <cstdlib>
#include "VertexBuffer.hpp"
#include "D3DResourceManager.hpp"

namespace Helper
{
	class ParticleSystem
	{
	public:
		ParticleSystem(ID3D10Device *device,const D3DXVECTOR3& pos,const std::string& file,const D3DXCOLOR& color,const bool& Gravity = false,const bool& Acceleration = false);
		void SetPosition(const D3DXVECTOR3& pos);
		void Draw(float dt,const Camera& cam);
	private:

		struct Particle
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Velocity;
			D3DXVECTOR3 Acceleration;
			float TimeLived;
			float TimeToLive;
		};

		D3DXVECTOR3 RandVec(int radius);

		void Update(float dt);
		ID3D10Device* mDevice;
		Framework::Effect* mEffect;
		D3DXVECTOR3 mPosition;
		D3DXCOLOR mColor;
		std::vector<Particle> mParticles;
		static const int C_PARTICLE_COUNT = 2000;
		static const int C_GRAVITY = 5;
		bool mGravityOn;
		bool mAccelerationOn;
		
	};
}
#endif