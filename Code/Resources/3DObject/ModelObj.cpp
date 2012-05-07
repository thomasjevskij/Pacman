#include "ModelObj.hpp"

#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>

#include "FileResourceManager.hpp"
#include "D3DResourceManager.hpp"
#include "r2-exception.hpp"

namespace Resources
{
	ModelObj::ModelObj(ID3D10Device* device, const std::string& filename)
		: mDevice(device)
		, mData(device, filename)
		, mEffect(NULL)
		, mScale(1.0f)
	{
		mEffect = D3DResourceManager<Framework::Effect>::Instance().Load("ModelObj.fx");

		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);
	}

	ModelObj::~ModelObj() throw()
	{}


	void ModelObj::Bind(unsigned int slot)
	{
		mData.VertexData.Bind(slot);
	}

	void ModelObj::Draw(const D3DXVECTOR3& drawPosition, const Helper::Camera& camera)
	{
		// Calculate the world matrix. Use worldViewProjection as temporary storage. Think green.
		D3DXMATRIX world;
		D3DXMATRIX worldViewProjection;
		D3DXMatrixTranslation(&world, drawPosition.x, drawPosition.y, drawPosition.z);
		D3DXMatrixScaling(&worldViewProjection, mScale, mScale, mScale);
		world *= worldViewProjection;

		// Calculate the REAL worldViewProjection.
		worldViewProjection = world * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", world);
		mEffect->SetVariable("g_matWVP", worldViewProjection);
		
		// DEBUG: get light position elsewhere
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(50, 50, 0, 0));

		// Draw the buffer, once for each pass
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mData.VertexData.GetElementCount(), 0);
		}
	}

	void ModelObj::SetScale(float newScale)
	{
		mScale = newScale;
	}




	/*
	ModelObj::ModelObj(ID3D10Device* device, const std::string& filename)
		: mMaterial(NULL), mDevice(device), mEffect(NULL), mBuffer(NULL)
	{
		D3DXMatrixIdentity(&mWorld);

		if(!Load(filename))
			return;
	}

	ModelObj::~ModelObj() throw()
	{
		SafeDelete(mBuffer);
	}

	bool ModelObj::Load(const std::string& filename)
	{
		

		// Describe the buffer and create it
		

		// Create the effect and set up the input layout
		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("ModelObj.fx");
		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);
		
		const Material::Definition* def = mMaterial->GetMaterial(mMaterialName);
		if(def != NULL)
			if(def->MainTexture != NULL)
				mEffect->SetVariable("g_modelTexture", def->MainTexture->GetShaderResoureceView());

		return true;
	}

	bool ModelObj::LoadMaterial(const std::string& filename)
	{
		mMaterial = FileResourceManager<Material>::Instance().Load(filename);

		return mMaterial->Materials.size() > 0;
	}

	void ModelObj::Bind(unsigned int slot) 
	{
		mBuffer->Bind(slot);
	}

	void ModelObj::Draw(const D3DXVECTOR3& drawPosition, const Helper::Camera& camera)
	{
		UpdatePositionInMatrix(drawPosition);
		D3DXMATRIX worldViewProjection, view, projection;
		worldViewProjection = mWorld * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", mWorld);
		mEffect->SetVariable("g_matWVP", worldViewProjection);
		
		// DEBUG: get light position elsewhere
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(50, 50, 0, 0));

		// Draw the buffer, once for each pass
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mBuffer->Draw();
		}
	}

	void ModelObj::SetScale(float newScale)
	{
		mWorld.m[0][0] = newScale;
		mWorld.m[1][1] = newScale;
		mWorld.m[2][2] = newScale;
	}

	void ModelObj::UpdatePositionInMatrix(const D3DXVECTOR3& position)
	{
		// Update position in matrix
		mWorld.m[3][0] = position.x;
		mWorld.m[3][1] = position.y;
		mWorld.m[3][2] = position.z;
	}
	*/
}