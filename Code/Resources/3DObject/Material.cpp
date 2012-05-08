#include <fstream>
#include <sstream>
#include <cassert>
#include "Material.hpp"
#include "D3DResourceManager.hpp"

namespace Resources
{
	Material::Definition::Definition()
		: Ambient(D3DXVECTOR3(0.2, 0.2, 0.2)), Diffuse(D3DXVECTOR3(0.8, 0.8, 0.8))
		,  Specular(D3DXVECTOR3(1.0, 1.0, 1.0)), Tf(D3DXVECTOR3(1.0, 1.0, 1.0))
		,  IlluminationModel(0), /*Opacitiy(1.0),*/ RefractionIndex(1.0)
		/*,  SpecularExp(), Sharpness(60.0)*/, MainTexture(NULL)
	{}

	Material::Material()
	{
		Materials["default"] = Definition();
	}

	Material::Material(const std::string& filename)
	{
		Definition currMaterial;
		std::string currMaterialName = "";
		std::ifstream file;
		file.open(filename.c_str(), std::ios_base::in);
	
		if(!file.is_open())
			return;

		while(!file.eof())
		{
			// Read first line of file.
			std::string line;
			std::getline(file, line);

			// Copy line to a stringstream and copy first word into string key
			std::stringstream streamLine;
			std::string key;

			streamLine.str(line);
			streamLine >> key;

			if(key == "newmtl")
			{
				if(currMaterialName != "") // It is not the first material read
				{
					// Save previous material, making sure the material does not already exist in Materials
					assert(Materials.find(currMaterialName) == Materials.end());
					Materials[currMaterialName] = currMaterial;
				}

				// Set new material name and clear current material
				streamLine >> currMaterialName;
				currMaterial = Definition();
			}
			else if(key == "Ka") // Ambient color
			{
				streamLine >> currMaterial.Ambient.x;
				streamLine >> currMaterial.Ambient.y;
				streamLine >> currMaterial.Ambient.z;
			}
			else if(key == "Kd") // Diffuse color
			{
				streamLine >> currMaterial.Diffuse.x;
				streamLine >> currMaterial.Diffuse.y;
				streamLine >> currMaterial.Diffuse.z;
			}
			else if(key == "Ks") // Specular color
			{
				streamLine >> currMaterial.Specular.x;
				streamLine >> currMaterial.Specular.y;
				streamLine >> currMaterial.Specular.z;
			}
			else if(key == "Tf") // Transmission filter
			{
				streamLine >> currMaterial.Tf.x;
				streamLine >> currMaterial.Tf.y;
				streamLine >> currMaterial.Tf.z;
			}
			else if(key == "illum") // Illumination model
			{
				streamLine >> currMaterial.IlluminationModel;
			}
			//else if(key == "d" || key == "Tr") // Opacity
			//{
			//	streamLine >> currMaterial.Opacitiy;
			//}
			else if(key == "Ni") // Optical density
			{
				streamLine >> currMaterial.RefractionIndex;
			}
			//else if(key == "Ns") // Specular exponent
			//{
			//	streamLine >> currMaterial.SpecularExp;
			//}
			//else if(key == "sharpness") // Reflection sharpness
			//{
			//	streamLine >> currMaterial.Sharpness;
			//}
			else if(key == "map_Ka" || key == "map_Kd" || key == "map_Ks")
			{
				// Get the next argument on the line
				std::string textureFilename;
				streamLine >> textureFilename;

				// Make sure there is a period in the name indicating a file name. The other
				// arguments are not interesting at this point.
				while (textureFilename.find('.') == std::string::npos && !streamLine.eof())
				{
					streamLine >> textureFilename;
				}

				// Only try to load the texture if a filename was read
				if(textureFilename.find('.') != std::string::npos)
					currMaterial.MainTexture = D3DResourceManager<Texture>::Instance().Load(textureFilename);
			}
		}

		if(currMaterialName != "") // It is not the first material read
		{
			// Save previous material, making sure the material does not already exist in Materials
			assert(Materials.find(currMaterialName) == Materials.end());
			Materials[currMaterialName] = currMaterial;
		}
	}

	const Material::Definition* Material::GetMaterial(const std::string& materialName) const
	{
		if(Materials.find(materialName) == Materials.end())
			return NULL;
		else
			return &Materials.find(materialName)->second;
	}
}