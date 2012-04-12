#include "D3DContext.hpp"

namespace Framework
{
	D3DContext::Viewport::Viewport()
		: Left(0.0f)
		, Top(0.0f)
		, Width(1.0f)
		, Height(1.0f)
	{}

	D3DContext::Viewport::Viewport(float left, float top, float width, float height)
		: Left(left)
		, Top(top)
		, Width(width)
		, Height(height)
	{}

	D3DContext::Description::Buffer::Buffer()
		: Width(0)
		, Height(0)
	{}

	D3DContext::Description::Description()
		: Fullscreen(false)
	{}


	D3DContext::D3DContext(ApplicationWindow* targetWindow, const Description& description)
		: mTargetWindow(targetWindow)
	{
		if (!CreateDeviceAndSwapChain(description))
			throw std::runtime_error("Failed to create device and swap chain");
		if (!CreateBackBufferView())
			throw std::runtime_error("Failed to create a back buffer view");
		if (!CreateDepthStencilBuffer(description.DepthBuffer))
			throw std::runtime_error("Failed to create a depth/stencil buffer");

		mDevice->OMSetRenderTargets(1, &mBackBufferView, mDepthStencilView);

		mTargetWindow->AddNotificationSubscriber(this);
	}

	D3DContext::~D3DContext() throw()
	{

	}

	void D3DContext::Clear(const D3DXCOLOR& color)
	{

	}
		
	void D3DContext::SwapBuffers()
	{

	}

	bool D3DContext::CreateDeviceAndSwapChain(const Description& description)
	{
		return true;
	}

	bool D3DContext::CreateBackBufferView()
	{
		return true;
	}

	bool D3DContext::CreateDepthStencilBuffer(const Description::Buffer& description)
	{
		return true;
	}

}