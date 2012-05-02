#ifndef D3D_RESOURCE_MANAGER_HPP
#define D3D_RESOURCE_MANAGER_HPP

#include "ResourceManager.hpp"
#include "r2-singleton.hpp"

namespace Resources
{
	// D3DResourceManager
	// Handles loading and storing of resources loaded from file.
	// The template variable should be the resource class and the manager can 
	// be accessed in the following way:
	//
	// Resources::D3DResourceManager<Effect>::Instance()
	// 
	// The manager will handle all creation/deletion of the resources, and when a resource
	// is to be loaded, use the Load() method. To access a resource, use the GetResource() method.
	//
	// The only restriction on resource types loaded from file, is that they have a constructor that
	// takes a pointer to a Direct3D device and the filename of the resource file.
	template <typename T>
	class D3DResourceManager : public r2::Singleton<D3DResourceManager<T>>, public Private::ResourceManager<T>
	{
	public:
		D3DResourceManager(ID3D10Device* device, const std::string& path);

		virtual T* Load(const Handle& filename);

	private:
		ID3D10Device* mDevice;
		std::string mPath;
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// D3DResourceManager Implementation
	//////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	D3DResourceManager<T>::D3DResourceManager(ID3D10Device* device, const std::string& path)
		: mPath(path), mDevice(device)
	{}

	template <typename T>
	T* D3DResourceManager<T>::Load(const Handle& filename)
	{
		T* resource = GetResource(filename);

		if (resource == NULL)
		{
			resource = new T(mDevice, mPath + filename);
			AddResource(filename, resource);
		}

		return resource;
	}
}

#endif