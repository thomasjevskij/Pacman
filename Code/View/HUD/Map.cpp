#include <vector>
#include "Map.hpp"
#include "Ghost.hpp"

namespace View
{
	const unsigned int Map::C_CELL_SIZE = 16;
	const unsigned int Map::C_CELL_PADDING = 4;
	const D3DXCOLOR Map::C_BACKGROUND_COLOR(0.5f, 0.5f, 0.5f, 1.0f);
	const D3DXCOLOR Map::C_WALL_COLOR(0.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR Map::C_PELLET_COLOR(1.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR Map::C_POWERPELLET_COLOR(0.0f, 0.0f, 1.0f, 1.0f);

	Map::Map()
		: mCellSprite("whitePixel.png")
		, mBackgroundSprite("whitePixel.png")
		, mActorSprite("circle.png")
	{
		
	}

	void Map::Draw(UISurface& surface, Model::ModelDataInterface& model, const D3DXVECTOR2& position, bool renderGhosts)
	{
		const Model::Level& level = model.GetLevel();

		const std::vector<Model::Coord>& wallPositions = level.GetWallPositions();
		const std::vector<Model::Coord>& pelletPositions = level.GetPelletPositions();
		const std::vector<Model::Coord>& powerPelletPositions = level.GetPowerPelletPositions();
		model.GetGhostPositions();
		
		// Draw background
		mBackgroundSprite.SetScale(level.GetWidth() * C_CELL_SIZE, 
								   level.GetHeight() * C_CELL_SIZE);
		mBackgroundSprite.SetPosition(position);
		mBackgroundSprite.SetTintColor(C_BACKGROUND_COLOR);
		surface.Draw(mBackgroundSprite);

		// Draw the static cells
		DrawCells(surface, position, wallPositions, C_WALL_COLOR);
		DrawCells(surface, position, pelletPositions, C_PELLET_COLOR);
		DrawCells(surface, position, powerPelletPositions, C_POWERPELLET_COLOR);

		// Draw Pacman's position
		DrawActor(surface, position, D3DXVECTOR2(model.GetPacmanPosition().X, model.GetPacmanPosition().Y), C_PELLET_COLOR);

		// Draw the ghosts' positions
		if (renderGhosts)
		{
			const std::vector<Model::Coord>& ghostPositions = model.GetGhostPositions();
			for (int i = 0; i < ghostPositions.size(); ++i)
			{
				DrawActor(surface, position, D3DXVECTOR2(ghostPositions[i].X, ghostPositions[i].Y), View::Ghost::C_COLORS[i]);
			}
		}
	}

	void Map::DrawCells(UISurface& surface, const D3DXVECTOR2& mapPosition, const std::vector<Model::Coord>& cells, const D3DXCOLOR& color)
	{
		for (std::vector<Model::Coord>::const_iterator it = cells.begin(); it != cells.end(); ++it)
		{
			mCellSprite.SetScale(C_CELL_SIZE);
			mCellSprite.SetPosition( mapPosition + D3DXVECTOR2(it->X * C_CELL_SIZE * 0.5f, it->Y * C_CELL_SIZE * 0.5f) );
			mCellSprite.SetTintColor(color);
			surface.Draw(mCellSprite);
		}
	}

	void Map::DrawActor(UISurface& surface, const D3DXVECTOR2& mapPosition, const D3DXVECTOR2& actorPosition, const D3DXCOLOR& color)
	{
		mActorSprite.SetPosition( mapPosition + D3DXVECTOR2(actorPosition.x * C_CELL_SIZE * 0.5f, actorPosition.y * C_CELL_SIZE * 0.5f) );
		mActorSprite.SetTintColor(color);
		surface.Draw(mActorSprite);
	}
}