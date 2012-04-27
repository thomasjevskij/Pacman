#include "ModelObj.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>

#include "FileResourceManager.hpp"
#include "D3DResourceManager.hpp"

namespace Resources
{
	Material::Definition::Definition()
		: Ambient(D3DXVECTOR3(0.2, 0.2, 0.2)), Diffuse(D3DXVECTOR3(0.8, 0.8, 0.8))
		,  Specular(D3DXVECTOR3(1.0, 1.0, 1.0)), Tf(D3DXVECTOR3(1.0, 1.0, 1.0))
		,  IlluminationModel(0), /*Opacitiy(1.0),*/ RefractionIndex(1.0)
		/*,  SpecularExp(), Sharpness(60.0)*/, MainTexture(NULL)
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
					Resources::D3DResourceManager<Texture>::Instance().Load(textureFilename);
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
	ModelObj::ModelObj(ID3D10Device* device, std::string filename)
		: mMaterial(NULL), mDevice(device), mEffect(NULL), mBuffer(NULL)
	{
		D3DXMatrixIdentity(&mWorld);

		if(!Load(filename))
			return;
	}

	ModelObj::~ModelObj() throw()
	{
		SafeDelete(mBuffer);
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

			if(key == "mtllib")
			{
				std::string matFile;
				streamLine >> matFile;

				if(!LoadMaterial(matFile))
				{
					// Material was not loaded
					// TODO: error checking?
				}
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
		}

		// Describe the buffer and create it
		Framework::VertexBuffer::Description desc;
		desc.ElementCount = vertices.size();
		desc.ElementSize = sizeof(Vertex);
		desc.FirstElementPointer = &vertices[0];
		desc.Topology = Framework::Topology::TriangleList;
		desc.Usage = Framework::Usage::Default;

		mBuffer = new Framework::VertexBuffer(mDevice);
		mBuffer->SetData(desc, NULL);

		// Create the effect and set up the input layout
		mEffect = Resources::D3DResourceManager<Framework::Effect>::Instance().Load("ModelObj.fx");
		Framework::InputLayoutVector inputLayout;
		inputLayout.push_back(Framework::InputLayoutElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT));
		inputLayout.push_back(Framework::InputLayoutElement("UV", DXGI_FORMAT_R32G32_FLOAT));

		mEffect->GetTechniqueByIndex(0).GetPassByIndex(0).SetInputLayout(inputLayout);

		return true;
	}

	bool ModelObj::LoadMaterial(std::string filename)
	{
		mMaterial = FileResourceManager<Material>::Instance().Load(filename);

		return mMaterial->Materials.size() > 0;
	}

	void ModelObj::Draw(D3DXVECTOR3 drawPosition)
	{
		UpdateWorldMatrix(drawPosition);
		D3DXMATRIX worldViewProjection, view, projection;

		// DEBUG: get from Camera...
		D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 50, -50), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixPerspectiveFovLH(&projection, 0.25f * D3DX_PI, 1024/768, 1.0f, 1000.0f);
		
		worldViewProjection = mWorld * view * projection;

		mEffect->SetVariable("g_matWorld", mWorld);
		mEffect->SetVariable("g_matWVP", worldViewProjection);
		
		// DEBUG: get light position elsewhere
		mEffect->SetVariable("g_lightDirection", D3DXVECTOR4(10, 10, 0, 0));

		// Bind and draw the buffer, once for each pass
		mBuffer->Bind();
		for(UINT p = 0; p < mEffect->GetTechniqueByIndex(0).GetPassCount(); ++p)
		{
			mEffect->GetTechniqueByIndex(0).GetPassByIndex(p).Apply(mDevice);
			mBuffer->Draw();
		}
	}

	void ModelObj::UpdateWorldMatrix(D3DXVECTOR3 position)
	{
		// Update position in matrix
		mWorld.m[3][0] = position.x;
		mWorld.m[3][1] = position.y;
		mWorld.m[3][2] = position.z;
	}
}