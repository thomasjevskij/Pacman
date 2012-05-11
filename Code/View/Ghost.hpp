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
		void Draw(float dt, Helper::Camera* camera, bool scared);
		void Update(float dt, Helper::Point2f ghostPos, Helper::Point2f pacmanPos);
		void PlayerSound();

		static const float C_HEIGHT;
		static const D3DXCOLOR C_COLORS[];
		static const D3DXCOLOR C_SCARED_COLOR;
	private:
		Resources::ModelObj* mObject;
		Helper::ParticleSystem* mParticleSystem;
		D3DXMATRIX mModelMatrix;
		float mScale;
		D3DXCOLOR mColor;
		//Resources::Sound3D* mSound;
	};
}
#endif