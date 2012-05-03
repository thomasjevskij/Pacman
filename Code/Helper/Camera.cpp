#include "Camera.hpp"

namespace Helper
{
	const D3DXVECTOR3 Camera::C_WORLD_UP(0, 1, 0);

	Camera::Camera(const D3DXMATRIX& projection, const D3DXVECTOR3& position, const D3DXVECTOR3& direction)
	{
		SetProjection(projection);
		SetPosition(position);
		SetDirection(direction);
		Commit();
	}

	const D3DXMATRIX& Camera::GetView() const
	{
		return mView;
	}

	const D3DXMATRIX& Camera::GetProjection() const
	{
		return mProjection;
	}

	const D3DXMATRIX& Camera::GetViewProjection() const
	{
		return mViewProjection;
	}

	void Camera::SetProjection(const D3DXMATRIX& projection)
	{
		mProjection = projection;
	}

	void Camera::SetPosition(const D3DXVECTOR3& position)
	{
		mStagingChanges.Position = position;
	}

	void Camera::SetDirection(const D3DXVECTOR3& direction)
	{
		mStagingChanges.Direction = direction;
	}

	void Camera::SetFacingPoint(const D3DXVECTOR3& target)
	{
		mStagingChanges.Direction = target - mStagingChanges.Position;
	}


	void Camera::Commit()
	{
		D3DXVec3Normalize(&mStagingChanges.Direction, &mStagingChanges.Direction);

		// calculate view matrix here!
		D3DXVECTOR3 right;
		D3DXVECTOR3 up;
		D3DXVec3Cross(&right, &C_WORLD_UP, &mStagingChanges.Direction);
		D3DXVec3Cross(&up, &mStagingChanges.Direction, &right);

		mView.m[0][0] = right.x;
		mView.m[1][0] = right.y;
		mView.m[2][0] = right.z;
		mView.m[3][0] = -D3DXVec3Dot(&mStagingChanges.Position, &right);

		mView.m[0][1] = up.x;
		mView.m[1][1] = up.y;
		mView.m[2][1] = up.z;
		mView.m[3][1] = -D3DXVec3Dot(&mStagingChanges.Position, &up);

		mView.m[0][2] = mStagingChanges.Direction.x;
		mView.m[1][2] = mStagingChanges.Direction.y;
		mView.m[2][2] = mStagingChanges.Direction.z;
		mView.m[3][2] = -D3DXVec3Dot(&mStagingChanges.Position, &mStagingChanges.Direction);

		mView.m[0][3] = 0;
		mView.m[1][3] = 0;
		mView.m[2][3] = 0;
		mView.m[3][3] = 1;		

		mViewProjection = mView * mProjection;
	}
}