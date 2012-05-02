#include <D3D10.h>
#include <D3DX10.h>
#include "Camera.hpp"

namespace Helper
{
	class ParticleHandlerInterface
	{
	public:
		virtual void NewEffect(char Effect[256],D3DXVECTOR3 Pos) = 0;
		virtual void Run(Camera Cam) = 0;
	};
}