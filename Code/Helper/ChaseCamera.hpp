#ifndef CHASECAMERA_HPP
#define CHASECAMERA_HPP

#include "Camera.hpp"
#include "Player.hpp"

namespace Helper
{
	class ChaseCamera
	{
	public:
		ChaseCamera(D3DXVECTOR3 pos);

		void Update(float dt,Model::Player pacman);

		const Camera& GetCamera() const;
	private:
		Camera* mCamera;
	};
}

#endif