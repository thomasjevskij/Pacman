#include "Sprite.hpp"
#include "r2-exception.hpp"
#include "D3DResourceManager.hpp"
#include <sstream>

namespace Resources
{
	Sprite::Sprite(ID3D10Device* device, const std::string& filename)
		: mDevice(device)
		, mBuffer(NULL)
		, mEffect(NULL)
	{
		ID3D10ShaderResourceView* texture;
		if (FAILED(D3DX10CreateShaderResourceViewFromFile(mDevice, filename.c_str(), NULL, NULL, &texture, NULL)))
			throw r2ExceptionIOM("Failed to load image: " + filename);

		if (FAILED(D3DX10GetImageInfoFromFile(filename.c_str(), NULL, &mImageInfo, NULL)))
			throw r2ExceptionIOM("Failed to load image information: " + filename);

		std::stringstream ss;
		ss << "Image loaded: " << filename << std::endl;
		ss << "Image width: " << mImageInfo.Width << std::endl;
		ss << "Image height: " << mImageInfo.Height << std::endl;

		OutputDebugString(ss.str().c_str());

		CreateBuffer();
		CreateEffect();

		mEffect->SetVariable("gImage", texture);
	}

	Sprite::~Sprite() throw()
	{
		SafeDelete(mBuffer);
	}

	void Sprite::CreateBuffer()
	{
		const int numVertices = 4;
		SpriteVertex vertices[numVertices];
		
		vertices[0].Position = D3DXVECTOR2(0, 0);
		vertices[0].UV = D3DXVECTOR2(0, 1);

		vertices[1].Position = D3DXVECTOR2(0, mImageInfo.Width);
		vertices[1].UV = D3DXVECTOR2(0, 0);

		vertices[2].Position = D3DXVECTOR2(mImageInfo.Width, 0);
		vertices[2].UV = D3DXVECTOR2(1, 1);

		vertices[3].Position = D3DXVECTOR2(mImageInfo.Width, mImageInfo.Height);
		vertices[3].UV = D3DXVECTOR2(1, 0);

		mBuffer = new Framework::VertexBuffer(mDevice);
		Framework::VertexBuffer::Description bufferDesc;

		bufferDesc.Usage =					Framework::Usage::Default;
		bufferDesc.Topology =				Framework::Topology::TriangleStrip;
		bufferDesc.ElementCount =			numVertices;
		bufferDesc.ElementSize =			sizeof(SpriteVertex);
		bufferDesc.FirstElementPointer	=	vertices;

		mBuffer->SetData(bufferDesc, NULL);
	}

	void Sprite::CreateEffect()
	{
		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Sprite.fx");

		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);
	}

	void Sprite::Draw(const D3DXVECTOR2& position, const D3DXCOLOR& tintColor)
	{
		D3DXMATRIX model;
		D3DXMatrixIdentity(&model);
		D3DXMatrixTranslation(&model, position.x, position.y, 0.0f);
		
		mEffect->SetVariable("gModel", model);
		mEffect->SetVariable("gTintColor", (D3DXVECTOR4)tintColor);
	
		mBuffer->Bind();
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mBuffer->GetElementCount(), 0);
		}
	}



	SpriteResourceManager::SpriteResourceManager(const std::string& path, ID3D10Device* device)
		: mPath(path)
		, mDevice(device)
	{}

	Sprite* SpriteResourceManager::Load(const std::string& filename)
	{
		Sprite* resource = GetResource(filename);

		if (resource == NULL)
		{
			resource = new Sprite(mDevice, mPath + filename);
			AddResource(filename, resource);
		}

		return resource;
	}
}