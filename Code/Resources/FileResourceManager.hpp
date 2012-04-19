#ifndef FILE_RESOURCE_MANAGER_HPP
#define FILE_RESOURCE_MANAGER_HPP

#include "ResourceManager.hpp"
#include "r2-singleton.hpp"

namespace Resources
{
	// FileResourceManager
	// Handles loading and storing of resources loaded from file.
	// The template variable should be the resource class and the manager can 
	// be accessed in the following way:
	//
	// Resources::FileResourceManager<Level>::Instance()
	// 
	// The manager will handle all creation/deletion of the resources, and when a resource
	// is to be loaded, use the Load() method. To access a resource, use the GetResource() method.
	//
	// The only restriction on resource types loaded from file, is that they have a constructor that
	// only takes the filename of the resource file.
	template <typename T>
	class FileResourceManager : public r2::Singleton<FileResourceManager<T> >, public Private::ResourceManager<T>
	{
	public:
		FileResourceManager(const std::string& path);

		virtual T* Load(const Handle& filename);
	private:
		std::string mPath;
	};





	//////////////////////////////////////////////////////////////////////////////////////
	// FileResourceManager Implementation
	//////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	FileResourceManager<T>::FileResourceManager(const std::string& path)
		: mPath(path)
	{}

	template <typename T>
	T* FileResourceManager<T>::Load(const Handle& filename)
	{
		T* resource = GetResource(filename);

		if (resource == NULL)
		{
			resource = new T(mPath + filename);
			AddResource(filename, resource);
		}

		return resource;
	}
}

#endif