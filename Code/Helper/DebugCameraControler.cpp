#include "DebugCameraControler.hpp"

namespace Helper
{
	DebugCameraControler::DebugCameraControler(D3DXVECTOR3 pos)
	{
		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH( &proj, 60, 1080/756, 10, 500 );
		mCamera = new Camera(proj,pos,D3DXVECTOR3(0,-0.2,1));
		
		mRot = 0;
		mKeyState = D3DXVECTOR3(0,0,0);

	}

	void DebugCameraControler::Update(float dt)
	{
		//Kollar så att rotationen befinner sig i ett lagom intervall och ökar om 
		//keystates säger att en av svängnings knapparna är nertryckta
		mRot += (TWO_PI/2)*dt*mKeyState.x;
		if(mRot < 0)
			mRot += TWO_PI;
		else if(mRot > TWO_PI)
			mRot -= TWO_PI;

		mCamera->SetDirection(D3DXVECTOR3(cos(mRot),mCamera->GetDirection().y,sin(mRot)));
		
		//Uppdaterar kamerans possition
		mCamera->SetPosition(mCamera->GetPostion()+(mCamera->GetDirection()*mKeyState.z*C_MOVESPEED*dt));

		mCamera->Commit();
	}

	void DebugCameraControler::KeyPressed(Framework::ApplicationWindow* window, int keyCode)
	{
		if(VK_UP == keyCode)
		{
			mKeyState.z = 1;
		}
		else if(VK_DOWN == keyCode)
		{
			mKeyState.z = -1;
		}
		else if(VK_RIGHT == keyCode)
		{
			mKeyState.x = 1;
		}
		else if(VK_LEFT == keyCode)
		{
			mKeyState.x = -1;
		}
	}

	void DebugCameraControler::KeyReleased(Framework::ApplicationWindow* window, int keyCode)
	{
		if(VK_UP == keyCode)
		{
			mKeyState.z = 0;
		}
		else if(VK_DOWN == keyCode)
		{
			mKeyState.z = 0;
		}
		else if(VK_RIGHT == keyCode)
		{
			mKeyState.x = 0;
		}
		else if(VK_LEFT == keyCode)
		{
			mKeyState.x = 0;
		}
	}
}