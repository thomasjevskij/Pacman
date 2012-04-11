#include "Global.hpp"
#include "ApplicationWindow.hpp"

using Framework::ApplicationWindow;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showState)
{
	ApplicationWindow::Description description;
	description.X = 0;
	description.Y = 0;
	description.ClientWidth = 640;
	description.ClientHeight = 480;
	description.ShowState = showState;
	description.HasFrame = true;
	description.Resizable = true;
	
	ApplicationWindow window(instance, description);
	
	bool running = true;
	while (running)
	{
		running = window.ProcessMessages();
	}

	return 0;
}