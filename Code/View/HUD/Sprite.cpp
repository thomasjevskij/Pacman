#include "Sprite.hpp"
#include "r2-exception.hpp"
#include "D3DResourceManager.hpp"
#include <sstream>

namespace View
{
	Sprite::Sprite(ID3D10Device* device, const std::string& filename)
		: mDevice(device)
		, mTexture(NULL)
	{
		mTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load(filename);

		/*CreateBuffer();
		CreateEffect();*/

		//mEffect->SetVariable("gImage", mTexture->GetShaderResourceView());
	}

	Sprite::~Sprite() throw()
	{

	}

	//void Sprite::CreateBuffer()
	//{
	//	const int numVertices = 4;
	//	SpriteVertex vertices[numVertices];
	//	
	//	vertices[0].Position = D3DXVECTOR2(0, 0);
	//	vertices[0].UV = D3DXVECTOR2(0, 1);

	//	vertices[1].Position = D3DXVECTOR2(0, mTexture->GetHeight());
	//	vertices[1].UV = D3DXVECTOR2(0, 0);

	//	vertices[2].Position = D3DXVECTOR2(mTexture->GetWidth(), 0);
	//	vertices[2].UV = D3DXVECTOR2(1, 1);

	//	vertices[3].Position = D3DXVECTOR2(mTexture->GetWidth(), mTexture->GetHeight());
	//	vertices[3].UV = D3DXVECTOR2(1, 0);

	//	mBuffer = new Framework::VertexBuffer(mDevice);
	//	Framework::VertexBuffer::Description bufferDesc;

	//	bufferDesc.Usage =					Framework::Usage::Default;
	//	bufferDesc.Topology =				Framework::Topology::TriangleStrip;
	//	bufferDesc.ElementCount =			numVertices;
	//	bufferDesc.ElementSize =			sizeof(SpriteVertex);
	//	bufferDesc.FirstElementPointer	=	vertices;

	//	mBuffer->SetData(bufferDesc, NULL);
	//}

	//void Sprite::CreateEffect()
	//{
	//	mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Sprite.fx");

	//	Framework::InputLayoutVector inputLayout;
	//	inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32_FLOAT));
	//	inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

	//	mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);
	//}

	//void Sprite::Draw(const D3DXVECTOR2& position, const D3DXCOLOR& tintColor)
	//{
	//	D3DXMATRIX model;
	//	D3DXMatrixIdentity(&model);
	//	D3DXMatrixTranslation(&model, position.x, position.y, 0.0f);
	//	
	//	mEffect->SetVariable("gModel", model);
	//	mEffect->SetVariable("gTintColor", (D3DXVECTOR4)tintColor);
	//
	//	mBuffer->Bind();
	//	for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
	//	{
	//		mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
	//		mDevice->Draw(mBuffer->GetElementCount(), 0);
	//	}
	//}

	// Get the texture associated with this sprite
	Resources::Texture* Sprite::GetTexture()
	{
		return mTexture;
	}

	// Get/Set the model matrix for the sprite
	const D3DXMATRIX& Sprite::GetModelMatrix() const
	{
		return mModelMatrix;
	}

	void Sprite::SetScale(float scale)
	{

	}

	void Sprite::SetPosition(const D3DXVECTOR2& position)
	{
		mModelMatrix._14 = position.x;
		mModelMatrix._24 = position.y;
		mModelMatrix._34 = 0.0f;
	}



	void Sprite::SetTintColor(const D3DXCOLOR& color)
	{
		mTintColor = color;
	}

	const D3DXCOLOR& Sprite::GetTintColor() const
	{
		return mTintColor;
	}
}