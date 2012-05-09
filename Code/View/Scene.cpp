#include "Scene.hpp"

namespace View
{
	Scene::Scene(ID3D10Device* device, Model::Level level, Framework::ApplicationWindow* window)
		: mDevice(device)
		, mEnvironment(NULL)
		, mCamera(NULL)
		, mCameraController(NULL)
	{
		Helper::Frustum f;
		f.AspectRatio = static_cast<float>(window->GetClientWidth()) / window->GetClientHeight();
		f.FarDistance = 1000;
		f.FieldOfViewY = D3DX_PI * 0.25;
		f.NearDistance = 1;

		mCamera = new Helper::Camera(f.CreatePerspectiveProjection());
		mCameraController = new Helper::DebugCameraController(D3DXVECTOR3(0, 0, 0), mCamera);
		//mCameraController = new Helper::DebugCameraController(pacmanSpawnPoint, mCamera);

		window->AddNotificationSubscriber(mCameraController);

		Create3DLevel(level);
		mGhost = new View::Ghost(device);		// Debug
	}

	Scene::~Scene() throw()
	{
		SafeDelete(mEnvironment);
		SafeDelete(mCameraController);
		SafeDelete(mCamera);
	}

	void Scene::Create3DLevel(Model::Level level)
	{
		delete mEnvironment;
		mEnvironment = new View::Environment(mDevice, level);

		D3DXVECTOR3 pacmanSpawnPoint = D3DXVECTOR3(level.GetPacmanSpawnPosition().X * Environment::C_CELL_SIZE,
												   Environment::C_CELL_SIZE * 0.5,
												   level.GetPacmanSpawnPosition().Y * Environment::C_CELL_SIZE);

		mCamera->SetPosition(pacmanSpawnPoint);
	}

	void Scene::Update(float dt)
	{
		mCameraController->Update(dt);
		mCamera->Commit();

		mGhost->Update(dt, Helper::Point2f(0,0),Helper::Point2f(10,0));
	}

	void Scene::Draw(float dt)
	{
		mEnvironment->Draw(*mCamera);
		mGhost->Draw(dt, mCamera);
	}
}