#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Global.hpp"
#include "D3DContext.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"

namespace Resources
{
	class Sprite
	{
	public:
		Sprite(ID3D10Device* device, const std::string& filename, float width, float height);
		~Sprite() throw();

		// Draw the sprite at the given position with the given tint.
		// The position should be in normalized space coordinates.
		void Draw(const D3DXVECTOR2& position, const D3DXCOLOR& tintColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	private:
		struct SpriteVertex
		{
			D3DXVECTOR2				Position;
			D3DXVECTOR2				UV;
		};

		ID3D10Device*				mDevice;
		Framework::VertexBuffer*	mBuffer;
		Framework::Effect*			mEffect;
		float						mWidth;
		float						mHeight;

		void CreateBuffer();
		void CreateEffect();
	};

	class SpriteResourceManager : public r2::Singleton<SpriteResourceManager>, public Private::ResourceManager<Sprite>
	{
	public:
		SpriteResourceManager(const std::string& path, ID3D10Device* device);

		Sprite* Load(const std::string& filename, float width, float height);
	private:
		ID3D10Device* mDevice;
		std::string mPath;
	};
}

#endif