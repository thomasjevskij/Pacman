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
		, mEffect(NULL)
		, mScale(1.0f)
		, mTintColour(D3DXCOLOR(1.0, 1.0, 1.0, 1.0))
	{
		mEffect = D3DResourceManager<Framework::Effect>::Instance().Load("ModelObj.fx");

		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);

		//mData = Resources::ModelResourceManager::Instance().Load(filename);
		mData = Resources::D3DResourceManager<Resources::StaticModelData>::Instance().Load(filename);

		/*
		const Material::Definition* def = mData->MaterialData->GetMaterial(mData->MaterialName);
		if(def != NULL)
			if(def->MainTexture != NULL)
				mEffect->SetVariable("g_modelTexture", def->MainTexture->GetShaderResourceView());
			else
			{
				Resources::Texture* defaultTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load("whitePixel.png");
				mEffect->SetVariable("g_modelTexture", defaultTexture->GetShaderResourceView());
			}
		else
		{
			Resources::Texture* defaultTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load("whitePixel.png");
			mEffect->SetVariable("g_modelTexture", defaultTexture->GetShaderResourceView());
		}
		*/

		// Commented out to instead use above code that makes sure the texture exists, else loads the whitepixel texture
		//mEffect->SetVariable("g_modelTexture", mData->MaterialData->GetMaterial(mData->MaterialName)->MainTexture->GetShaderResourceView());
	}

	ModelObj::~ModelObj() throw()
	{}


	void ModelObj::Bind(unsigned int slot)
	{
		mData->VertexData.Bind(slot);
	}

	void ModelObj::Draw(const D3DXVECTOR3& drawPosition, const Helper::Camera& camera)
	{
		// Calculate the world matrix. Use worldViewProjection as temporary storage. Think green.
		D3DXMATRIX world;
		D3DXMATRIX worldViewProjection;
		D3DXMatrixScaling(&world, mScale, mScale, mScale);		
		D3DXMatrixTranslation(&worldViewProjection, drawPosition.x, drawPosition.y, drawPosition.z);
		world *= worldViewProjection;

		// Calculate the REAL worldViewProjection.
		worldViewProjection = world * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", world);
		mEffect->SetVariable("g_matWVP", worldViewProjection);
		mEffect->SetVariable("g_modelTintColour", static_cast<D3DXVECTOR4>(mTintColour));
		mEffect->SetVariable("g_modelTexture",mData->MaterialData->GetMaterial(mData->MaterialName)->MainTexture->GetShaderResourceView());
		
		// DEBUG: get light position elsewhere
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(50, 50, 0, 0));

		// Draw the buffer, once for each pass
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mData->VertexData.GetElementCount(), 0);
		}
	}

	void ModelObj::Draw(const D3DXMATRIX& modelMatrix, const Helper::Camera& camera)
	{
		D3DXMATRIX worldViewProjection;

		// Calculate the REAL worldViewProjection.
		worldViewProjection = modelMatrix * camera.GetViewProjection();

		mEffect->SetVariable("g_matWorld", modelMatrix);
		mEffect->SetVariable("g_matWVP", worldViewProjection);
		mEffect->SetVariable("g_modelTintColour", static_cast<D3DXVECTOR4>(mTintColour));
		mEffect->SetVariable("g_modelTexture",mData->MaterialData->GetMaterial(mData->MaterialName)->MainTexture->GetShaderResourceView());

		// DEBUG: get light position elsewhere
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(50, 50, 0, 0));

		// Draw the buffer, once for each pass
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mData->VertexData.GetElementCount(), 0);
		}
	}

	void ModelObj::SetScale(float newScale)
	{
		mScale = newScale;
	}

	void ModelObj::SetTintColour(D3DXCOLOR newColour)
	{
		mTintColour = newColour;
	}
}