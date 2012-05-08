#ifndef DEBUGCAMERACONTROLER_HPP
#define DEBUGCAMERACONTROLER_HPP

#include "ApplicationWindow.hpp"
#include "Camera.hpp"


#define TWO_PI 6.283185307179586476925286766559

namespace Helper
{
	class DebugCameraController: public Framework::WindowNotificationSubscriber
	{
	public:
		DebugCameraController(D3DXVECTOR3 pos,Helper::Camera *c);

		void Update(float dt);

		void KeyPressed(Framework::ApplicationWindow* window, int keyCode);
		void KeyReleased(Framework::ApplicationWindow* window, int keyCode);

		const D3DXVECTOR3& GetPosition() const;
		const D3DXVECTOR3& GetDirection() const;
		const D3DXMATRIX& GetViewProjection() const;
		const D3DXMATRIX& GetView() const;
		const Camera& GetCamera() const;
	private:
		Camera* mCamera;
		D3DXVECTOR3 mKeyState;
		static const int C_MOVESPEED = 20;
		float mRot,yRot;
	};
}
#endif