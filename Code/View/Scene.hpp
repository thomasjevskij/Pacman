#ifndef SCENE_HPP
#define SCENE_HPP

#include "Global.hpp"
#include "Environment.hpp"
#include "Level.hpp"
#include "Ghost.hpp" // Debug
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
		void Draw(float dt);

	private:
		ID3D10Device* mDevice;
		View::Environment* mEnvironment;
		Helper::Camera* mCamera;
		Helper::DebugCameraController* mCameraController;
		View::Ghost* mGhost;				// Debug

		Scene(const Scene&);
		Scene& operator=(const Scene&);
	};
}
#endif