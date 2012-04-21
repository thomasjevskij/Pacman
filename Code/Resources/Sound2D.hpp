#ifndef SOUND_2D_HPP
#define SOUND_2D_HPP

#include <fmod.hpp>
#include <string>

#include "ResourceManager.hpp"
#include "r2-singleton.hpp"

namespace Resources
{
	// Creates a 2D sound that can be played by calling Sound2D::Play()
	class Sound2D
	{
	public:
		Sound2D(const std::string& path, FMOD::System* soundSystem);
		~Sound2D() throw();

		void Play();

	private:
		FMOD::System* mSystem;
		FMOD::Sound* mSound;
		
		Sound2D(const Sound2D&);
		Sound2D& operator=(const Sound2D&);
	};
}

namespace Resources
{
	// SoundResourceManager
	// Handles loading and storing of sound resources loaded from file.
	// The manager can be accessed in the following way:
	//
	// Resources::SoundResourceManager::Instance()
	// 
	// The manager will handle all creation/deletion of the resources, and when a resource
	// is to be loaded, use the Load() method. To access a resource, use the GetResource() method.
	//
	// The only restriction on sound resource types loaded from file, is that they have a
	// constructor that only takes the filename of the resource file.
	class SoundResourceManager : public r2::Singleton<SoundResourceManager>, public Private::ResourceManager<Sound2D>
	{
	public:
		SoundResourceManager(const std::string& path);

		Sound2D* Load(const std::string& filename);

	private:
		FMOD::System* mSystem;
		std::string mPath;
	};
}
#endif