#ifndef CHASECAMERA_HPP
#define CHASECAMERA_HPP

#include "Camera.hpp"
#include "Player.hpp"
#include "ModelDataInterface.hpp"

namespace Helper
{
	class ChaseCamera
	{
	public:
		ChaseCamera(Helper::Camera *c, Model::ModelDataInterface* modelDataInterface);

		void Update(float dt, Model::ModelDataInterface* modelDataInterface);

		const Camera& GetCamera() const;
	private:
		static const float C_CHASE_SPEED;
		static const float C_CHASE_HEIGHT;
		static const float C_CHASE_DISTANCE;

		D3DXVECTOR3 mTargetPosition;
		D3DXVECTOR3 mPosition;
		Camera* mCamera;
	};
}

#endif