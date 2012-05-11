#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "Camera.hpp"
#include "MorphAnimation.hpp"
#include "Coord.hpp"
#include "Global.hpp"

namespace View
{
	class Pacman
	{
	public:
		Pacman(ID3D10Device* device);
		void Draw(Helper::Camera* camera);
		void Update(float dt,Helper::Point2f pos,Model::Coord facing);
		void PlayEatPellet();
		void PlayDie();
		void PlayEatPowerPellet();
		void PlayEatFruit();
		void PlayEatGhost();

		static const float C_HEIGHT;
	private:
		Helper::MorphAnimation* mAnimation;
		D3DXMATRIX mModelMatrix;
		float mScale;

		
		//Resources::Sound3D mEatPelletSound;
		//Resources::Sound3D mDieSound;
		//Resources::Sound3D mEatPowerPelletSound;
		//Resources::Sound3D mEatFruitSound;
		//Resources::Sound3D mEatGhostSound;
	};
}
#endif