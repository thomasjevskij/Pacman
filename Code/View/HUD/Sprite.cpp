#include "Sprite.hpp"
#include "r2-exception.hpp"
#include "D3DResourceManager.hpp"
#include <sstream>

namespace View
{
	Sprite::Sprite(const std::string& filename)
		: mTexture(NULL)
		, mScaleX(1.0f)
		, mScaleY(1.0f)
		, mPosition(0.0f, 0.0f)
		, mTintColor(1.0f, 1.0f, 1.0f, 1.0f)
	{
		mTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load(filename);
	}

	Resources::Texture* Sprite::GetTexture() const
	{
		return mTexture;
	}

	void Sprite::SetScale(float uniformScale)
	{
		mScaleX = uniformScale;
		mScaleY = uniformScale;
	}

	void Sprite::SetScale(float scaleX, float scaleY) 
	{
		mScaleX = scaleX;
		mScaleY = scaleY;
	}

	float Sprite::GetScaleX() const
	{
		return mScaleX;
	}

	float Sprite::GetScaleY() const
	{
		return mScaleY;
	}

	void Sprite::SetPosition(const D3DXVECTOR2& position)
	{
		mPosition = position;
	}

	const D3DXVECTOR2& Sprite::GetPosition() const
	{
		return mPosition;
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