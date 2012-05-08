#include "AnimationCamera.hpp"

namespace Helper
{
	AnimationCamera::AnimationCamera(Helper::Camera *c):
	mCamera(c)
	{
		mRot = 0;
	}

	void AnimationCamera::Update(float dt,Model::Player pacman)
	{
		mRot += D3DX_PI/2 * dt;

		D3DXVECTOR3 temp = D3DXVECTOR3(-50,0,-50);
		temp.x *= pacman.GetFacing().X;
		temp.z *= pacman.GetFacing().Y;

		D3DXVECTOR3 newCamPos = D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y) + temp;

		newCamPos.x *= sin(mRot);
		newCamPos.z *= cos(mRot);

		mCamera->SetPosition(newCamPos);
		mCamera->SetFacingPoint(D3DXVECTOR3(pacman.GetRealPos().X,10,pacman.GetRealPos().Y));

		mCamera->Commit();
	}

	void AnimationCamera::Restart()
	{
		mRot = 0;
	}

	const Camera& AnimationCamera::GetCamera() const
	{
		return *mCamera;
	}
}