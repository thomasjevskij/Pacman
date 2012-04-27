#include "Effect.hpp"
#include <algorithm>
#include <cassert>

namespace Framework
{
	Effect::Effect(ID3D10Device* device, const std::string& filename) :
		mDevice(device),
		mEffect(NULL)
	{
		if (!LoadEffectFile(filename))
		{
			throw std::runtime_error("Failed to load and compile effect file: " + filename);
		}
	}

	Effect::~Effect()
	{
		for (unsigned int i = 0; i < mTechniques.size(); ++i)
		{
			SafeDelete(mTechniques[i]);
		}

		SafeRelease(mEffect);
	}

	bool Effect::LoadEffectFile(const std::string& filename)
	{
		// Release the old effect and clear the old techniques
		SafeRelease(mEffect);
		mTechniques.clear();


		// Load and compile the new effect
		UINT shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	#ifdef DEBUG_MODE
			shaderFlags |= D3D10_SHADER_DEBUG;
	#endif

		ID3D10Blob* errors = NULL;
		HRESULT result = D3DX10CreateEffectFromFile(filename.c_str(),
													NULL,
													NULL,
													"fx_4_0",
													shaderFlags,
													0,
													mDevice,
													NULL,
													NULL,
													&mEffect,
													&errors,
													NULL);

		// See if load and compile was successful
		if (FAILED(result))
		{
			// If we have compile errors, print them
			if (errors != NULL)
			{
				MessageBox(NULL, static_cast<char*>(errors->GetBufferPointer()), "Error", MB_OK | MB_ICONERROR);
				SafeRelease(errors);
			}

			return false;
		}

		// Store all techniques
		D3D10_EFFECT_DESC effectDescription;
		mEffect->GetDesc(&effectDescription);
	
		mTechniques.reserve(effectDescription.Techniques);
		for (unsigned int i = 0; i < effectDescription.Techniques; ++i)
		{
			mTechniques.push_back(new Technique(mEffect->GetTechniqueByIndex(i)));
		}

		return true;
	}

	unsigned int Effect::GetTechniqueCount() const
	{
		return mTechniques.size();
	}

	Technique& Effect::GetTechniqueByIndex(unsigned int index)
	{
		assert(index >= 0);
		assert(index < mTechniques.size());
		return *mTechniques[index];
	}

	const Technique& Effect::GetTechniqueByIndex(unsigned int index) const
	{
		assert(index >= 0);
		assert(index < mTechniques.size());
		return *mTechniques[index];
	}

	Technique& Effect::GetTechniqueByName(const std::string& name)
	{
		for (unsigned int i = 0; i < mTechniques.size(); ++i)
		{
			if (mTechniques[i]->GetName() == name)
				return *mTechniques[i];
		}

		throw std::runtime_error("No technique by the name: " + name);
	}

	const Technique& Effect::GetTechniqueByName(const std::string& name) const
	{
		for (unsigned int i = 0; i < mTechniques.size(); ++i)
		{
			if (mTechniques[i]->GetName() == name)
				return *mTechniques[i];
		}

		throw std::runtime_error("No technique by the name: " + name);
	}




	void Effect::SetVariable(const std::string& variableName, int value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsScalar()->SetInt(value);
	}

	void Effect::SetVariable(const std::string& variableName, bool value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsScalar()->SetBool(value);
	}

	void Effect::SetVariable(const std::string& variableName, float value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsScalar()->SetFloat(value);
	}

	void Effect::SetVariable(const std::string& variableName, const D3DXVECTOR4& value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsVector()->SetFloatVector((FLOAT*)&value);
	}

	void Effect::SetVariable(const std::string& variableName, const D3DXVECTOR3& value)
	{
		D3DXVECTOR3 v = value;
		mEffect->GetVariableByName(variableName.c_str())->SetRawValue(&v, 0, sizeof(D3DXVECTOR3));
	}

	void Effect::SetVariable(const std::string& variableName, const D3DXVECTOR2& value)
	{
		D3DXVECTOR2 v = value;
		mEffect->GetVariableByName(variableName.c_str())->SetRawValue(&v, 0, sizeof(D3DXVECTOR2));
	}

	void Effect::SetVariable(const std::string& variableName, const D3DXMATRIX& value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsMatrix()->SetMatrix((FLOAT*)&value);
	}

	void Effect::SetVariable(const std::string& variableName, ID3D10ShaderResourceView* value)
	{
		mEffect->GetVariableByName(variableName.c_str())->AsShaderResource()->SetResource(value);
	}
}