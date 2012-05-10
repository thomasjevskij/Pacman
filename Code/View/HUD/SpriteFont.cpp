#include "SpriteFont.hpp"

namespace View
{
	const int SpriteFont::C_FONT_ROWS = 11;
	const int SpriteFont::C_FONT_COLS = 9;

	SpriteFont::SpriteFont(const std::string& filename)
		: mFontSprite(filename)
	{
		float charWidth = 1.0f / C_FONT_COLS;
		float charHeight = 1.0f / C_FONT_ROWS;
		mCharacterWidth = charWidth * C_FONT_COLS;
		mCharacterHeight = charHeight * C_FONT_ROWS;

		for (int y = 0; y < C_FONT_ROWS; ++y)
		{
			for (int x = 0; x < C_FONT_COLS; ++x)
			{
				Sprite s(filename);
				s.SetUVCoordinates(x * charWidth, y * charHeight, charWidth, charHeight);

				mGlyphSprites.push_back(s);
			}
		}
	}

	const Sprite& SpriteFont::GetGlyphSprite(const char c) const
	{
		return mGlyphSprites[static_cast<size_t>(c - 32)];
	}

	const Sprite& SpriteFont::GetFontSprite() const
	{
		return mFontSprite;
	}

	unsigned int SpriteFont::GetCharacterHeight() const
	{
		return mCharacterHeight;
	}

	unsigned int SpriteFont::GetCharacterWidth() const
	{
		return mCharacterWidth;
	}
}