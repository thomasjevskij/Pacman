#include "Level.hpp"
#include "FreeImage.h"
#include <cassert>
#include <algorithm>

namespace Model
{

	Cell::Cell()
		: Coordinate(0, 0), Type(0) {}

	Cell::Cell(int x, int y, CellType type)
		: Coordinate(x, y), Type(type) {}

	Cell::Cell(Coord coordinate, CellType type)
		: Coordinate(coordinate), Type(type) {}

	Level::Level()
	{
		mHeight = 0;
		mWidth = 0;
	}
	
	Level::Level(const std::string& path)
	{
		FIBITMAP *imgFile = FreeImage_Load(FIF_PNG, path.c_str(), PNG_DEFAULT);
		mHeight = FreeImage_GetHeight(imgFile);
		mWidth = FreeImage_GetWidth(imgFile);

		for (int i = mHeight - 1; i >= 0; --i)
		{
			for (unsigned int j = 0; j < mWidth; ++j)
			{
				RGBQUAD color;
			
				BOOL a = FreeImage_GetPixelColor(imgFile, j, i, &color);
				assert(a != 0);

				if (color.rgbRed == 255)
				{
					if (color.rgbGreen == 255)
					{
						if (color.rgbBlue == 255)
						{
							Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_EMPTY); 
							mCells.push_back(c);
						}
						else
						{
							Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_GHOSTSPAWN);
							mCells.push_back(c);
							mGhostSpawnPositions.push_back(c.Coordinate);
						}
					}
					else
					{
						Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_POWERPELLET);
						mCells.push_back(c);
						mPowerPelletPositions.push_back(c.Coordinate);
					}
				}
				else if (color.rgbGreen == 255)
				{
					if (color.rgbBlue == 255)
					{
						Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_WALL);
						mCells.push_back(c);
						mLightPositions.push_back(c.Coordinate);
					}
					else
					{
						Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_PELLET);
						mCells.push_back(c);
						mPelletPositions.push_back(c.Coordinate);
					}
				}
				else if (color.rgbBlue == 255)
				{
					Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_PACMANSPAWN);
					mCells.push_back(c);
					mPacmanSpawnPosition = c.Coordinate;
				}
				else
				{
					Cell c = Cell(Coord(j, i), Cell::C_CELLTYPE_WALL);
					mCells.push_back(c);
					mWallPositions.push_back(c.Coordinate);
				}
			}
		}

		// DEBUG
		for(int k = -3; k < 3; ++k)
		{
			mWallPositions.push_back(Coord(k, 0));
		}

	}

	void Level::AddFood()
	{
		SetCellType(GetPacmanSpawnPosition().X, GetPacmanSpawnPosition().Y, Cell::C_CELLTYPE_FOOD);
	}

	void Level::RemoveFood()
	{
		SetCellType(GetPacmanSpawnPosition().X, GetPacmanSpawnPosition().Y, Cell::C_CELLTYPE_EMPTY);
	}

	void Level::SetEaten(int x, int y)
	{
		Cell c = GetCell(x, y);
		if (c.Type == Cell::C_CELLTYPE_PELLET)
		{
			std::vector<Coord>::iterator it = std::find(mPelletPositions.begin(), mPelletPositions.end(), c.Coordinate);
			mPelletPositions.erase(it);
		}
		else if (c.Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			std::vector<Coord>::iterator it = std::find(mPowerPelletPositions.begin(), mPowerPelletPositions.end(), c.Coordinate);
			mPelletPositions.erase(it);
		}
		SetCellType(x, y, Cell::C_CELLTYPE_EMPTY);
	}

	
	const int Level::GetWidth() const
	{
		return mWidth;
	}
	const int Level::GetHeight() const
	{
		return mHeight;
	}

	const Cell& Level::GetCell(int x, int y) const
	{
		int i = GetIndex(x, y);
		assert(i >= 0 && i < mCells.size());

		return mCells[i];
	}

	bool Level::FoodExists() const
	{
		return (GetCell(GetPacmanSpawnPosition().X, GetPacmanSpawnPosition().Y).Type == Cell::C_CELLTYPE_FOOD);
	}

	Coord Level::GetPacmanSpawnPosition() const
	{
		return mPacmanSpawnPosition;
	}
	const std::vector<Coord>& Level::GetWallPositions() const
	{
		return mWallPositions;
	}
	const std::vector<Coord>& Level::GetLightPositions() const
	{
		return mLightPositions;
	}
	const std::vector<Coord>& Level::GetPelletPositions() const
	{
		return mPelletPositions;
	}
	const std::vector<Coord>& Level::GetPowerPelletPositions() const
	{
		return mPowerPelletPositions;
	}
	const std::vector<Coord>& Level::GetGhostSpawnPositions() const
	{
		return mGhostSpawnPositions;
	}

	int Level::GetIndex(int x, int y) const
	{
		if (x >= 0 && x < mWidth &&
			y >= 0 && y < mHeight)
			return x + y * mHeight;
		else
			return -1;
	}

	void Level::SetCellType(int x, int y, Cell::CellType type)
	{
		int i = GetIndex(x, y);
		assert(i >= 0 && i < mCells.size());

		mCells[i].Type = type;
	}
}