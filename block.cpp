#include "block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	rowOffset = 0;
	columnOffset = 0;
	colors = Get_cell_Colors();
}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = Get_Block_Pos();

	for (Position item : tiles)
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[color_id]);
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::Rotate(void)
{
	rotationState++;

	if (rotationState == cells.size())
		rotationState = 0;
}

void Block::UndoRotation(void)
{
	rotationState--;

	if (rotationState == -1)
		rotationState = cells.size() - 1;
}

std::vector<Position> Block::Get_Block_Pos(void)
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> moved_tiles;

	for (Position item : tiles)
	{
		Position new_Pos = { item.row + rowOffset,item.column + columnOffset };
		moved_tiles.push_back(new_Pos);
	}
	return moved_tiles;
}