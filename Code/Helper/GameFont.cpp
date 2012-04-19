#include "GameFont.hpp"

namespace Helper
{
	GameFont::GameFont() : mFont(NULL) {}

	GameFont::GameFont(ID3D10Device* graphicsDevice, TCHAR* name, int size, bool italic, bool bold)
	{
		mGraphicsDevice = graphicsDevice;

		// Create the font description
		mFontDesc.Height			= size;					// Logical units height of the character cell
		mFontDesc.Width				= 0;					// Logical units width of the characters (0 - use aspect ratio)
		if(bold)
			mFontDesc.Weight		= 700;					// Font weight (0-1000: 0 - use default, 400 - normal, 700 - bold)
		else
			mFontDesc.Weight		= 400;					// Font weight (0-1000: 0 - use default, 400 - normal, 700 - bold)
		mFontDesc.MipLevels			= 1;					// Map texture space identically to screen space
		mFontDesc.Italic			= italic;				// Whether the font should be italic or not
		mFontDesc.CharSet			= DEFAULT_CHARSET;		// Use default character set
		mFontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;	// Default output precision (match requested height width etc)
		mFontDesc.Quality			= DEFAULT_QUALITY;		// Default output quality
		mFontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;
		strcpy_s(mFontDesc.FaceName, name);

		// Create the font from description
		D3DX10CreateFontIndirect(mGraphicsDevice, &mFontDesc, &mFont);
	}

	GameFont::~GameFont()
	{
		SafeRelease(mFont);
		mGraphicsDevice = NULL;
	}

	// Writes text at the specified position with the specified color
	void GameFont::WriteText(std::string text, POINT position, D3DXCOLOR textColor)
	{
		if(mFont == NULL)
			return;

		RECT destinationRect = {position.x, position.y, 0, 0};

		mFont->DrawTextA(NULL,				// No sprite needed for few print outs
						text.c_str(),		// String to print
						-1,					// Characters in print string (-1 since the string is null terminated)
						&destinationRect,	// The rectangle to draw text to
						DT_NOCLIP,			// How to act when the text reaches rectangle edge
						textColor);			// Text color
	}

	// Writes text with the specified color in a rectangle, using the specified vertical and horizontal alignment.
	// If the line goes outside the rectangle, a line break will occur (unless the vertical alignment is set to middle 
	// or bottom which require a single line of text - all line breaks are ignored)
	void GameFont::WriteText(std::string text, RECT* destinationRect, D3DXCOLOR textColor, 
		AlignHorizontal alignHor, AlignVertical alignVert)
	{
		if(mFont == NULL)
			return;

		UINT alignment			= DT_WORDBREAK;		// Set the alignment to break between rows

		switch(alignHor)							// Set the horizontal alignment based on the enum AlignHorizontal
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

		switch(alignVert)							// Set the vertical alignment based on the enum AlignVertical
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
						destinationRect,	// The rectangle to draw text to
						alignment,			// How to act when the text reaches rectangle edge
						textColor);			// Text color
	}

	// Changes the font name and updates the font
	void GameFont::ChangeFontName(TCHAR* newName)
	{
		if(mFont == NULL)
			return;

		strcpy_s(mFontDesc.FaceName, newName);								// Change the font name in the description

		D3DX10CreateFontIndirect(mGraphicsDevice, &mFontDesc, &mFont);		// Update the font
	}

	// Changes the size of the font and updates
	void GameFont::ChangeSize(int newSize)
	{
		if(mFont == NULL)
			return;

		mFontDesc.Height = newSize;											// Change the size in the description

		D3DX10CreateFontIndirect(mGraphicsDevice, &mFontDesc, &mFont);		// Update the font
	}

	// Changes whether the font is bold and italic, then font is updated
	void GameFont::ChangeBoldItalic(bool isItalic, bool isBold)
	{
		if(mFont == NULL)
			return;

		// Change the bold and italic values in the description
		if(isBold)
			mFontDesc.Weight		= 700;
		else
			mFontDesc.Weight		= 400;
		mFontDesc.Italic			= isItalic;

		D3DX10CreateFontIndirect(mGraphicsDevice, &mFontDesc, &mFont);		// Update the font

	}

	// Returns the current font size
	int GameFont::GetSize()
	{
		return mFontDesc.Height;
	}

}