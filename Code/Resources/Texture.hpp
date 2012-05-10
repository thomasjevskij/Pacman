#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "Global.hpp"

namespace Resources
{
	class Texture
	{
	public:
		Texture(ID3D10Device* device, const std::string& filename);
		~Texture() throw();

		ID3D10ShaderResourceView* GetShaderResourceView();
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
	private:
		ID3D10ShaderResourceView* mTexture;
		D3DX10_IMAGE_INFO mImageInfo;

		Texture(const Texture&);
		Texture& operator=(const Texture&);
	};
}
#endif