#include "ModelObj.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>

#include "FileResourceManager.hpp"

namespace Resources
{
	Material::Definition::Definition()
		: Ambient(D3DXVECTOR3(0.2, 0.2, 0.2)), Diffuse(D3DXVECTOR3(0.8, 0.8, 0.8))
		,  Specular(D3DXVECTOR3(1.0, 1.0, 1.0)), Tf(D3DXVECTOR3(1.0, 1.0, 1.0))
		,  IlluminationModel(0), /*Opacitiy(1.0),*/ RefractionIndex(1.0)
		//,  SpecularExp(), Sharpness(60.0)
	{}

	Material::Material(std::string filename)
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
				// TODO: Add Textures
			}
		}

		if(currMaterialName != "") // It is not the first material read
		{
			// Save previous material, making sure the material does not already exist in Materials
			assert(Materials.find(currMaterialName) == Materials.end());
			Materials[currMaterialName] = currMaterial;
		}
	}
}

namespace Resources
{
	ModelObj::ModelObj(std::string filename)
	{
		if(!Load(filename))
			return;
	}

	ModelObj::~ModelObj() throw()
	{
	}

	bool ModelObj::Load(std::string filename)
	{
		std::ifstream file;
		std::vector<D3DXVECTOR3> outPositions;
		std::vector<D3DXVECTOR2> outUVCoords;
		std::vector<D3DXVECTOR3> outNormals;
		std::vector<Vertex> vertices;
	
		file.open(filename.c_str(), std::ios_base::in);
	
		if(!file.is_open())
			return false;

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

			if(key == "v")
			{
				D3DXVECTOR3 currPos;
				streamLine >> currPos.x;
				streamLine >> currPos.y;
				streamLine >> currPos.z;
				outPositions.push_back(currPos);
			}
			else if(key == "vt")
			{
				D3DXVECTOR2 currUV;
				streamLine >> currUV.x;
				streamLine >> currUV.y;
				currUV.y = 1 - currUV.y;
				outUVCoords.push_back(currUV);
			}
			else if(key == "vn")
			{
				D3DXVECTOR3 currNormal;
				streamLine >> currNormal.x;
				streamLine >> currNormal.y;
				streamLine >> currNormal.z;
				outNormals.push_back(currNormal);
			}
			else if(key == "f")
			{
				int pos[3]; 
				int uv[3];
				int norm[3];

				for(int i = 0; i < 3; ++i)
				{
					streamLine >> pos[i];
					streamLine.ignore();
					streamLine >> uv[i];
					streamLine.ignore();
					streamLine >> norm[i];

					Vertex currVertex;
					currVertex.Position = outPositions[pos[i] - 1];
					currVertex.UV = outUVCoords[uv[i] - 1];
					currVertex.Normal = outNormals[norm[i] - 1];
					vertices.push_back(currVertex);
				}
			}
			else if(key == "mtllib")
			{
				std::string matFile;
				streamLine >> matFile;

				if(!LoadMaterial(matFile))
				{
					// Material was not loaded
					// TODO: error checking?
				}
			}
		}

		return true;
	}

	bool ModelObj::LoadMaterial(std::string filename)
	{
		objectMaterial = FileResourceManager<Material>::Instance().Load(filename);

		return objectMaterial->Materials.size() > 0;
	}
}