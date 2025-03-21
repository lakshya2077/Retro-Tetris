#include "game.h"
#include <iostream>

Game::Game()
{
	grid = new Grid{};
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	GameOver = false;
	score = 0;

	InitAudioDevice();
	/*music = LoadMusicStream("Sounds/music.mp3");
	PlayMusicStream(music);*/

	rotateSound = LoadSound("Sounds/rotate.mp3");
	clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	/*UnloadMusicStream(music);*/
	CloseAudioDevice();
	delete grid;
	for (Block* item : blocks)
		delete item;
}

Block *Game::GetRandomBlock(void)
{
	if (blocks.empty())
		blocks = GetAllBlocks();

	int randomIndex = random(0, blocks.size()-1);
	Block *block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	
	return block;
}

std::vector<Block*> Game::GetAllBlocks(void)
{
	return { new LBlock{},new JBlock{},new IBlock{},new OBlock{},new SBlock{},new TBlock{},new ZBlock{}};
}

void Game::Draw(void)
{
	grid->Draw();
	currentBlock->Draw(11,11);

	switch (nextBlock->color_id)
	{
	case 3:
		nextBlock->Draw(255,290);
		break;
	case 4:
		nextBlock->Draw(255, 280);
		break;
	default:
		nextBlock->Draw(270, 270);
		break;
	}
}

void Game::handleInput(void)
{
	int keyInput = GetKeyPressed();

	switch (keyInput)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;

	case KEY_RIGHT:
		MoveBlockRight();
		break;

	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		break;

	case KEY_UP:
		RotateBlock();
		break;

	case KEY_SPACE:
		if (GameOver)
			Reset();
		break;

	default:
		break;
	}

}

void Game::MoveBlockLeft(void)
{
	if (!GameOver)
	{
		currentBlock->Move(0, -1);

		if (IsBlockOutside() || !BlockFits())
			currentBlock->Move(0, 1);
	}
}

void Game::MoveBlockRight(void)
{
	if (!GameOver)
	{
		currentBlock->Move(0, 1);

		if (IsBlockOutside() || !BlockFits())
			currentBlock->Move(0, -1);
	}
}

void Game::MoveBlockDown(void)
{
	if (!GameOver)
	{
		currentBlock->Move(1, 0);

		if (IsBlockOutside() || !BlockFits())
		{
			currentBlock->Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateBlock(void)
{
	if (!GameOver)
	{
		currentBlock->Rotate();

		if (IsBlockOutside() || !BlockFits())
			currentBlock->UndoRotation();
		else
			PlaySound(rotateSound);
	}
}

bool Game::IsBlockOutside(void)
{
	std::vector<Position> tiles = currentBlock->Get_Block_Pos();

	for (Position item : tiles)
	{
		if (grid->IsCellOutside(item.row,item.column))
			return true;
	}
	return false;
}

bool Game::BlockFits(void)
{
	std::vector<Position> tiles = currentBlock->Get_Block_Pos();

	for (Position item : tiles)
		if (!grid->IsCellEmpty(item.row, item.column))
			return false;

	return true;
}

void Game::LockBlock(void)
{
	std::vector<Position> tiles = currentBlock->Get_Block_Pos();

	for (Position item : tiles)
		grid->grid[item.row][item.column] = currentBlock->color_id;

	currentBlock = nextBlock;

	if (!BlockFits())
	{
		GameOver = true;
		return;
	}

	nextBlock = GetRandomBlock();

	int rowsCleared=grid->ClearFullRows();

	if (rowsCleared)
	{
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
}
	
void Game::UpdateScore(int rowsCleared, int blocksDown)
{
	score += blocksDown;

	switch (rowsCleared)
	{
	case 1:
		score += 100;
		break;

	case 2:
		score += 300;
		break;

	case 3:
		score += 500;
		break;

	default:
		break;
	}
}

void Game::Reset(void)
{
	grid->Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	GameOver = false;
	score = 0;
}