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
		struct UVCoordinates
		{
			UVCoordinates();

			float U;
			float V;
			float Width;
			float Height;
		};

		// Create a sprite from the given texture file.
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

		// Get/Set the UV coordinates. Defines, in normalized coordinates, what
		// part of the texture the sprite will use.
		void SetUVCoordinates(float u, float v, float width, float height);
		UVCoordinates GetUVCoordinates() const;
	private:
		Resources::Texture*	mTexture;
		
		UVCoordinates mUVCoordinates;
		float mScale;
		D3DXVECTOR2 mPosition;
		D3DXCOLOR mTintColor;
	};
}

#endif