#ifndef GAMEFONT_H
#define GAMEFONT_H

#include "Global.hpp"
#include "Primitives.hpp"
#include <string>

namespace Helper
{
	class GameFont
	{
	public:
		enum AlignVertical
		{
			Top, Middle, Bottom
		};

		enum AlignHorizontal
		{
			Left, Center, Right
		};


		// Load a font with the specified name, size and style.
		// The name of the font cannot be longer than 31 characters.
		GameFont(ID3D10Device* device, const std::string& name = "Times New Roman", unsigned int height = 18, 
			bool italics = false, bool bold = false);
		~GameFont() throw();

		// Draw a string with its top-left corner at the specified position.
		void WriteText(const std::string& text, const Helper::Point2i& position, const D3DXCOLOR& color = D3DXCOLOR(0, 0, 0, 1));

		// Draw a string in the specified rectangle. If the line goes outside the rectangle, a line break will occur
		// (unless the vertical alignment is set to middle or bottom which require a single line of text - all line breaks are ignored)
		void WriteText(const std::string& text, RECT destinationRect, const D3DXCOLOR& color = D3DXCOLOR(0, 0, 0, 1), 
			AlignHorizontal alignHor = Left, AlignVertical alignVert = Top);


		// Load a font with the specified name, size and style.
		// The name of the font cannot be longer than 31 characters.
		bool LoadFont(const std::string& name, unsigned int height = 18, bool italics = false, bool bold = false);
		bool SetHeight(unsigned int height);
		bool SetStyle(bool italics, bool bold);

		// Getters
		unsigned int GetHeight();
		bool IsBold() const;
		bool IsItalics() const;
	private:
		static const unsigned int C_WEIGHT_NORMAL;
		static const unsigned int C_WEIGHT_BOLD;

		ID3D10Device* mDevice;
		ID3DX10Font* mFont;
		D3DX10_FONT_DESC mFontDesc;
		
		// Recreate the font resource from mFontDesc.
		bool RecreateFontFromDescription();

		// Resource - disable copying
		GameFont(const GameFont&);
		GameFont& operator=(const GameFont&);
	};
}

#endif