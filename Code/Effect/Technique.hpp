#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP

#include "Global.hpp"
#include <vector>
#include "Pass.hpp"

namespace D3D
{
	/**
		Specifies one technique in an effect file. Every technique can hold several passes.
	*/
	class Technique
	{
	public:
		Technique(ID3D10EffectTechnique* technique);
		~Technique() throw();

		/**
			Get the name of the technique
		*/
		const std::string& GetName() const { return mName; }

		/**
			Get the number of passes this technique contains
		*/
		unsigned int GetPassCount() const { return mPasses.size(); }
	
		/**
			Get a pass by specifying its index
		*/
		Pass& GetPassByIndex(unsigned int index);
		const Pass& GetPassByIndex(unsigned int index) const;

		/**
			Get a pass by specifying its name. If no pass by the name exists,
			a runtime exception is raised.
		*/
		Pass& GetPassByName(const std::string& name);
		const Pass& GetPassByName(const std::string& name) const;
	private:
		ID3D10EffectTechnique* mTechnique;
		std::string mName;

		std::vector<Pass*> mPasses;

		/**
			Non-copyable - internally created only by effect.
		*/
		Technique(const Technique& copy);
		Technique& operator=(const Technique& copy);
	};
}

#endif