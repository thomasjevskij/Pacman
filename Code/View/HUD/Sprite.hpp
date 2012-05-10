#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include "Global.hpp"
#include "Texture.hpp"

namespace View
{
	class Sprite
	{
	public:
		Sprite(const std::string& filename);

		// Get the texture associated with this sprite
		Resources::Texture* GetTexture() const;

		// Get/Set the uniform scale of the sprite
		void SetScale(float scale);
		float GetScale() const;

		// Get/Set the position of the sprite, with the origin
		// in the upper-left corner.
		void SetPosition(const D3DXVECTOR2& position);
		const D3DXVECTOR2& GetPosition() const;

		// Get/Set the tint color of the sprite
		void SetTintColor(const D3DXCOLOR& color);
		const D3DXCOLOR& GetTintColor() const;
	private:
		Resources::Texture*	mTexture;
		float mScale;
		D3DXVECTOR2 mPosition;
		D3DXCOLOR mTintColor;
	};
}

#endif