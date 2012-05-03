#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "Global.hpp"
#include <string>
#include <vector>
#include "Technique.hpp"
#include "ResourceManager.hpp"
#include "r2-singleton.hpp"

namespace Framework
{
	class EffectVariableBatch
	{
	public:
		EffectVariableBatch();
		~EffectVariableBatch() throw();

		void SetVariable(const std::string& variableName, int value);
		void SetVariable(const std::string& variableName, bool value);
		void SetVariable(const std::string& variableName, float value);
		void SetVariable(const std::string& variableName, const D3DXVECTOR4& value);
		void SetVariable(const std::string& variableName, const D3DXVECTOR3& value);
		void SetVariable(const std::string& variableName, const D3DXVECTOR2& value);
		void SetVariable(const std::string& variableName, const D3DXMATRIX& value);
		void SetVariable(const std::string& variableName, ID3D10ShaderResourceView* value);
	private:
		std::map<std::string, int> mIntegers;
		std::map<std::string, bool> mBooleans;
		std::map<std::string, float> mScalars;
		std::map<std::string, D3DXVECTOR4> mVectors4;
		std::map<std::string, D3DXVECTOR3> mVectors3;
		std::map<std::string, D3DXVECTOR2> mVectors2;
		std::map<std::string, D3DXMATRIX> mMatrices;
		//std::map<std::string, 
		// TODO: Figure out how to store textures.
	};

	class Effect
	{
	public:
		Effect(ID3D10Device* device, const std::string& filename);
		~Effect();

		// Release the old effect file and load a new one, and enumerate all the techniques
		bool LoadEffectFile(const std::string& filename);

		// Get the number of techniques in this effect
		unsigned int GetTechniqueCount() const;

		// Get a technique by specifying its index
		Technique& GetTechniqueByIndex(unsigned int index);
		const Technique& GetTechniqueByIndex(unsigned int index) const;

		
		// Get a technique by specifying its name. If no technique by the name exists,
		// a runtime exception is raised.
		Technique& GetTechniqueByName(const std::string& name);
		const Technique& GetTechniqueByName(const std::string& name) const;
	private:
		ID3D10Device* mDevice;
		ID3D10Effect* mEffect;
	
		std::vector<Technique*> mTechniques;

		
		// Effects should not be copied. Immutable resource (at this point, since
		// no methods for modifying them are present).
		Effect(const Effect& copy);
		Effect& operator=(const Effect& copy);
	};
}
#endif