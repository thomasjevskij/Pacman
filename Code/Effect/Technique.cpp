#include "Technique.hpp"
#include <cassert>

namespace D3D
{
	Technique::Technique(ID3D10EffectTechnique* technique) :
		mTechnique(technique)
	{
		D3D10_TECHNIQUE_DESC description;
		mTechnique->GetDesc(&description);

		mName = description.Name;

		mPasses.reserve(description.Passes);
		for (unsigned int i = 0; i < description.Passes; ++i)
		{
			mPasses.push_back(new Pass(mTechnique->GetPassByIndex(i)));
		}
	}

	Technique::~Technique() throw()
	{
		for (unsigned int i = 0; i < mPasses.size(); ++i)
		{
			SafeDelete(mPasses[i]);
		}
	}

	Pass& Technique::GetPassByIndex(unsigned int index)
	{
		assert(index >= 0);
		assert(index < mPasses.size());
		return *mPasses[index];
	}

	const Pass& Technique::GetPassByIndex(unsigned int index) const
	{
		assert(index >= 0);
		assert(index < mPasses.size());
		return *mPasses[index];
	}


	Pass& Technique::GetPassByName(const std::string& name)
	{
		for (unsigned int i = 0; i < mPasses.size(); ++i)
		{
			if (mPasses[i]->GetName() == name)
				return *mPasses[i];
		}

		throw std::runtime_error("No pass by name: " + name);
	}

	const Pass& Technique::GetPassByName(const std::string& name) const
	{
		for (unsigned int i = 0; i < mPasses.size(); ++i)
		{
			if (mPasses[i]->GetName() == name)
				return *mPasses[i];
		}

		throw std::runtime_error("No pass by name: " + name);
	}
}