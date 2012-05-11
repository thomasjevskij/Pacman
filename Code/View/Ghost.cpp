#include "Ghost.hpp"

namespace View
{
	const float Ghost::C_HEIGHT = 5.0f;
	const D3DXCOLOR Ghost::C_COLORS[] = { D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f) };

	Ghost::Ghost(ID3D10Device* device, const D3DXCOLOR& color)
	{
		mParticleSystem = new Helper::ParticleSystem(device, D3DXVECTOR3(0,0,0), "GhostTrail.fx", color ,10);
		mObject = new Resources::ModelObj(device,"ghost.obj");
		D3DXMatrixIdentity(&mModelMatrix);
	}

	void Ghost::Draw(float dt, Helper::Camera* camera)
	{
		mObject->Draw(mModelMatrix, *camera);
		mParticleSystem->Draw(dt, *camera);
	}

	void Ghost::Update(float dt, Helper::Point2f ghostPos, Helper::Point2f pacmanPos)
	{
		D3DXMATRIX translation,rot;

		D3DXMatrixTranslation(&translation,ghostPos.X, C_HEIGHT, ghostPos.Y);

		D3DXVECTOR3 dxyGP = D3DXVECTOR3(ghostPos.X - pacmanPos.X, 0, ghostPos.Y - pacmanPos.Y);


		D3DXVec3Normalize(&dxyGP, &dxyGP);
		
		D3DXMatrixRotationY(&rot, atan(dxyGP.z / dxyGP.x));

		mModelMatrix = rot * translation;

		mParticleSystem->SetPosition(D3DXVECTOR3(ghostPos.X, C_HEIGHT, ghostPos.Y));
	}

	void Ghost::PlayerSound()
	{

	}
}