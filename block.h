#pragma once
#include "raylib.h"
#include "colors.h"
#include "position.h"
#include <vector>
#include <map>


class Block
{
public:
	Block();
	void Draw(int offsetX,int offsetY);
	void Move(int rows, int columns);
	void Rotate(void);
	void UndoRotation(void);
	std::vector<Position> Get_Block_Pos(void);

	int color_id;
	std::map<int, std::vector<Position>> cells;

private:

	int cellSize;
	int rotationState;
	int rowOffset;
	int columnOffset;
	std::vector<Color> colors;
};



