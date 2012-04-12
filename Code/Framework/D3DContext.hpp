#ifndef D3DCONTEXT_HPP
#define D3DCONTEXT_HPP

#include <vector>

#include "Global.hpp"
#include "ApplicationWindow.hpp"

namespace Framework
{
	// Sets up the Direct3D environment
	class D3DContext : public WindowNotificationSubscriber
	{
	public:
		// Defines a rendering area on the backbuffer. All values ar nomalized [0.0, 1.0]
		struct Viewport
		{
			float Left;
			float Top;
			float Width;
			float Height;

			Viewport();
			Viewport(float left, float top, float width, float height);
		};

		// Describes the initial context for rendering
		struct Description
		{
			struct Buffer
			{
				unsigned int Width;
				unsigned int Height;

				Buffer();
			};

			// Whether the application should initially be in fullscreen or not.
			bool Fullscreen;

			// Setting the width or height to 0 will make the buffer the size of the target window's client area
			Buffer BackBuffer;

			// Setting the width or height to 0 will make the buffer the size of the back buffer
			Buffer DepthBuffer;

			// A vector of all viewports.
			std::vector<Viewport> Viewports;


			Description();
		};

		// Constructor & Destructor
		D3DContext(ApplicationWindow* targetWindow, const Description& description);
		~D3DContext() throw();

		// Clear the backbuffer and the depth/stencil buffer
		void Clear(const D3DXCOLOR& color = D3DXCOLOR(0, 0, 0, 0));
		
		// Swap the frontbuffer and the backbuffer
		void SwapBuffers();
	private:
		ApplicationWindow* mTargetWindow;

		ID3D10Device* mDevice;
		IDXGISwapChain* mSwapChain;
		ID3D10RenderTargetView* mBackBufferView;
		ID3D10Texture2D* mDepthStencilBuffer;
		ID3D10DepthStencilView* mDepthStencilView;

		std::vector<Viewport> mViewports;
		unsigned int mActiveViewport;

		bool CreateDeviceAndSwapChain(const Description& description);
		bool CreateBackBufferView();
		bool CreateDepthStencilBuffer(const Description::Buffer& description);

		// Resource - disable copying
		D3DContext(const D3DContext&);
		D3DContext& operator=(const D3DContext&);
	};
}
#endif