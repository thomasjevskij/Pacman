#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Primitives.hpp"

namespace Helper
{
	class Camera
	{
	public:
		Camera(const D3DXMATRIX& projection, const D3DXVECTOR3& position = D3DXVECTOR3(0, 0, 0), 
			   const D3DXVECTOR3& direction = D3DXVECTOR3(1, 0, 0));

		const D3DXMATRIX& GetView() const;
		const D3DXMATRIX& GetProjection() const;
		const D3DXMATRIX& GetViewProjection() const;

		void SetProjection(const D3DXMATRIX& projection);

		void SetPosition(const D3DXVECTOR3& position);
		void SetDirection(const D3DXVECTOR3& direction);
		void SetFacingPoint(const D3DXVECTOR3& target);

		void Commit();

		const D3DXVECTOR3& GetPosition() const;
		const D3DXVECTOR3& GetDirection() const;
		const D3DXMATRIX& GetViewProjection() const;
		const D3DXMATRIX& GetView() const;

	private:
		static const D3DXVECTOR3 C_WORLD_UP;

		struct CameraState
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Direction;
		};

		CameraState mStagingChanges;
		D3DXMATRIX mView;
		D3DXMATRIX mProjection;
		D3DXMATRIX mViewProjection;
	};
}

#endif