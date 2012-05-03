#include <D3D10.h>
#include <D3DX10.h>
#include "Camera.hpp"

namespace Helper
{
	class ParticleHandlerInterface
	{
	public:
		virtual void Run(Camera Cam) = 0;
	};
}