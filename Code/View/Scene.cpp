#include "Scene.hpp"
#include <cmath>

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
		mPelletObject.SetTintColor(D3DXCOLOR(1.0, 1.0, 0.0, 1.0));
		mPowPelletObject.SetScale(C_POW_PELLET_SIZE);
		mPowPelletObject.SetTintColor(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

		for (int i = 0; i < mModelDataInterface->GetGhostPositions().size(); ++i)
		{
			mGhosts.push_back(View::Ghost(device, Ghost::C_COLORS[i]));
		}
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
		mCameraController->Update(dt, mModelDataInterface);
		mCamera->Commit();

		const std::vector<Model::Coord>& ghostPositions = mModelDataInterface->GetGhostPositions();
		for (int i = 0; i < ghostPositions.size(); ++i)
		{
			mGhosts[i].Update(dt, Helper::Point2f(ghostPositions[i].X * Environment::C_CELL_SIZE, 
											      ghostPositions[i].Y * Environment::C_CELL_SIZE), 
							      Helper::Point2f((mModelDataInterface->GetPacmanPosition().X + 0.5f) * Environment::C_CELL_SIZE, 
											      (mModelDataInterface->GetPacmanPosition().Y + 0.5f) * Environment::C_CELL_SIZE));
		}
		
		Helper::Point2f offset(0.5f, 0.5f);
		mPacman.Update(dt, (mModelDataInterface->GetPacmanPosition()) * Environment::C_CELL_SIZE, mModelDataInterface->GetPacmanFacing());
	}

	void Scene::Draw(float dt)
	{
		/*
		Resources::ModelObj obj(mDevice, "ghost2.obj");
		D3DXMATRIX translation, scale, model;
		D3DXMatrixTranslation(&translation, 40, 40, 40);
		D3DXMatrixScaling(&scale, 30.0f, 30.0f, 30.0f);
		model = scale * translation;
		*/

		mEnvironment->Draw(*mCamera);
		mPacman.Draw(mCamera);

		for (int i = 0; i < mModelDataInterface->GetGhostPositions().size(); ++i)
		{
			mGhosts[i].Draw(dt, mCamera);
		}


		D3DXVECTOR3 camPos = mCamera->GetPosition();
		
		const std::vector<Model::Coord>& pelletPosInGrid = mModelDataInterface->GetLevel().GetPelletPositions();


		mPelletObject.Bind();
		for(int i = 0; i < pelletPosInGrid.size(); ++i)
		{
			D3DXVECTOR3 pelletPos = D3DXVECTOR3((pelletPosInGrid[i].X + 0.5f) * Environment::C_CELL_SIZE, 
												 C_PELLET_Y_POS, 
												 (pelletPosInGrid[i].Y + 0.5f) * Environment::C_CELL_SIZE);
			

			if (abs(camPos.x - pelletPos.x) <= 1.1f * Environment::C_CELL_SIZE || 
				abs(camPos.z - pelletPos.z) <= 1.1f * Environment::C_CELL_SIZE)
				mPelletObject.Draw(pelletPos, *mCamera);
		}



		const std::vector<Model::Coord>& powPelletPosInGrid = mModelDataInterface->GetLevel().GetPowerPelletPositions();

		mPowPelletObject.Bind();
		for(int i = 0; i < powPelletPosInGrid.size(); ++i)
		{
			D3DXVECTOR3 pelletPos = D3DXVECTOR3((powPelletPosInGrid[i].X + 0.5f) * Environment::C_CELL_SIZE, 
												 C_PELLET_Y_POS, 
												 (powPelletPosInGrid[i].Y + 0.5f) * Environment::C_CELL_SIZE);

			if (abs(camPos.x - pelletPos.x) <= 1.1f * Environment::C_CELL_SIZE || 
				abs(camPos.z - pelletPos.z) <= 1.1f * Environment::C_CELL_SIZE)
				mPowPelletObject.Draw(pelletPos, *mCamera);
		}
	}
}