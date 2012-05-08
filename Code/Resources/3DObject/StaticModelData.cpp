#include <sstream>
#include <fstream>
#include <cassert>
#include "StaticModelData.hpp"
#include "FileResourceManager.hpp"
#include "r2-exception.hpp"


namespace Resources
{
	StaticModelData::StaticModelData(ID3D10Device* device, const std::string& objectFilename)
		: VertexData(device)
	{
		if (!Load(objectFilename))
			throw r2ExceptionIOM("Failed to load object/material file: " + objectFilename);
	}

	StaticModelData::StaticModelData(ID3D10Device* device, const std::string& objectFilename, const std::string& materialFilename)
		: VertexData(device)
	{
		if (!LoadBuffer(objectFilename))
			throw r2ExceptionIOM("Failed to load object file: " + objectFilename);
		if (!LoadMaterial(materialFilename))
			throw r2ExceptionIOM("Failed to load material file: " + objectFilename);
	}

	bool StaticModelData::Load(const std::string& objectFilename)
	{
		std::string materialFile;

		if (!LoadObjectFile(objectFilename, materialFile, MaterialName))
			return false;
		return LoadMaterial(materialFile);
	}

	bool StaticModelData::LoadBuffer(const std::string& filename)
	{
		std::string materialFile;
		std::string materialName;

		return LoadObjectFile(filename, materialFile, materialName);
	}

	bool StaticModelData::LoadMaterial(const std::string& filename)
	{
		MaterialData = FileResourceManager<Material>::Instance().Load(filename);
		return MaterialData != NULL;
	}

	bool StaticModelData::LoadObjectFile(const std::string& filename,
										 std::string& materialFile, 
										 std::string& materialName)
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

			if(key == "mtllib")
			{
				streamLine >> materialFile;
			}
			else if(key == "v")
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
			else if(key == "usemtl")
			{
				streamLine >> materialName;
			}
		}

		Framework::VertexBuffer::Description desc;
		desc.ElementCount = vertices.size();
		desc.ElementSize = sizeof(Vertex);
		desc.FirstElementPointer = &vertices[0];
		desc.Topology = Framework::Topology::TriangleList;
		desc.Usage = Framework::Usage::Default;

		return VertexData.SetData(desc, NULL);
	}




	ModelResourceManager::ModelResourceManager(const std::string& path, ID3D10Device* device)
		: mPath(path)
		, mDevice(device)
	{}

	StaticModelData* ModelResourceManager::Load(const std::string& objectFilename)
	{
		StaticModelData* resource = GetResource(objectFilename);

		if (resource == NULL)
		{
			resource = new StaticModelData(mDevice, mPath + objectFilename);
			AddResource(objectFilename, resource);
		}

		return resource;
	}

	StaticModelData* ModelResourceManager::Load(const std::string& objectFilename, const std::string& materialFilename)
	{
		StaticModelData* resource = GetResource(objectFilename);

		if (resource == NULL)
		{
			resource = new StaticModelData(mDevice, mPath + objectFilename, mPath + materialFilename);
			AddResource(objectFilename, resource);
		}

		return resource;
	}
}