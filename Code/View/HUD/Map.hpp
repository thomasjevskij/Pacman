#ifndef MAP_HPP
#define MAP_HPP

#include "ModelDataInterface.hpp"
#include "UISurface.hpp"
#include "Sprite.hpp"

namespace View
{
	class Map
	{
	public:
		Map();

		void Draw(UISurface& surface, Model::ModelDataInterface& model, const D3DXVECTOR2& position, bool renderGhosts);

		static const unsigned int C_CELL_PADDING;
		static const unsigned int C_CELL_SIZE;
		static const D3DXCOLOR C_BACKGROUND_COLOR;
		static const D3DXCOLOR C_WALL_COLOR;
		static const D3DXCOLOR C_PELLET_COLOR;
		static const D3DXCOLOR C_POWERPELLET_COLOR;
	private:
		View::Sprite mActorSprite;
		View::Sprite mCellSprite;
		View::Sprite mBackgroundSprite;

		void DrawCells(UISurface& surface, const D3DXVECTOR2& mapPosition, const std::vector<Model::Coord>& cells, const D3DXCOLOR& color);
		void DrawActor(UISurface& surface, const D3DXVECTOR2& mapPosition, const D3DXVECTOR2& actorPosition, const D3DXCOLOR& color);
	};
}

#endif