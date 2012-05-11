#include "Texture.hpp"
#include "r2-exception.hpp"

namespace Resources
{
	Texture::Texture(ID3D10Device* device, const std::string& filename)
		: mTexture(NULL)
	{
		if (FAILED(D3DX10CreateShaderResourceViewFromFile(device, filename.c_str(), NULL, NULL, &mTexture, NULL)))
			throw r2ExceptionIOM("Failed to load texture: " + filename);

		if (FAILED(D3DX10GetImageInfoFromFile(filename.c_str(), NULL, &mImageInfo, NULL)))
			throw r2ExceptionIOM("Failed to load texture information: " + filename);
	}

	Texture::~Texture() throw()
	{
		SafeRelease(mTexture);
	}

	ID3D10ShaderResourceView* Texture::GetShaderResourceView()
	{
		return mTexture;
	}

	unsigned int Texture::GetWidth() const
	{
		return mImageInfo.Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return mImageInfo.Height;
	}
}