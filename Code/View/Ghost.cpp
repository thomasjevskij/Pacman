#include "Ghost.hpp"

namespace View
{
	const float Ghost::C_HEIGHT = 5.0f;
	const D3DXCOLOR Ghost::C_COLORS[] = { D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f) };

	Ghost::Ghost(ID3D10Device* device, const D3DXCOLOR& color)
		: mScale(2.5f)
		, mColor(color)
	{

		mParticleSystem = new Helper::ParticleSystem(device, D3DXVECTOR3(0,0,0), "GhostTrail.fx", color ,10,false,true,true);

		mObject = new Resources::ModelObj(device,"ghost2.obj");
		mObject->SetTintColor(mColor);

		D3DXMatrixIdentity(&mModelMatrix);
	}

	void Ghost::Draw(float dt, Helper::Camera* camera)
	{
		mObject->Bind();
		mObject->Draw(mModelMatrix, *camera);
		mParticleSystem->Draw(dt, *camera);
	}

	void Ghost::Update(float dt, Helper::Point2f ghostPos, Helper::Point2f pacmanPos)
	{
		D3DXMATRIX translation, scale;

		D3DXMatrixScaling(&scale, mScale, mScale, mScale);
		D3DXMatrixTranslation(&translation,ghostPos.X, C_HEIGHT, ghostPos.Y);

		mModelMatrix = scale * translation;
		mParticleSystem->SetPosition(D3DXVECTOR3(ghostPos.X, C_HEIGHT, ghostPos.Y));
	}

	void Ghost::PlayerSound()
	{

	}
}