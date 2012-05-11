#include "DebuggingParts.hpp"

namespace Model
{
	void DbgOutFloat(std::string label, float value ) 
	{
		std::stringstream strs;
		strs << value;
		label.append(strs.str()) ;
		const char *c_str =label.c_str() ;
		OutputDebugString( c_str ) ;
	}
}