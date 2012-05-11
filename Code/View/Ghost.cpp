#include "Ghost.hpp"

namespace View
{
	Ghost::Ghost(ID3D10Device* device)
	{

			mParticleSystem = new Helper::ParticleSystem(device,D3DXVECTOR3(0,0,0),"GhostTrail.fx",D3DXCOLOR(0,1,0,0.5),10);
			mObject = new Resources::ModelObj(device,"ghost.obj");
			D3DXMatrixIdentity(&mModelMatrix);
	}

	void Ghost::Draw(float dt,Helper::Camera* camera)
	{
		mObject->Draw(mModelMatrix,*camera);
		mParticleSystem->Draw(dt,*camera);
		
	}

	void Ghost::Update(float dt,Helper::Point2f ghostPos,Helper::Point2f pacmanPos)
	{
		D3DXMATRIX translation,rot;
		D3DXMatrixTranslation(&translation,ghostPos.X,30,ghostPos.Y);
		
		D3DXVECTOR3 dxyGP = D3DXVECTOR3(ghostPos.X - pacmanPos.X,0,ghostPos.Y - pacmanPos.Y);

		D3DXVec3Normalize(&dxyGP,&dxyGP);

		D3DXMatrixRotationY(&rot, atan(dxyGP.z/dxyGP.x));

		mModelMatrix = rot * translation;

		mParticleSystem->SetPosition(D3DXVECTOR3(ghostPos.X,30,ghostPos.Y));
	}

	void Ghost::PlayerSound()
	{

	}
}