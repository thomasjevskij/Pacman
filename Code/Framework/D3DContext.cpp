#include "D3DContext.hpp"
#include <cassert>

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

		SetViewports(description.Viewports);
		SetActiveViewport(0);
	}

	D3DContext::~D3DContext() throw()
	{
		if(mDevice != NULL) 
			mDevice->ClearState();

		mSwapChain->SetFullscreenState(FALSE, NULL);

		SafeRelease(mDepthStencilView);
		SafeRelease(mDepthStencilBuffer);
		SafeRelease(mBackBufferView);
		SafeRelease(mSwapChain);
		SafeRelease(mDevice);
	}

	const std::vector<D3DContext::Viewport> D3DContext::GetViewports() const
	{
		return mViewports;
	}

	void D3DContext::SetViewports(const std::vector<Viewport>& viewports)
	{
		mViewports = viewports;
	}

	void D3DContext::SetActiveViewport(unsigned int index)
	{
		assert(index < mViewports.size());

		D3D10_VIEWPORT vp;
		vp.TopLeftX = mViewports[index].Left * mTargetWindow->GetClientWidth();
		vp.TopLeftY = mViewports[index].Top * mTargetWindow->GetClientHeight();
		vp.Width = mViewports[index].Width * mTargetWindow->GetClientWidth();
		vp.Height = mViewports[index].Height * mTargetWindow->GetClientHeight();
		vp.MinDepth = 0;
		vp.MaxDepth = 1;

		mActiveViewport = index;
		mDevice->RSSetViewports(1, &vp);
	}

	unsigned int D3DContext::GetActiveViewport() const
	{
		return mActiveViewport;
	}

	void D3DContext::ToggleFullscreen()
	{
		mSwapChain->SetFullscreenState(TRUE, NULL);
	}

	bool D3DContext::ResizeBuffers(Description::Buffer backBufferDescription, const Description::Buffer& depthBufferDescription)
	{
		backBufferDescription.Width = (backBufferDescription.Width == 0) ? mTargetWindow->GetClientWidth() : backBufferDescription.Width;
		backBufferDescription.Height = (backBufferDescription.Height == 0) ? mTargetWindow->GetClientHeight() : backBufferDescription.Height;
		
		SafeRelease(mBackBufferView);
		SafeRelease(mDepthStencilBuffer);
		SafeRelease(mDepthStencilView);

		if (FAILED(mSwapChain->ResizeBuffers(0, backBufferDescription.Width, backBufferDescription.Height, DXGI_FORMAT_UNKNOWN, 0)))
			return false;

		if (!CreateBackBufferView())
			return false;

		if (!CreateDepthStencilBuffer(depthBufferDescription))
			return false;

		mBackBufferSize = backBufferDescription;
		mDepthBufferSize = depthBufferDescription;

		return true;
	}

	void D3DContext::Clear(const D3DXCOLOR& color)
	{
		mDevice->ClearRenderTargetView(mBackBufferView, color);
		mDevice->ClearDepthStencilView(mDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
	}
		
	void D3DContext::SwapBuffers()
	{
		mSwapChain->Present(0, 0);
	}

	bool D3DContext::CreateDeviceAndSwapChain(Description description)
	{
		unsigned int deviceFlags = 0;
#ifdef DEBUG_MODE
		deviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

		// Create the swap chain description
		description.BackBuffer.Width = (description.BackBuffer.Width == 0) ? mTargetWindow->GetClientWidth() : description.BackBuffer.Width;
		description.BackBuffer.Height = (description.BackBuffer.Height == 0) ? mTargetWindow->GetClientHeight() : description.BackBuffer.Height;
		
		DXGI_SWAP_CHAIN_DESC scDescription;
		ZeroMemory(&scDescription, sizeof(scDescription));
		scDescription.BufferCount = 1;
		scDescription.BufferDesc.Width = description.BackBuffer.Width;		
		scDescription.BufferDesc.Height = description.BackBuffer.Height;
		scDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDescription.BufferDesc.RefreshRate.Numerator = 60;
		scDescription.BufferDesc.RefreshRate.Denominator = 1;
		scDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDescription.OutputWindow = mTargetWindow->GetHandle();
		scDescription.SampleDesc.Count = 1;
		scDescription.SampleDesc.Quality = 0;
		scDescription.Windowed = !description.Fullscreen;

		// Create the device and the swap chain
		// Try different drivers for Direct3D, hardware first, reference only if that fails.
		D3D10_DRIVER_TYPE driverTypes[] = { D3D10_DRIVER_TYPE_HARDWARE, D3D10_DRIVER_TYPE_REFERENCE };
		unsigned int driverTypeCount = sizeof(driverTypes) / sizeof(driverTypes[0]);

		HRESULT result = S_OK;
		for (unsigned int i = 0; i < driverTypeCount; ++i)
		{
			result = D3D10CreateDeviceAndSwapChain(NULL,
												   driverTypes[i],
												   NULL,
												   deviceFlags,
												   D3D10_SDK_VERSION,
												   &scDescription,
												   &mSwapChain,
												   &mDevice);

			if (SUCCEEDED(result))
				break;
		}

		if (FAILED(result))
			return false;

		mBackBufferSize.Width = description.BackBuffer.Width;
		mBackBufferSize.Height = description.BackBuffer.Height;

		return true;
	}

	bool D3DContext::CreateBackBufferView()
	{
		// Create a render target view for the back buffer
		ID3D10Texture2D* backBuffer;

		HRESULT result = mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer));
		if (FAILED(result))
		{
			SafeRelease(backBuffer);
			return false;
		}

		result = mDevice->CreateRenderTargetView(backBuffer, NULL, &mBackBufferView);
		if (FAILED(result))
		{
			SafeRelease(backBuffer);
			return false;
		}

		SafeRelease(backBuffer);

		return SUCCEEDED(result);
	}

	bool D3DContext::CreateDepthStencilBuffer(Description::Buffer description)
	{
		description.Width = (description.Width == 0) ? mBackBufferSize.Width : description.Width;
		description.Height = (description.Height == 0) ? mBackBufferSize.Height : description.Height;

		assert(description.Width >= mBackBufferSize.Width);
		assert(description.Height >= mBackBufferSize.Height);

		// Create depth stencil texture
		D3D10_TEXTURE2D_DESC depthTextureDescription;
		depthTextureDescription.Width = description.Width;
		depthTextureDescription.Height = description.Height;
		depthTextureDescription.MipLevels = 1;
		depthTextureDescription.ArraySize = 1;
		depthTextureDescription.Format = DXGI_FORMAT_D32_FLOAT;
		depthTextureDescription.SampleDesc.Count = 1;
		depthTextureDescription.SampleDesc.Quality = 0;
		depthTextureDescription.Usage = D3D10_USAGE_DEFAULT;
		depthTextureDescription.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		depthTextureDescription.CPUAccessFlags = 0;
		depthTextureDescription.MiscFlags = 0;

		HRESULT result = mDevice->CreateTexture2D(&depthTextureDescription, NULL, &mDepthStencilBuffer);
		if (FAILED(result))
			return false;

		// Create depth stencil view
		D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription;
		depthStencilViewDescription.Format = depthTextureDescription.Format;
		depthStencilViewDescription.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDescription.Texture2D.MipSlice = 0;
	
		result = mDevice->CreateDepthStencilView(mDepthStencilBuffer, &depthStencilViewDescription, &mDepthStencilView);
		if (FAILED(result))
			return false;

		mDepthBufferSize.Width = description.Width;
		mDepthBufferSize.Height = description.Height;

		return true;
	}

}