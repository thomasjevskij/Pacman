#include <cmath>
#include "ChaseCamera.hpp"
#include "Environment.hpp"
#include "Pacman.hpp"

namespace Helper
{
	const float ChaseCamera::C_CHASE_SPEED = 10.0f;

	const float ChaseCamera::C_CHASE_HEIGHT = 25.0f;//25
	const float ChaseCamera::C_CHASE_DISTANCE = 2.5f;//2.5


	ChaseCamera::ChaseCamera(Helper::Camera *c, Model::ModelDataInterface* modelDataInterface)
		: mCamera(c)
		, mTargetPosition(0,0,0)
		, mPosition(0,0,0)
	{
		mTargetPosition.x = modelDataInterface->GetPacmanPosition().X - (C_CHASE_DISTANCE * modelDataInterface->GetPacmanFacing().X);
		mTargetPosition.z = modelDataInterface->GetPacmanPosition().Y - (C_CHASE_DISTANCE * modelDataInterface->GetPacmanFacing().Y);

		mTargetPosition *= View::Environment::C_CELL_SIZE;
		mTargetPosition.y = C_CHASE_HEIGHT + View::Pacman::C_HEIGHT;

		mPosition = mTargetPosition;
	}

	void ChaseCamera::Update(float dt, Model::ModelDataInterface* modelDataInterface)
	{
		mTargetPosition.x = modelDataInterface->GetPacmanPosition().X - (C_CHASE_DISTANCE * modelDataInterface->GetPacmanFacing().X);
		mTargetPosition.z = modelDataInterface->GetPacmanPosition().Y - (C_CHASE_DISTANCE * modelDataInterface->GetPacmanFacing().Y);

		mTargetPosition *= View::Environment::C_CELL_SIZE;
		mTargetPosition.y = C_CHASE_HEIGHT + View::Pacman::C_HEIGHT;

		if (D3DXVec3LengthSq(&(mTargetPosition - mPosition)) > 2.0f)
		{
			/*D3DXVECTOR3 vel = mTargetPosition - mPosition;
			D3DXVec3Normalize(&vel, &vel);
			mPosition += vel;*/
			mPosition += (mTargetPosition - mPosition) / 5;
		}
		else
			mPosition = mTargetPosition;

		D3DXVECTOR3 pacPos;
		pacPos.x = modelDataInterface->GetPacmanPosition().X;
		pacPos.z = modelDataInterface->GetPacmanPosition().Y;
		pacPos *= View::Environment::C_CELL_SIZE;

		pacPos.y = View::Pacman::C_HEIGHT;

		mCamera->SetPosition(mPosition);
		mCamera->SetFacingPoint(pacPos);
		mCamera->Commit();
	}

	const Camera& ChaseCamera::GetCamera() const
	{
		return *mCamera;
	}
}