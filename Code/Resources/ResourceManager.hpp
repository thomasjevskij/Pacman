#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include "r2-assert.hpp"

namespace Resources
{
	namespace Private
	{
		// ResourceManager
		// Manages a map of resources, mapping name to resource.
		// When a new resource type is added, that is not loaded from file
		// a new manager should be derived from this class.
		template <typename T>
		class ResourceManager
		{
		public:
			typedef std::string Handle;

			~ResourceManager() throw();

			T* GetResource(const Handle& handle);
		protected:
			typedef std::map<Handle, T*> ResourceMap;

			void AddResource(const Handle& handle, T* resource);
		private:
			ResourceMap mResourceMap;
		};
	}
	



	//////////////////////////////////////////////////////////////////////////////////////
	// ResourceManager Implementation
	//////////////////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template <typename T>
		ResourceManager<T>::~ResourceManager() throw()
		{
			ResourceMap::iterator it;
			for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
			{
				delete it->second;
			}
		}

		template <typename T>
		T* ResourceManager<T>::GetResource(const Handle& handle)
		{
			T* resource = NULL;
		
			ResourceMap::iterator it = mResourceMap.find(handle);
			if (it != mResourceMap.end())
			{
				resource = it->second;
			}
		
			return resource;
		}

		template <typename T>
		void ResourceManager<T>::AddResource(const Handle& handle, T* resource)
		{
			r2AssertM(!handle.empty(), "Empty resource handle");
			r2AssertM(resource != NULL, "NULL resource");

			ResourceMap::iterator it = mResourceMap.find(handle);
			if (it == mResourceMap.end())
			{
				mResourceMap[handle] = resource;
			}
			else
			{
				r2AssertM(false, "Two resources with same handle loaded");
			}
		}
	}
}

#endif