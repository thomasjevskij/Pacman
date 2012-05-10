#include "Scene.hpp"

namespace View
{
	const float Scene::C_PELLET_SIZE = 0.1f;
	const float Scene::C_POW_PELLET_SIZE = 0.3f;
	const float Scene::C_PELLET_Y_POS = 3;

	Scene::Scene(ID3D10Device* device, Model::Level level, Framework::ApplicationWindow* window, Model::ModelDataInterface* modelData)
		: mDevice(device)
		, mEnvironment(NULL)
		, mCamera(NULL)
		, mCameraController(NULL)
		, mPelletObject(device, "pellet.obj")
		, mPowPelletObject(device, "pellet.obj")
		, mModelDataInterface(modelData)
		, mPacman(device)
	{
		Helper::Frustum f;
		f.AspectRatio = static_cast<float>(window->GetClientWidth()) / window->GetClientHeight();
		f.FarDistance = 1000;
		f.FieldOfViewY = D3DX_PI * 0.25;
		f.NearDistance = 1;

		mCamera = new Helper::Camera(f.CreatePerspectiveProjection());
		mCameraController = new Helper::ChaseCamera(mCamera, mModelDataInterface);

		Create3DLevel(level);
		mPelletObject.SetScale(C_PELLET_SIZE);
		mPelletObject.SetTintColour(D3DXCOLOR(1.0, 1.0, 0.0, 1.0));
		mPowPelletObject.SetScale(C_POW_PELLET_SIZE);
		mPowPelletObject.SetTintColour(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

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

		const std::vector<Model::Coord> pelletPosInGrid = level.GetPelletPositions();
		const std::vector<Model::Coord> powPelletPosInGrid = level.GetPowerPelletPositions();
		mPelletPositions.clear();
		mPowPelletPositions.clear();

		for(int i = 0; i < pelletPosInGrid.size(); ++i)
		{
			mPelletPositions.push_back(D3DXVECTOR3((pelletPosInGrid[i].X + 0.5f) * Environment::C_CELL_SIZE, 
												   C_PELLET_Y_POS, 
												   (pelletPosInGrid[i].Y + 0.5f) * Environment::C_CELL_SIZE));
		}

		for(int j = 0; j < powPelletPosInGrid.size(); ++j)
		{
			mPowPelletPositions.push_back(D3DXVECTOR3((powPelletPosInGrid[j].X + 0.5f) * Environment::C_CELL_SIZE,
													  C_PELLET_Y_POS, 
													  (powPelletPosInGrid[j].Y + 0.5f) * Environment::C_CELL_SIZE));
		}
	}

	void Scene::Update(float dt)
	{
		mCameraController->Update(dt, mModelDataInterface);
		mCamera->Commit();

		mGhost->Update(dt, Helper::Point2f(0,0),Helper::Point2f(10,0));
		Helper::Point2f offset(0.5f, 0.5f);
		mPacman.Update(dt, (mModelDataInterface->GetPacmanPosition()) * Environment::C_CELL_SIZE, mModelDataInterface->GetPacmanFacing());
	}

	void Scene::Draw(float dt)
	{
		mEnvironment->Draw(*mCamera);
		mGhost->Draw(dt, mCamera);
		mPacman.Draw(mCamera);

		mPelletObject.Bind();
		for(int i = 0; i < mPelletPositions.size(); ++i)
		{
			mPelletObject.Draw(mPelletPositions[i], *mCamera);
		}

		mPowPelletObject.Bind();
		for(int i = 0; i < mPowPelletPositions.size(); ++i)
		{
			mPowPelletObject.Draw(mPowPelletPositions[i], *mCamera);
		}
	}
}