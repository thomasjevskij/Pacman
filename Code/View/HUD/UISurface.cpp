#include "UISurface.hpp"
#include "D3DResourceManager.hpp"

namespace View
{
	UISurface::UISurface(ID3D10Device* device)
		: mDevice(device)
		, mSpriteEffect(NULL)
		, mSpriteBuffer(NULL)
	{
		CreateSpriteBuffer();
		CreateSpriteEffect();
	}

	UISurface::~UISurface() throw()
	{
		SafeDelete(mSpriteBuffer);
	}

	void UISurface::Clear()
	{
		// Clear all buffered sprite copies
		mBufferedSprites.clear();
	}

	void UISurface::Draw(const Sprite& sprite)
	{
		// Save a copy of the sprite for buffering
		mBufferedSprites.push_back(sprite);
	}

	void UISurface::DrawSurface(const Framework::D3DContext& context)
	{
		// Draw all the buffered sprites to the surface
		mSpriteBuffer->Bind();
		for (int i = 0; i < mBufferedSprites.size(); ++i)
		{
			DrawSpriteToViewport(mBufferedSprites[i], context);
		}
	}

	void UISurface::CreateSpriteEffect()
	{
		mSpriteEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("Sprite.fx");

		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT));

		mSpriteEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);
	}

	void UISurface::CreateSpriteBuffer()
	{
		SpriteVertex vertices[4];
			
		vertices[0].Position = D3DXVECTOR2(0, 0);
		vertices[0].UV = D3DXVECTOR2(0, 1);

		vertices[1].Position = D3DXVECTOR2(0, 1);
		vertices[1].UV = D3DXVECTOR2(0, 0);

		vertices[2].Position = D3DXVECTOR2(1, 0);
		vertices[2].UV = D3DXVECTOR2(1, 1);

		vertices[3].Position = D3DXVECTOR2(1, 1);
		vertices[3].UV = D3DXVECTOR2(1, 0);

		mSpriteBuffer = new Framework::VertexBuffer(mDevice);
		Framework::VertexBuffer::Description bufferDesc;

		bufferDesc.Usage =					Framework::Usage::Default;
		bufferDesc.Topology =				Framework::Topology::TriangleStrip;
		bufferDesc.ElementCount =			4;
		bufferDesc.ElementSize =			sizeof(SpriteVertex);
		bufferDesc.FirstElementPointer	=	vertices;

		mSpriteBuffer->SetData(bufferDesc, NULL);
	}

	void UISurface::DrawSpriteToViewport(const Sprite& sprite, const Framework::D3DContext& context)
	{
		float viewportWidth = static_cast<float>(context.GetViewportWidth(context.GetActiveViewport()));
		float viewportHeight = static_cast<float>(context.GetViewportHeight(context.GetActiveViewport()));
		
		float scaleX = sprite.GetScale() * static_cast<float>(sprite.GetTexture()->GetWidth()) / viewportWidth;
		float scaleY = sprite.GetScale() * static_cast<float>(sprite.GetTexture()->GetHeight()) / viewportHeight;
		float posX = (2.0f * sprite.GetPosition().x / viewportWidth) - 1.0f;
		float posY = (2.0f * sprite.GetPosition().y / viewportHeight) - 1.0f;

		D3DXMATRIX scale, translation, model;
		D3DXMatrixScaling(&scale, scaleX, scaleY, 1.0f);
		D3DXMatrixTranslation(&translation, posX, posY, 1.0f);
		model = scale * translation;

		mSpriteEffect->SetVariable("gTintColor", static_cast<D3DXVECTOR4>(sprite.GetTintColor()) );
		mSpriteEffect->SetVariable("gModel", model);
		mSpriteEffect->SetVariable("gImage", sprite.GetTexture()->GetShaderResourceView());

		for (unsigned int p = 0; p < mSpriteEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mSpriteEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mSpriteBuffer->GetElementCount(), 0);
		}
	}
}