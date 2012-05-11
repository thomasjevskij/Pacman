#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Global.hpp"
#include "ApplicationWindow.hpp"
#include "Environment.hpp"
#include "Level.hpp"
#include "Ghost.hpp" // Debug
#include "Camera.hpp"
#include "ModelDataInterface.hpp"
#include "ChaseCamera.hpp"	// Debug
#include "Pacman.hpp"

namespace View
{
	class Scene
	{
	public:
		Scene(ID3D10Device* device, Model::Level level, Framework::ApplicationWindow* window, Model::ModelDataInterface* modelData);
		~Scene() throw();

		void Create3DLevel(Model::Level level);

		void Update(float dt);
		void Draw(float dt);

	private:
		static const float C_PELLET_SIZE;
		static const float C_POW_PELLET_SIZE;
		static const float C_PELLET_Y_POS;

		Model::ModelDataInterface* mModelDataInterface;
		ID3D10Device* mDevice;
		View::Environment* mEnvironment;
		Helper::Camera* mCamera;
		Helper::ChaseCamera* mCameraController;
		Resources::ModelObj mPelletObject;
		Resources::ModelObj mPowPelletObject;
		std::vector<View::Ghost> mGhosts;				// Debug
		Pacman mPacman;

		Scene(const Scene&);
		Scene& operator=(const Scene&);
	};
}
#endif