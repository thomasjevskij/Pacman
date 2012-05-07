#include "Environment.hpp"
#include "D3DResourceManager.hpp"
#include "Texture.hpp"

namespace View
{
	Environment::Environment(ID3D10Device* device, Model::Level level)
		: mDevice(device), mBuffer(NULL), mEffect(NULL), mWallObject(NULL)
	{
		CreateGround();
		CreateWalls(level);
	}

	Environment::~Environment() throw()
	{
		SafeDelete(mBuffer);
	}

	void Environment::CreateGround()
	{
		const int C_NUM_VERTICES = 4;
		Vertex vertices[C_NUM_VERTICES];

		vertices[0].Position = D3DXVECTOR3(-100, -3, -100);
		vertices[0].UV = D3DXVECTOR2(0, 0);

		vertices[1].Position = D3DXVECTOR3(100, -3, -100);
		vertices[1].UV = D3DXVECTOR2(10, 0);

		vertices[2].Position = D3DXVECTOR3(-100, -3, 100);
		vertices[2].UV = D3DXVECTOR2(0, 10);

		vertices[3].Position = D3DXVECTOR3(100, -3, 100);
		vertices[3].UV = D3DXVECTOR2(10, 10);

		// Describe the buffer and create it
		Framework::VertexBuffer::Description desc;
		desc.ElementCount = C_NUM_VERTICES;
		desc.ElementSize = sizeof(Vertex);
		desc.FirstElementPointer = vertices;
		desc.Topology = Framework::Topology::TriangleStrip;
		desc.Usage = Framework::Usage::Default;

		mBuffer = new Framework::VertexBuffer(mDevice);
		mBuffer->SetData(desc, NULL);

		// Create the effect and set up the input layout
		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Ground.fx");
		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);

		Resources::Texture* groundTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load("cobblestone.png");
		mEffect->SetVariable("g_modelTexture", groundTexture->GetShaderResoureceView());
	}

	void Environment::CreateWalls(Model::Level level)
	{
		mWallObject = Resources::D3DResourceManager<Resources::ModelObj>::Instance().Load("wallSegment.obj");
		mWallObject->SetScale(C_CELL_SIZE);

		const std::vector<Model::Coord> wallPosInGrid = level.GetWallPositions();

		for(int i = 0; i < wallPosInGrid.size(); ++i)
		{
			mWallPositions.push_back(D3DXVECTOR3(wallPosInGrid[i].X * C_CELL_SIZE, 0, wallPosInGrid[i].Y * C_CELL_SIZE));
		}

		//mWallPositions.push_back(D3DXVECTOR3(-30, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(-20, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(-10, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(0, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(10, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(20, 0, 0));
		//mWallPositions.push_back(D3DXVECTOR3(30, 0, 0));
	}

	void Environment::Draw(const Helper::Camera& camera)
	{
		D3DXMATRIX worldViewProjection, view, projection;		
		worldViewProjection = camera.GetViewProjection();

		mEffect->SetVariable("g_matWVP", worldViewProjection);

		// Bind and draw the buffer, once for each pass
		mBuffer->Bind();
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mBuffer->Draw();
		}

		mWallObject->Bind();
		for(int i = 0; i < mWallPositions.size(); ++i)
		{
			mWallObject->Draw(mWallPositions[i], camera);
		}
	}
}