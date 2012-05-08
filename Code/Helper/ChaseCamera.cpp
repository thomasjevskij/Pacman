#include "ChaseCamera.hpp"

namespace Helper
{
	ChaseCamera::ChaseCamera(Helper::Camera *c):
	mCamera(c)
	{
	}

	void ChaseCamera::Update(float dt,Model::Player pacman)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3(-50,10,-50);
		temp.x *= pacman.GetFacing().X;
		temp.z *= pacman.GetFacing().Y;
		mCamera->SetPosition(D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y) + temp);
		mCamera->SetFacingPoint(D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y));
		mCamera->Commit();
	}

	const Camera& ChaseCamera::GetCamera() const
	{
		return *mCamera;
	}
}