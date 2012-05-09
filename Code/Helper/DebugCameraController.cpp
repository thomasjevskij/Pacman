#include "DebugCameraController.hpp"

namespace Helper
{
	DebugCameraController::DebugCameraController(D3DXVECTOR3 pos,Helper::Camera *c):
	mCamera(c)
	{
		mCamera->SetPosition(pos);

		mRot = 0;
		yRot = 0;
		mKeyState = D3DXVECTOR3(0,0,0);

	}

	void DebugCameraController::Update(float dt)
	{
		//Kollar s� att rotationen befinner sig i ett lagom intervall och �kar om 
		//keystates s�ger att en av sv�ngnings knapparna �r nertryckta
		mRot += (TWO_PI/2)*dt*mKeyState.x;
		if(mRot < 0)
			mRot += TWO_PI;
		else if(mRot > TWO_PI)
			mRot -= TWO_PI;

		yRot += (TWO_PI/2)*dt*mKeyState.y;
		if(yRot < -TWO_PI/4)
			yRot = -TWO_PI/4;
		else if(yRot > TWO_PI/4)
			yRot = TWO_PI/4;

		mCamera->SetDirection(D3DXVECTOR3(cos(mRot),sin(yRot) ,sin(mRot)));
		
		//Uppdaterar kamerans possition
		mCamera->SetPosition(mCamera->GetPosition()+(mCamera->GetDirection()*mKeyState.z*C_MOVESPEED*dt));

		mCamera->Commit();
	}

	void DebugCameraController::KeyPressed(Framework::ApplicationWindow* window, int keyCode)
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
			mKeyState.x = -1;
		}
		else if(VK_LEFT == keyCode)
		{
			mKeyState.x = 1;
		}
		else if(VK_NUMPAD8 == keyCode)
		{
			mKeyState.y = 1;
		}
		else if(VK_NUMPAD5 == keyCode)
		{
			mKeyState.y = -1;
		}
	}

	void DebugCameraController::KeyReleased(Framework::ApplicationWindow* window, int keyCode)
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
		else if(VK_NUMPAD8 == keyCode)
		{
			mKeyState.y = 0;
		}
		else if(VK_NUMPAD5 == keyCode)
		{
			mKeyState.y = 0;
		}
	}

	const D3DXVECTOR3& DebugCameraController::GetPosition() const
	{
		return mCamera->GetPosition();
	}
	const D3DXVECTOR3& DebugCameraController::GetDirection() const
	{
		return mCamera->GetDirection();
	}
	const D3DXMATRIX& DebugCameraController::GetViewProjection() const
	{
		return mCamera->GetViewProjection();
	}
	const D3DXMATRIX& DebugCameraController::GetView() const
	{
		return mCamera->GetView();
	}

	const Camera& DebugCameraController::GetCamera() const
	{
		return *mCamera;
	}
}