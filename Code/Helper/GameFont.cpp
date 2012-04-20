#include "GameFont.hpp"
#include "r2-exception.hpp"

namespace Helper
{
	const unsigned int GameFont::C_WEIGHT_NORMAL = 400;
	const unsigned int GameFont::C_WEIGHT_BOLD = 700;

	GameFont::GameFont(ID3D10Device* device, const std::string& name, unsigned int height, bool italics, bool bold)
		: mDevice(device)
		, mFont(NULL)
	{
		if (!LoadFont(name, height, italics, bold))
			throw r2ExceptionIOM("Failed to load font: " + name);
	}

	GameFont::~GameFont()
	{
		SafeRelease(mFont);
	}



	void GameFont::WriteText(const std::string& text, const Helper::Point2i& position, const D3DXCOLOR& color)
	{
		RECT destinationRect = {position.X, position.Y, 0, 0};

		mFont->DrawTextA(NULL,				// No sprite needed for few print outs
						text.c_str(),		// String to print
						-1,					// Characters in print string (-1 since the string is null terminated)
						&destinationRect,	// The rectangle to draw text to
						DT_NOCLIP,			// How to act when the text reaches rectangle edge
						color);				// Text color
	}

	void GameFont::WriteText(const std::string& text, RECT destinationRect, const D3DXCOLOR& color, 
			AlignHorizontal alignHor, AlignVertical alignVert)
	{
		UINT alignment = DT_WORDBREAK;				// Set the alignment to break between rows

		switch (alignHor)							// Set the horizontal alignment based on the enum AlignHorizontal
		{
			case(Left):
				alignment |= DT_LEFT;
				break;
			case(Center):
				alignment |= DT_CENTER;
				break;
			case(Right):
				alignment |= DT_RIGHT;
				break;
			default:
				alignment |= DT_LEFT;
		}

		switch (alignVert)							// Set the vertical alignment based on the enum AlignVertical
		{
			case(Top):
				alignment |= DT_TOP;
				break;
			case(Middle):			// If vertical alignment is middle, text must be on one line
				alignment |= DT_VCENTER | DT_SINGLELINE;
				break;
			case(Bottom):			// If vertical alignment is bottom, text must be on one line
				alignment |= DT_BOTTOM | DT_SINGLELINE;
				break;
			default:
				alignment |= DT_TOP;
		}

		mFont->DrawTextA(NULL,				// No sprite needed for few print outs
						text.c_str(),		// String to print
						-1,					// Characters in print string (-1 since the string is null terminated)
						&destinationRect,	// The rectangle to draw text to
						alignment,			// How to act when the text reaches rectangle edge
						color);				// Text color
	}



	bool GameFont::LoadFont(const std::string& name, unsigned int height, bool italics, bool bold)
	{
		// Set the font description
		mFontDesc.Height			= height;				// Logical units height of the character cell
		mFontDesc.Width				= 0;					// Logical units width of the characters (0 - use aspect ratio)
		if(bold)
			mFontDesc.Weight		= C_WEIGHT_BOLD;		// Font weight (0-1000: 0 - use default, 400 - normal, 700 - bold)
		else
			mFontDesc.Weight		= C_WEIGHT_NORMAL;		// Font weight (0-1000: 0 - use default, 400 - normal, 700 - bold)
		mFontDesc.MipLevels			= 1;					// Map texture space identically to screen space
		mFontDesc.Italic			= italics;				// Whether the font should be in italics or not
		mFontDesc.CharSet			= DEFAULT_CHARSET;		// Use default character set
		mFontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;	// Default output precision (match requested height width etc)
		mFontDesc.Quality			= DEFAULT_QUALITY;		// Default output quality
		mFontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;
		
		// Copy the font name into the description
		strncpy_s(mFontDesc.FaceName, name.c_str(), 31);
		mFontDesc.FaceName[31] = '\0';

		// Recreate the font
		return RecreateFontFromDescription();
	}

	bool GameFont::SetHeight(unsigned int height)
	{
		mFontDesc.Height = height;
		return RecreateFontFromDescription();
	}

	bool GameFont::SetStyle(bool italics, bool bold)
	{
		if (bold)
			mFontDesc.Weight = C_WEIGHT_BOLD;
		else
			mFontDesc.Weight = C_WEIGHT_NORMAL;
		mFontDesc.Italic = italics;

		return RecreateFontFromDescription();
	}



	unsigned int GameFont::GetHeight()
	{
		return mFontDesc.Height;
	}

	bool GameFont::IsBold() const
	{
		return mFontDesc.Weight == C_WEIGHT_BOLD;
	}

	bool GameFont::IsItalics() const
	{
		return mFontDesc.Italic == TRUE;
	}



	bool GameFont::RecreateFontFromDescription()
	{
		SafeRelease(mFont);
		return SUCCEEDED(D3DX10CreateFontIndirect(mDevice, &mFontDesc, &mFont));
	}
}