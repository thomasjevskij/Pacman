#include "D3DContext.hpp"

namespace Framework
{
	D3DContext::Viewport::Viewport()
		: Left(0.0f)
		, Top(0.0f)
		, Width(1.0f)
		, Height(1.0f)
	{
		
	}

	D3DContext::Viewport::Viewport(float left, float top, float width, float height)
		: Left(left)
		, Top(top)
		, Width(width)
		, Height(height)
	{
		
	}

	D3DContext::D3DContext(ApplicationWindow* targetWindow, const Description& description)
	{

	}

	D3DContext::~D3DContext() throw()
	{

	}

	// Clear the backbuffer and the depth/stencil buffer
	void D3DContext::Clear(const D3DXCOLOR& color)
	{

	}
		
	// Swap the frontbuffer and the backbuffer
	void D3DContext::SwapBuffers()
	{

	}
}