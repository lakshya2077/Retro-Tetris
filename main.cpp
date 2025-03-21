#pragma warning (disable:4996)

#include "raylib.h"
#include "game.h"
#include "colors.h"
#include <iostream>

double previousTime = 0;

bool eventTriggered(double interval)
{
	double currentTime = GetTime();

	if (currentTime - previousTime >= interval)
	{
		previousTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	InitWindow(500, 620, "Tetris");
	SetTargetFPS(60);

	Game* game = new Game{};
	Font font = LoadFontEx("Font/monogram.ttf",64,0,0);

	char* scoreText = new char[10];

	while (!WindowShouldClose())
	{
		//UpdateMusicStream(game->music);
		game->handleInput();

		if(eventTriggered(0.2))
			game->MoveBlockDown();

		BeginDrawing();
		ClearBackground(darkblue);

		DrawTextEx(font, "Score", { 365,15 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320,55,170,60 }, 0.3, 6, lightblue);

		sprintf(scoreText, "%d", game->score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2,65 }, 38, 2, WHITE);


		DrawTextEx(font, "Next", { 370,175 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320,215,170,180 }, 0.3, 6, lightblue);

		if (game->GameOver)
			DrawTextEx(font, "GAME OVER", { 320,450 }, 38, 2, WHITE);

		game->Draw();

		EndDrawing();
	}

	delete game;
	UnloadFont(font);
	CloseWindow();
	return 0;
}