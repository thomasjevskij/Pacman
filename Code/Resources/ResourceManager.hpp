#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <cassert>

namespace Resources
{
	// Handles the loading and unloading of resources of a specific type.
	// Every resource class R must implement a constructor:
	// R(const std::string& filename)
	// When a resource of type R needs to be loaded, anywhere in the program, use the following syntax:
	// Resources::ResourceManager<R>::GetManager().Load("filename");
	// .. and a pointer of type R is returned to you. The ResourceManager handles ALL memory management
	// and no new/delete calls should be manually called.
	template <typename R>
	class ResourceManager
	{
	public:
		ResourceManager(const std::string& resourcePath);
		~ResourceManager() throw();

		R* Load(const std::string& filename);

		static ResourceManager<R>& GetManager();
	private:
		typedef std::map<std::string, R*> ResourceMap;

		static ResourceManager<R>* sManager;
		ResourceMap mResourceMap;
		std::string mResourcePath;
	};


	
	
	// IMPLEMENTATION

	template <typename R>
	ResourceManager<R>* ResourceManager<R>::sManager = NULL;

	template <typename R>
	ResourceManager<R>& ResourceManager<R>::GetManager()
	{
		return *sManager;
	}


	template <typename R>
	ResourceManager<R>::ResourceManager(const std::string& resourcePath)
		: mResourcePath(resourcePath)
	{
		assert(sManager == NULL);
		sManager = this;
	}

	template <typename R>
	ResourceManager<R>::~ResourceManager() throw()
	{
		assert(sManager != NULL);
		sManager = NULL;

		ResourceMap::iterator it;
		for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
		{
			delete it->second;
		}
	}


	template <typename R>
	R* ResourceManager<R>::Load(const std::string& filename)
	{
		std::string filePath = mResourcePath + filename;
		R* resource = NULL;
		
		ResourceMap::iterator it = mResourceMap.find(filePath);
		if (it != mResourceMap.end())
		{
			resource = it->second;
		}
		else
		{
			resource = new R(filePath);
			mResourceMap[filePath] = resource;
		}

		return resource;
	}
}

#endif