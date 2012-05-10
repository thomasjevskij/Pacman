#include "Sprite.hpp"
#include "r2-exception.hpp"
#include "D3DResourceManager.hpp"
#include <sstream>

namespace View
{
	Sprite::Sprite(const std::string& filename)
		: mTexture(NULL)
	{
		mTexture = Resources::D3DResourceManager<Resources::Texture>::Instance().Load(filename);
	}

	Resources::Texture* Sprite::GetTexture() const
	{
		return mTexture;
	}

	void Sprite::SetScale(float scale)
	{
		mScale = scale;
	}

	float Sprite::GetScale() const
	{
		return mScale;
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