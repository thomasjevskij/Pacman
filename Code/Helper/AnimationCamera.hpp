#ifndef ANIMATIONCAMERA_HPP
#define ANIMATIONCAMERA_HPP


#include "Camera.hpp"
#include "Player.hpp"

namespace Helper
{
	class AnimationCamera
	{
	public:
		AnimationCamera(Helper::Camera *c);

		void Update(float dt,Model::Player pacman);

		void Restart();

		const Camera& GetCamera() const;
	private:
		Camera* mCamera;
		float mRot;
	};
}
#endif