#include <D3D10.h>
#include <D3DX10.h>

class ParticleHandlerInterface
{
public:
	virtual void Initialize() = 0;
	virtual void NewEffect(char Effect[256],D3DXVECTOR3 Pos) = 0;
	virtual void Run(Camera Cam) = 0;
};