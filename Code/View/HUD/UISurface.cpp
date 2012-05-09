#include "UISurface.hpp"

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
		
	}

	void UISurface::CreateSpriteEffect()
	{
		
	}

	void UISurface::CreateSpriteBuffer()
	{

	}
}