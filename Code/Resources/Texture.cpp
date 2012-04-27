#include "Texture.hpp"

namespace Resources
{
	Texture::Texture(ID3D10Device* device, std::string filename)
		: texture(NULL)
	{
		D3DX10CreateShaderResourceViewFromFile(device, filename.c_str(), NULL, NULL, &texture, NULL );
	}

	Texture::~Texture() throw()
	{
		SafeRelease(texture);
	}

	ID3D10ShaderResourceView* Texture::GetShaderResoureceView()
	{
		return texture;
	}
}