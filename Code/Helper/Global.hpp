#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#if defined(DEBUG) | defined(_DEBUG)
	#define DEBUG_MODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <D3D10.h>
#include <D3DX10.h>

/**
	Inline functions for deleting/releasing and setting the pointer to NULL afterwards. Methods of courtesy.
*/
template <typename T>
inline void SafeDelete(T*& memory)
{
	delete memory;
	memory = 0;
}

template <typename T>
inline void SafeDeleteArray(T*& memory)
{
	delete [] memory;
	memory = 0;
}

template <typename T>
inline void SafeRelease(T*& handle)
{
	if (handle != 0)
	{
		handle->Release();
		handle = 0;
	}
}

#endif