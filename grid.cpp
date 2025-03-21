#include "grid.h"
#include "colors.h"
#include <iostream>

Grid::Grid()
{
	numRows = 20;
	numColumns = 10;
	cellSize = 30;

	//Allocating memory for 2d array
	grid = new int* [numRows];
	for (int i = 0; i < numRows; i++)
		grid[i] = new int[numColumns];

	Initialize();
	colors = Get_cell_Colors();
}

Grid::~Grid()
{
	for (int i = 0; i < numRows; i++)
		delete[] grid[i];
	delete[] grid;
}

void Grid::Initialize(void)
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
			grid[i][j] = 0;
}

void Grid::Print(void)
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
			std::cout<<grid[i][j]<<" ";
		std::cout << "\n";
	}
}

void Grid::Draw(void)
{
	for (int i = 0; i < numColumns; i++)
		for (int j = 0; j < numRows; j++)
		{
			int cellvalue = grid[j][i];
			DrawRectangle(i * cellSize + 11, j * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellvalue]);
		}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numColumns)
		return false;
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
		return true;
	return false;
}

bool Grid::IsRowFull(int row)
{
	for (int i = 0; i < numColumns; i++)
		if (grid[row][i] == 0)
			return false;
	
	return true;
}

void Grid::ClearRow(int row)
{
	for (int i = 0; i < numColumns; i++)
		grid[row][i] = 0;
}

void Grid::MoveRowDown(int row, int gradient)
{
	for (int i = 0; i < numColumns; i++)
	{
		grid[row + gradient][i] = grid[row][i];
		grid[row][i] = 0;
	}
}

int Grid::ClearFullRows(void)
{
	int completed = 0;
	for (int i = numRows - 1; i >= 0; i--)
	{
		if (IsRowFull(i))
		{
			ClearRow(i);
			completed++;
		}

		else if(completed/*==2*/)
			MoveRowDown(i, completed);
	}

	return completed;
}