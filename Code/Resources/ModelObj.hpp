#ifndef MODELOBJ_HPP
#define MODELOBJ_HPP

#include <string>
#include <map>

#include "Global.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"

namespace Resources
{
	// Material
	// Defines the properties of a material and keeps a list of its textures.
	struct Material
	{
		struct Definition
		{
			D3DXVECTOR3 Ambient;		// Ka coefficient, default (0.2, 0.2, 0.2)
			D3DXVECTOR3 Diffuse;		// Kd coefficient, default (0.8, 0.8, 0.8)
			D3DXVECTOR3 Specular;		// Ks coefficient, default (1.0, 1.0, 1.0)
			D3DXVECTOR3 Tf;				// Transmission filter, how much of each color to pass through
			int IlluminationModel;		// illum, 0-10
			//float Opacitiy;				// d or Tr, 1.0-> fully opaque, 0.0-> fully transparent
			float RefractionIndex;		// Ni, optical density, (0.001)1.0-10.0, 1.0-> light doesn't bend
			//float SpecularExp;			// Ns, ~0-1000, High value-> concentrated highlight
			//float Sharpness;			// Sharpness of reflections, 0-1000, default 60.0
			// Textures

			Definition();
		};

		std::map<std::string, Definition> Materials;

		Material(std::string filename);
	};

	class ModelObj
	{
	public:
		ModelObj(std::string filename);
		~ModelObj() throw();

	private:
		// The struct for a vertex in the object. 
		// The vertex has a position, a texture coordinate and a normal
		struct Vertex
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Normal;
			D3DXVECTOR2	UV;
		};

		Material* objectMaterial;

		ModelObj(const ModelObj&);
		ModelObj& operator=(const ModelObj&);

		bool Load(std::string filename);
		bool LoadMaterial(std::string filename);
	};
}
#endif