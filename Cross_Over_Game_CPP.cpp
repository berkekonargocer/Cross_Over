#include <iostream>
#include "raylib.h"

int main()
{
	constexpr int WIDTH = 1024;
	constexpr int HEIGHT = 768;

	constexpr int START_POINT_X = 30;
	constexpr int START_POINT_Y = 375;
	constexpr float RADIUS = 25.0f;

	int circleCurrentXPoint = 30;
	int circleCurrentYPoint = 375;

	InitWindow(WIDTH, HEIGHT, "Cross Over");


	SetTargetFPS(144);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------

		if (IsKeyDown(KEY_D) && circleCurrentXPoint < WIDTH - RADIUS)
		{
			circleCurrentXPoint += 3;
		}
		if (IsKeyDown(KEY_A)&& circleCurrentXPoint > 1 + RADIUS)
		{
			circleCurrentXPoint -= 3;
		}
		if (IsKeyDown(KEY_W) && circleCurrentYPoint > 1 + RADIUS)
		{
			circleCurrentYPoint -= 3;
		}
		if (IsKeyDown(KEY_S) && circleCurrentYPoint < HEIGHT - RADIUS)
		{
			circleCurrentYPoint += 3;
		}

		DrawCircle(circleCurrentXPoint, circleCurrentYPoint, RADIUS, PURPLE);

		// ------------------------------------- GAME LOGIC END ---------------------------------------

		EndDrawing();
	}
}