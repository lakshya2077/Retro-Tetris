#pragma once
#include <vector>
#include "raylib.h"

class Grid
{
public:
	Grid();
	~Grid();
	void Initialize(void);
	void Print(void);
	void Draw(void);
	bool IsCellOutside(int row,int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows(void);


	int** grid;
private:

	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int gradient);


	int numRows;
	int numColumns;
	int cellSize;
	std::vector<Color> colors;

};
