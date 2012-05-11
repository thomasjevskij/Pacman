#ifndef VIEWGHOST_HPP
#define VIEWGHOST_HPP

#include "Global.hpp"
#include "ModelObj.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"

namespace View
{
	class Ghost
	{
	public:
		Ghost(ID3D10Device* device, const D3DXCOLOR& color);
		void Draw(float dt,Helper::Camera* camera);
		void Update(float dt,Helper::Point2f ghostPos,Helper::Point2f pacmanPos);
		void PlayerSound();

		static const float C_HEIGHT;
		static const D3DXCOLOR C_COLORS[];
	private:
		Resources::ModelObj* mObject;
		Helper::ParticleSystem* mParticleSystem;
		D3DXMATRIX mModelMatrix;
		//Resources::Sound3D* mSound;
	};
}
#endif