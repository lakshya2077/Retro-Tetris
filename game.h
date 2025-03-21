#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "random.h"

class Game
{
public:

	Game();
	~Game();

	void Draw(void);
	void MoveBlockDown(void);
	void handleInput(void);

	bool GameOver;
	int score;
	//Music music;

private:

	Block* GetRandomBlock(void);
	std::vector<Block*> GetAllBlocks(void);

	void RotateBlock(void);
	void MoveBlockLeft(void);
	void MoveBlockRight(void);

	bool IsBlockOutside(void);
	bool BlockFits(void);

	void LockBlock(void);
	void Reset(void);
	void UpdateScore(int rowsCleared,int blocksDown);
	
	Grid* grid;
	std::vector<Block*> blocks;
	Block *currentBlock;
	Block *nextBlock;

	Sound rotateSound;
	Sound clearSound;
};
