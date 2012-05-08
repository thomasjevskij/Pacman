#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "Camera.hpp"

namespace View
{
	class Pacman
	{
	public:
		Pacman();
		void Draw(float dt,Helper::Camera camera);
		void PlayEatPellet();
		void PlayDie();
		void PlayEatPowerPellet();
		void PlayEatFruit();
		void PlayEatGhost();
	private:
		//Helper::Animation mAnimation;
		//Resources::Sound3D mEatPelletSound;
		//Resources::Sound3D mDieSound;
		//Resources::Sound3D mEatPowerPelletSound;
		//Resources::Sound3D mEatFruitSound;
		//Resources::Sound3D mEatGhostSound;
	};
}
#endif