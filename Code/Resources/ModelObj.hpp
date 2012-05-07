#ifndef MODELOBJ_HPP
#define MODELOBJ_HPP

#include <string>
#include <map>

#include "Global.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "Effect.hpp"
#include "Camera.hpp"

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
			Texture* MainTexture;		// Texture that can be sent to the shaders

			Definition();
		};

		std::map<std::string, Definition> Materials;

		Material(std::string filename);
		
		const Definition* GetMaterial(std::string materialName) const;
	};



	class ModelObj
	{
	public:
		ModelObj(ID3D10Device* device, const std::string& filename);
		~ModelObj() throw();

		// Bind the model's associated vertex buffer to an input slot
		void Bind(unsigned int slot = 0);

		// Draw the object. Must be bound to an input slot.
		void Draw(const D3DXVECTOR3& drawPosition, const Helper::Camera& camera);

		void SetScale(float newScale);

	private:
		// The struct for a vertex in the object. 
		// The vertex has a position, a texture coordinate and a normal
		struct Vertex
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Normal;
			D3DXVECTOR2	UV;
		};

		Material* mMaterial;
		std::string mMaterialName;
		ID3D10Device* mDevice;
		Framework::Effect* mEffect;
		Framework::VertexBuffer* mBuffer;
		D3DXMATRIX mWorld;

		ModelObj(const ModelObj&);
		ModelObj& operator=(const ModelObj&);

		bool Load(const std::string& filename);
		bool LoadMaterial(const std::string& filename);
		void UpdatePositionInMatrix(const D3DXVECTOR3& position);
	};
}
#endif