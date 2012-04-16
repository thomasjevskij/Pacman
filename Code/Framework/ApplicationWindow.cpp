#include "ApplicationWindow.hpp"
#include "Primitives.hpp"
#include <stdexcept>
#include <algorithm>

namespace Framework
{
	// Static initialization
	std::map<HWND, ApplicationWindow*> ApplicationWindow::sWindowRegister;

	// Static WndProc
	LRESULT CALLBACK ApplicationWindow::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_CREATE)
		{
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			ApplicationWindow* instance = reinterpret_cast<ApplicationWindow*>(cs->lpCreateParams);

			if (instance != NULL)
			{
				sWindowRegister[handle] = instance;
			}
		}

		WindowRegister::iterator it = sWindowRegister.find(handle);
		if (it != sWindowRegister.end())
		{
			if (it->second->HandleWindowMessage(message, wParam, lParam))
				return 0;
		}
		
		return DefWindowProc(handle, message, wParam, lParam);
	}



	ApplicationWindow::Description::Description()
		: X(0)
		, Y(0)
		, ShowState(SW_SHOW)
		, ClientWidth(640)
		, ClientHeight(480)
		, Caption("Application")
		, Resizable(true)
		, HasFrame(true)
	{}

	ApplicationWindow::ApplicationWindow(HINSTANCE instance, const Description& description)
		: mExitValue(0)
	{
		if (!SetupClass(description))
			throw std::runtime_error("Failed to register window class");
		if (!SetupWindow(description))
			throw std::runtime_error("Failed to create window");
	}

	ApplicationWindow::~ApplicationWindow()
	{
		if (sWindowRegister.find(mHandle) != sWindowRegister.end())
		{
			sWindowRegister.erase(mHandle);
		}
	}

	void ApplicationWindow::AddNotificationSubscriber(WindowNotificationSubscriber* subscriber)
	{
		NotificationSubscriberVector::iterator it = std::find(mNotificationSubscribers.begin(), mNotificationSubscribers.end(), subscriber);
		if (it == mNotificationSubscribers.end())
		{
			mNotificationSubscribers.push_back(subscriber);
		}
	}

	void ApplicationWindow::RemoveNotificationSubscriber(WindowNotificationSubscriber* subscriber)
	{
		NotificationSubscriberVector::iterator it = std::find(mNotificationSubscribers.begin(), mNotificationSubscribers.end(), subscriber);
		while (it != mNotificationSubscribers.end())
		{
			mNotificationSubscribers.erase(it);
			it = std::find(mNotificationSubscribers.begin(), mNotificationSubscribers.end(), subscriber);
		}
	}

	bool ApplicationWindow::IsNotificationSubscriber(const WindowNotificationSubscriber* subscriber) const
	{
		NotificationSubscriberVector::const_iterator it = std::find(mNotificationSubscribers.begin(), mNotificationSubscribers.end(), subscriber);
		return it != mNotificationSubscribers.end();
	}

	unsigned int ApplicationWindow::GetWindowWidth() const
	{
		return Helper::GetRectWidth(mWindowRect);
	}

	unsigned int ApplicationWindow::GetWindowHeight() const
	{
		return Helper::GetRectHeight(mWindowRect);
	}

	unsigned int ApplicationWindow::GetClientWidth() const
	{
		return Helper::GetRectWidth(mClientRect);
	}

	unsigned int ApplicationWindow::GetClientHeight() const
	{
		return Helper::GetRectHeight(mClientRect);
	}

	HWND ApplicationWindow::GetHandle() const
	{
		return mHandle;
	}

	int ApplicationWindow::GetExitValue() const
	{
		return mExitValue;
	}

	bool ApplicationWindow::ProcessMessages()
	{
		MSG message;
		ZeroMemory(&message, sizeof(message));

		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		if (message.message == WM_QUIT)
			mExitValue = (int) message.wParam;

		return message.message != WM_QUIT;
	}

	bool ApplicationWindow::SetupClass(const Description& description)
	{
		WNDCLASSEX windowClass;

		windowClass.cbSize			= sizeof(WNDCLASSEX);				// Size of the structure in bytes
		windowClass.style			= CS_VREDRAW | CS_HREDRAW;			// When to redraw: at both vertical and horizontal resizing
		windowClass.cbClsExtra		= 0;								// Extra memory slot, not needed
		windowClass.cbWndExtra		= 0;								// Extra memory slot, not needed
		windowClass.hInstance		= mInstance;						// Application handle
		windowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOWTEXT + 1);	// Window background color
		windowClass.hCursor			= LoadCursor(0, IDC_ARROW);			// Window mouse cursor icon
		windowClass.hIcon			= LoadIcon(0, IDI_APPLICATION);		// Window icon
		windowClass.hIconSm			= 0;								// No small icon version is needed
		windowClass.lpfnWndProc		= WndProc;							// The windowClass procedure to handle windowClass messages
		windowClass.lpszClassName	= "ApplicationWindow";				// Name of the windowClass, used for identification
		windowClass.lpszMenuName	= 0;								// Since there are no menu for the window, value is 0

		if (!RegisterClassEx(&windowClass))
			return false;

		return true;
	}

	bool ApplicationWindow::SetupWindow(const Description& description)
	{
		DWORD style = WS_OVERLAPPEDWINDOW;
		unsigned int windowX = (description.X < 0) ? CW_USEDEFAULT : description.X;
		unsigned int windowY = (description.Y < 0) ? CW_USEDEFAULT : description.Y;

		if (!description.Resizable)
		{
			style ^= WS_SIZEBOX;
			style ^= WS_MAXIMIZEBOX;
		}

		if (!description.HasFrame)
		{
			style ^= WS_SYSMENU;
			style ^= WS_OVERLAPPED;
			style ^= WS_CAPTION;
			style ^= WS_THICKFRAME;
			style |= WS_POPUP;
		}

		mClientRect.left = 0;
		mClientRect.right = description.ClientWidth;
		mClientRect.top = 0;
		mClientRect.bottom = description.ClientHeight;

		mWindowRect = mClientRect;
		AdjustWindowRect(&mWindowRect, style, FALSE);

		mHandle = CreateWindow("ApplicationWindow",							// The name of the registered window "mold" to use
									 description.Caption.c_str(),			// Title of the window
									 style,									// Window style
									 windowX,								// X-position
									 windowY,								// Y-position
									 Helper::GetRectWidth(mWindowRect),		// Window width
									 Helper::GetRectHeight(mWindowRect),	// Window height
									 0,										// Parent window, 0 because there is no parent
									 0,										// Menu handle, 0 because there is no menu
									 mInstance,								// Application instance handle
									 this);
		if (mHandle == NULL)
			return false;

		ShowWindow(mHandle, description.ShowState);
		UpdateWindow(mHandle);

		return true;
	}

	bool ApplicationWindow::HandleWindowMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return true;
			case WM_SIZE:
				HandleSizeMessage();
				return true;
			case WM_KEYDOWN:
				HandleKeyDownMessage(wParam, lParam);
				return true;
			case WM_KEYUP:
				HandleKeyUpMessage(wParam, lParam);
				return true;
			case WM_CHAR:
				HandleCharMessage(wParam, lParam);
				return true;
		}

		return false;
	}

	void ApplicationWindow::HandleSizeMessage()
	{
		WINDOWINFO info;
		GetWindowInfo(mHandle, &info);

		bool resized = false;
		if (Helper::GetRectWidth(info.rcClient) != Helper::GetRectWidth(mClientRect))
			resized = true;
		else if (Helper::GetRectHeight(info.rcClient) != Helper::GetRectHeight(mClientRect))
			resized = true;

		mClientRect = info.rcClient;
		mWindowRect = info.rcWindow;
				
		if (resized)
		{
			for (size_t i = 0; i < mNotificationSubscribers.size(); ++i)
			{
				mNotificationSubscribers[i]->WindowResized(this, GetClientWidth(), GetClientHeight());
			}
		}
	}

	void ApplicationWindow::HandleKeyDownMessage(WPARAM wParam, LPARAM lParam)
	{
		for (size_t i = 0; i < mNotificationSubscribers.size(); ++i)
		{
			mNotificationSubscribers[i]->KeyPressed(this, wParam);
		}
	}

	void ApplicationWindow::HandleKeyUpMessage(WPARAM wParam, LPARAM lParam)
	{
		for (size_t i = 0; i < mNotificationSubscribers.size(); ++i)
		{
			mNotificationSubscribers[i]->KeyReleased(this, wParam);
		}
	}

	void ApplicationWindow::HandleCharMessage(WPARAM wParam, LPARAM lParam)
	{
		for (size_t i = 0; i < mNotificationSubscribers.size(); ++i)
		{
			mNotificationSubscribers[i]->CharEntered(this, static_cast<char>(wParam));
		}
	}
}