#ifndef SCENE_HPP
#define SCENE_HPP

#include "Global.hpp"
#include "Environment.hpp"
#include "Level.hpp"
#include "Camera.hpp"
#include "DebugCameraController.hpp"	// Debug

namespace View
{
	class Scene
	{
	public:
		Scene(ID3D10Device* device, Model::Level level, Framework::ApplicationWindow* window);
		~Scene() throw();

		void Create3DLevel(Model::Level level);

		void Update(float dt);
		void Draw();

	private:
		ID3D10Device* mDevice;
		View::Environment* mEnvironment;
		Helper::Camera* mCamera;
		Helper::DebugCameraController* mCameraController;

		Scene(const Scene&);
		Scene& operator=(const Scene&);
	};
}
#endif