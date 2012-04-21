#include "Sound2D.hpp"
#include <fmod_errors.h>

namespace Resources
{
	Sound2D::Sound2D(const std::string& path, FMOD::System* soundSystem)
		: mSystem(soundSystem)
	{
		FMOD_RESULT result;

		// FMOD_DEFAULT uses the defaults. These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
		result = soundSystem->createSound(path.c_str(), FMOD_DEFAULT, 0, &mSound);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		}
	}

	Sound2D::~Sound2D() throw()
	{
		mSound->release();
	}

	// Play the sound once
	void Sound2D::Play()
	{
		FMOD_RESULT result;

		result = mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, NULL);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}
}

namespace Resources
{
	SoundResourceManager::SoundResourceManager(const std::string& path)
		: mPath(path)
	{
		FMOD_RESULT result;

		result = FMOD::System_Create(&mSystem);		// Create the main system object.
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

		result = mSystem->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	Sound2D* SoundResourceManager::Load(const std::string& filename)
	{

		Sound2D* resource = GetResource(filename);

		if (resource == NULL)
		{
			resource = new Sound2D(mPath + filename, mSystem);
			AddResource(filename, resource);
		}

		return resource;
	}
}