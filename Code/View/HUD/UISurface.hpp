#ifndef UISURFACE_HPP
#define UISURFACE_HPP

#include "Sprite.hpp"

namespace View
{
	class UISurface
	{
	public:
		UISurface(ID3D10Device* device);
		~UISurface() throw();

		void Draw(const Sprite& sprite);
	private:
		struct SpriteVertex
		{
			D3DXVECTOR2	Position;
			D3DXVECTOR2	UV;
		};

		ID3D10Device* mDevice;
		ID3D10Texture2D* mOverlayTexture;
		ID3D10RenderTargetView* mOverlayTarget;

		Framework::Effect* mSpriteEffect;
		Framework::VertexBuffer* mSpriteBuffer;

		void CreateSpriteEffect();
		void CreateSpriteBuffer();
	};
}

#endif