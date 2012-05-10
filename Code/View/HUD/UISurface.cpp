#include "UISurface.hpp"
#include "D3DResourceManager.hpp"

namespace View
{
	UISurface::UISurface(ID3D10Device* device)
		: mDevice(device)
		, mOverlayTexture(NULL)
		, mOverlayTarget(NULL)
		, mSpriteEffect(NULL)
		, mSpriteBuffer(NULL)
	{
		CreateSpriteBuffer();
		CreateSpriteEffect();
	}

	UISurface::~UISurface() throw()
	{
		SafeDelete(mSpriteBuffer);
		SafeDelete(mSpriteEffect);
		SafeRelease(mOverlayTarget);
		SafeRelease(mOverlayTexture);
	}

	void UISurface::Draw(const Sprite& sprite)
	{
		// Save a copy of the sprite for buffering
		mBufferedSprites.push_back(sprite);
	}

	void UISurface::DrawSurface(const D3DXVECTOR2& position, const Framework::D3DContext& context)
	{
		// Draw all the buffered sprites to the surface
		for (int i = 0; i < mBufferedSprites.size(); ++i)
		{
			DrawSpriteToSurface(mBufferedSprites[i], context);
		}

		// TODO: Draw the surface to the current render target
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

	void UISurface::DrawSpriteToSurface(const Sprite& sprite, const Framework::D3DContext& context)
	{
		D3DXMATRIX scale;
		D3DXMATRIX translation;
		float scaleX = static_cast<float>( sprite.GetTexture()->GetWidth() ) / static_cast<float>( context.GetViewportWidth(context.GetActiveViewport()) );
		float scaleY = static_cast<float>( sprite.GetTexture()->GetHeight() ) / static_cast<float>( context.GetViewportHeight(context.GetActiveViewport()) );

		D3DXMatrixScaling(&scale, sprite.GetScale() * scaleX, sprite.GetScale() * scaleY, 1.0f);
		//D3DXMatrixTranslation(&translation, 

		mSpriteEffect->SetVariable("gTintColor", static_cast<D3DXVECTOR4>(sprite.GetTintColor()) );
		mSpriteEffect->SetVariable("gModel", model);
		mSpriteEffect->SetVariable("gImage", sprite.GetTexture()->GetShaderResourceView());

		mSpriteBuffer->Bind();
		for (unsigned int p = 0; p < mSpriteEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mSpriteEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mDevice->Draw(mSpriteBuffer->GetElementCount(), 0);
		}
	}
}