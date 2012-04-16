#include "Global.hpp"
#include "ResourceManager.hpp"

class Dummy
{
public:
	Dummy(const std::string& filename)
	{
		MessageBox(NULL, filename.c_str(), "Loaded!", MB_OK);
	}
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showState)
{
	Resources::ResourceManager<Dummy> rm("Resources/");

	Resources::ResourceManager<Dummy>::GetManager().Load("Hello world");
	Resources::ResourceManager<Dummy>::GetManager().Load("Hello world 2");

	return 0;
}