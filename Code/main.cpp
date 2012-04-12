#include "Global.hpp"
#include "ApplicationWindow.hpp"
#include "D3DContext.hpp"

using namespace Framework;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showState)
{
	ApplicationWindow::Description wd;
	wd.X = 0;
	wd.Y = 0;
	wd.ClientWidth = 640;
	wd.ClientHeight = 480;
	wd.ShowState = showState;
	wd.HasFrame = true;
	wd.Resizable = false;
	wd.Caption = "Dutch Painter Vermeer";

	ApplicationWindow window(instance, wd);

	D3DContext::Description cd;
	cd.BackBuffer.Width = 1280;
	cd.BackBuffer.Height = 1024;
	cd.Fullscreen = false;
	cd.Viewports.push_back(D3DContext::Viewport());

	D3DContext context(&window, cd);
	
	bool running = true;
	while (running)
	{
		running = window.ProcessMessages();

		context.Clear(D3DXCOLOR(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f));

		context.SwapBuffers();
	}

	return 0;
}