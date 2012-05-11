#include "Pacman.hpp"


namespace View
{
	const float Pacman::C_HEIGHT = 5.0f;
	
	Pacman::Pacman(ID3D10Device* device)
		: mScale(2.5f)
	{
		std::vector<std::string> keyFrameFilenames;
		keyFrameFilenames.push_back("Pacman1.obj");
		keyFrameFilenames.push_back("Pacman2.obj");

		std::vector<float> timeSpans;
		timeSpans.push_back(0.3);
		timeSpans.push_back(0.3);

		mAnimation = new Helper::MorphAnimation(device,keyFrameFilenames,timeSpans);
		D3DXMatrixIdentity(&mModelMatrix);
	}

	void Pacman::Draw(Helper::Camera* camera)
	{
		mAnimation->Draw(*camera,mModelMatrix);
	}

	void Pacman::Update(float dt,Helper::Point2f pos,Model::Coord facing)
	{
		D3DXMATRIX translation, rot, scale;
		D3DXMatrixScaling(&scale, mScale, mScale, mScale);
		D3DXMatrixTranslation(&translation,pos.X,C_HEIGHT,pos.Y);

		if(facing.X == -1)
			D3DXMatrixRotationY(&rot,0);
		else if(facing.X == 1)
			D3DXMatrixRotationY(&rot,D3DX_PI);
		else if(facing.Y == 1)
			D3DXMatrixRotationY(&rot,D3DX_PI/2);
		else if(facing.Y == -1)
			D3DXMatrixRotationY(&rot,-D3DX_PI/2);

		mModelMatrix = scale * rot * translation;
		mAnimation->Update(dt);
	}

	void Pacman::PlayEatPellet()
	{

	}

	void Pacman::PlayDie()
	{

	}

	void Pacman::PlayEatPowerPellet()
	{

	}

	void Pacman::PlayEatFruit()
	{

	}

	void Pacman::PlayEatGhost()
	{

	}
}