#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Global.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"

namespace View
{
	class Sprite
	{
	public:
		Sprite(ID3D10Device* device, const std::string& filename);
		~Sprite() throw();

		// Draw the sprite at the given position with the given tint.
		// The position should be in normalized space coordinates.
		void Draw(const D3DXVECTOR2& position, const D3DXCOLOR& tintColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

		// Get the texture associated with this sprite
		Resources::Texture* GetTexture();

		// Get/Set the model matrix for the sprite
		const D3DXMATRIX& GetModelMatrix() const;
		void SetScale(float scale);
		void SetPosition(const D3DXVECTOR2& position);

		// Get/Set the tint color of the sprite
		void SetTintColor(const D3DXCOLOR& color);
		const D3DXCOLOR& GetTintColor() const;
	private:
		ID3D10Device* mDevice;
		Resources::Texture*	mTexture;
		D3DXMATRIX mModelMatrix;
		D3DXCOLOR mTintColor;
	};
}

#endif