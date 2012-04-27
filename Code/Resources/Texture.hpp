#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "Global.hpp"

namespace Resources
{
	class Texture
	{
	public:
		Texture(ID3D10Device* device, std::string filename);
		~Texture() throw();

		ID3D10ShaderResourceView* GetShaderResoureceView();

	private:
		ID3D10ShaderResourceView* texture;

		Texture(const Texture&);
		Texture& operator=(const Texture&);
	};
}
#endif