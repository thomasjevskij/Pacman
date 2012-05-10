#ifndef SPRITE_FONT_HPP
#define SPRITE_FONT_HPP

#include <string>
#include <vector>
#include "Sprite.hpp"

namespace View
{
	class SpriteFont
	{
	public:
		SpriteFont(const std::string& filename);

		// Get the sprite for any given character.
		const Sprite& GetGlyphSprite(const char c) const;

		// Get the sprite for the entire font chart.
		const Sprite& GetFontSprite() const;

		// Get the width/height of an arbitrary character (all characters
		// use the same size).
		unsigned int GetCharacterHeight() const;
		unsigned int GetCharacterWidth() const;
	private:
		static const int C_FONT_ROWS;
		static const int C_FONT_COLS;

		unsigned int mCharacterWidth;
		unsigned int mCharacterHeight;
		Sprite mFontSprite;
		std::vector<Sprite> mGlyphSprites;
	};
}

#endif