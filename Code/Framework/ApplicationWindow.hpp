#ifndef APPLICATION_WINDOW_HPP
#define APPLICATION_WINDOW_HPP

#include "Global.hpp"
#include <string>
#include <map>
#include <vector>

namespace Framework
{
	// Forward declare
	class ApplicationWindow;

	// Defines a subscription interface for receiving window events
	class WindowNotificationSubscriber
	{
	public:
		virtual void WindowResized(ApplicationWindow* window, unsigned int clientWidth, unsigned int clientHeight) {}

		virtual void KeyPressed(ApplicationWindow* window, int keyCode) {}
		virtual void KeyReleased(ApplicationWindow* window, int keyCode) {}
		virtual void CharEntered(ApplicationWindow* window, char character) {}
	};



	// Defines a main application window
	class ApplicationWindow
	{
	public:
		// Defines the initial state of a window
		struct Description
		{
			int X;
			int Y;
			int ShowState;
			unsigned int ClientWidth;
			unsigned int ClientHeight;
			std::string Caption;
			bool Resizable;
			bool HasFrame;

			Description();
		};

		// Constructor & Destructor
		ApplicationWindow(HINSTANCE instance, const Description& description);
		~ApplicationWindow();

		// Notification subscription management
		void AddNotificationSubscriber(WindowNotificationSubscriber* subscriber);
		void RemoveNotificationSubscriber(WindowNotificationSubscriber* subscriber);
		bool IsNotificationSubscriber(const WindowNotificationSubscriber* subscriber) const;

		// Getters
		unsigned int GetWindowWidth() const;
		unsigned int GetWindowHeight() const;
		unsigned int GetClientWidth() const;
		unsigned int GetClientHeight() const;
		HWND GetHandle() const;
		int GetExitValue() const;

		// Process all messages currently in the message queue
		bool ProcessMessages();
	private:
		typedef std::vector<WindowNotificationSubscriber*> NotificationSubscriberVector;
		typedef std::map<HWND, ApplicationWindow*> WindowRegister;

		static WindowRegister sWindowRegister;

		HINSTANCE mInstance;
		HWND mHandle;
		RECT mClientRect;
		RECT mWindowRect;
		NotificationSubscriberVector mNotificationSubscribers;
		int mExitValue;

		// The static WndProc. Forwards all messages to the proper ApplicationWindow class.
		static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

		// Methods for creating the window from the description.
		bool SetupClass(const Description& description);
		bool SetupWindow(const Description& description);

		// Message handling
		bool HandleWindowMessage(UINT message, WPARAM wParam, LPARAM lParam);
		void HandleSizeMessage();
		void HandleKeyDownMessage(WPARAM wParam, LPARAM lParam);
		void HandleKeyUpMessage(WPARAM wParam, LPARAM lParam);
		void HandleCharMessage(WPARAM wParam, LPARAM lParam);

		// Resource - disable copying
		ApplicationWindow(const ApplicationWindow&);
		ApplicationWindow& operator=(const ApplicationWindow&);
	};
}

#endif