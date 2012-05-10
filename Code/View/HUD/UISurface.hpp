#ifndef UISURFACE_HPP
#define UISURFACE_HPP

#include "Sprite.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"
#include "D3DContext.hpp"

namespace View
{
	class UISurface
	{
	public:
		UISurface(ID3D10Device* device);
		~UISurface() throw();

		// Clear all buffered sprites
		void Clear();

		// Buffer a sprite up for rendering to the surface
		void Draw(const Sprite& sprite);

		// Draw all buffered sprites and then render the surface to the
		// current render target.
		void DrawSurface(const Framework::D3DContext& context);
	private:
		struct SpriteVertex
		{
			D3DXVECTOR2	Position;
			D3DXVECTOR2	UV;
		};


		ID3D10Device* mDevice;

		Framework::Effect* mSpriteEffect;
		Framework::VertexBuffer* mSpriteBuffer;

		std::vector<Sprite> mBufferedSprites;


		void CreateSpriteEffect();
		void CreateSpriteBuffer();
		void DrawSpriteToViewport(const Sprite& sprite, const Framework::D3DContext& context);

		// Disable copying
		UISurface(const UISurface&);
		UISurface& operator=(const UISurface&);
	};
}

#endif