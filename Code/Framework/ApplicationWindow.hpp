#ifndef APPLICATION_WINDOW_HPP
#define APPLICATION_WINDOW_HPP

#include "Global.hpp"
#include <string>
#include <map>

namespace Framework
{
	class ApplicationWindow
	{
	public:
		/*
			See this struct for standard! FOLLOW AND OBEY!
			Structs have no m prefix in their members's names.
			
			These types of comments are to be used
		*/
		struct Description
		{
			Description();

			int X;
			int Y;
			int ShowState;
			unsigned int ClientWidth;
			unsigned int ClientHeight;
			std::string Caption;
			bool Resizable;
			bool HasFrame;
		};

		ApplicationWindow(HINSTANCE instance, const Description& description);
		~ApplicationWindow();

		bool ProcessMessages();
	private:
		typedef std::map<HWND, ApplicationWindow*> WindowRegister;

		static WindowRegister sWindowRegister;

		HINSTANCE mInstance;
		HWND mHandle;
		RECT mClientRect;
		RECT mWindowRect;

		static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
		bool SetupClass(const Description& description);
		bool SetupWindow(const Description& description);
		bool HandleWindowMessage(UINT message, WPARAM wParam, LPARAM lParam);

		// Resource - disable copying
		ApplicationWindow(const ApplicationWindow&);
		ApplicationWindow& operator=(const ApplicationWindow&);
	};
}

#endif