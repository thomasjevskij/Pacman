#include <cmath>
#include "ChaseCamera.hpp"
#include "Environment.hpp"
#include "Pacman.hpp"

namespace Helper
{
	const float ChaseCamera::C_CHASE_SPEED = 10.0f;
<<<<<<< HEAD
	const float ChaseCamera::C_CHASE_HEIGHT = 100.0f;//25
	const float ChaseCamera::C_CHASE_DISTANCE = 2.5f;//2.5
=======
	const float ChaseCamera::C_CHASE_HEIGHT = 75.0f;
	const float ChaseCamera::C_CHASE_DISTANCE = 2.5f;
>>>>>>> 05ec8b7d7c0cb5e1a40f8e163cbc639d69482c3c

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