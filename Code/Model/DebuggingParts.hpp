#ifndef DEBUGSTUFF_HPP
#define DEBUGSTUFF_HPP

#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
 
namespace Model
{
	template <typename T>
	void DbgOutFloat(std::string label, T value ) 
	{
		std::stringstream strs;
		strs << value;
		label.append(strs.str()) ;
		const char *c_str =label.c_str() ;
		OutputDebugString( c_str ) ;
	}
}
#endif