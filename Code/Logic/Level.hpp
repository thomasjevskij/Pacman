#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

namespace Model
{
	struct Coord
	{
		Coord();
		Coord(int x, int y);
		bool operator==(const Coord& rhs) const;
		int X, Y;
	};

	struct Cell
	{
		typedef int CellType;
		static const CellType C_CELLTYPE_EMPTY = 0;
		static const CellType C_CELLTYPE_PELLET = 1;
		static const CellType C_CELLTYPE_POWERPELLET = 2;
		static const CellType C_CELLTYPE_FOOD = 3;
		static const CellType C_CELLTYPE_WALL = 4;
		static const CellType C_CELLTYPE_PACMANSPAWN = 5;
		static const CellType C_CELLTYPE_GHOSTSPAWN = 6;

		Cell();
		Cell(int x, int y, CellType type);
		Cell(Coord coordinate, CellType type);


		Coord Coordinate;
		CellType Type;
	
	};

	class Level
	{
	public:
		// Reads a level from a png file
		Level(const std::string& path);

		// Sets food to existing state
		void AddFood();

		// Removes food
		void RemoveFood();

		// Removes food, pellet or powerpellet
		void SetEaten(int x, int y);

	

		// Checks if food exists or not
		bool FoodExists() const;

		const Cell& GetCell(int x, int y) const;
		Coord GetPacmanSpawnPosition() const;
		const std::vector<Coord>& GetWallPositions() const;
		const std::vector<Coord>& GetLightPositions() const;
		const std::vector<Coord>& GetPelletPositions() const;
		const std::vector<Coord>& GetPowerPelletPositions() const;
		const std::vector<Coord>& GetGhostSpawnPositions() const;
	private:
		// Converts x and y coordinates to the corresponding index in mCells. Returns -1 if invalid x or y is passed
		int GetIndex(int x, int y) const;
		void SetCellType(int x, int y, Cell::CellType type);

		std::vector<Cell> mCells;
		Coord mPacmanSpawnPosition;
		std::vector<Coord> mWallPositions;
		std::vector<Coord> mLightPositions;
		std::vector<Coord> mPelletPositions;
		std::vector<Coord> mPowerPelletPositions;
		std::vector<Coord> mGhostSpawnPositions;

		int mHeight;
		int mWidth;
	};
}

#endif