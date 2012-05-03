#include "ChaseCamera.hpp"

namespace Helper
{
	ChaseCamera::ChaseCamera(D3DXVECTOR3 pos)
	{
		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH( &proj, D3DX_PI/2, 1, 0, 500 );
		mCamera = new Camera(proj,pos,D3DXVECTOR3(0,0,1));
	}

	void ChaseCamera::Update(float dt,Model::Player pacman)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3(-50,10,-50);
		temp.x *= pacman.GetFacing().X;
		temp.z *= pacman.GetFacing().Y;
		mCamera->SetPosition(D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y) + temp);
		mCamera->SetFacingPoint(D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y));
	}

	const Camera& ChaseCamera::GetCamera() const
	{
		return *mCamera;
	}
}