#include <iostream>
#include "raylib.h"

class PlayerCircle
{
public:
	const int START_POSITION_X = 30;
	const int START_POSITION_Y = 375;
	const int RADIUS = 25.0f;

	int currentXPosition = 30;
	int currentYPosition = 375;
};

class Game
{
public:
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	int level = 1;
};

class RectangleObject
{
public:
	int CurrentXPosition = 120;
	int CurrentYPosition = 0;
	int Width = 50;
	int Height = 50;
	int DirectionX = 1;
	int DirectionY = 1;
	int MoveSpeed = 10;
	Color ObjectColor{ RED };

	RectangleObject() = default;

	RectangleObject(int startPositionX, int startPositionY, const int width, const int height, int directionX, int directionY, int moveSpeed, const Color color)
	{
		CurrentXPosition = startPositionX;
		CurrentYPosition = startPositionY;
		Width = width;
		Height = height;
		DirectionX = directionX;
		DirectionY = directionY;
		MoveSpeed = moveSpeed;
		ObjectColor = color;
	}
};

int main()
{

	auto* game = new Game();
	auto* playerCircle = new PlayerCircle();
	const auto* rectangleObject = new RectangleObject[5];

	RectangleObject rectangle1 = rectangleObject[0];
	rectangle1.MoveSpeed = 12;

	InitWindow(game->SCREEN_WIDTH, game->SCREEN_HEIGHT, "Cross Over");
	SetTargetFPS(144);

	bool isCollidedWithRectangle = false;

	// ------------------------------------------ GAME LOOP START -------------------------------------
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------


		// --------------------------------- SET PLAYER CIRCLE EDGES ----------------------------------
		const int circleUpperYEdge = playerCircle->currentYPosition - playerCircle->RADIUS;
		const int circleBottomYEdge = playerCircle->currentYPosition + playerCircle->RADIUS;
		const int circleRightXEdge = playerCircle->currentXPosition + playerCircle->RADIUS;
		const int circleLeftXEdge = playerCircle->currentXPosition - playerCircle->RADIUS;
		// --------------------------------------------------------------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const int rectangleUpperYEdge = rectangle1.CurrentYPosition;
		const int rectangleBottomYEdge = rectangle1.CurrentYPosition + rectangle1.Height;
		const int rectangleRightXEdge = rectangle1.CurrentXPosition + rectangle1.Width;
		const int rectangleLeftXEdge = rectangle1.CurrentXPosition;
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- MOVEMENT INPUTS --------------------------------------
		if (IsKeyDown(KEY_D) && circleRightXEdge < game->SCREEN_WIDTH)
		{
			playerCircle->currentXPosition += 3;
		}
		if (IsKeyDown(KEY_A) && circleLeftXEdge > 0)
		{
			playerCircle->currentXPosition -= 3;
		}
		if (IsKeyDown(KEY_W) && circleUpperYEdge > 0)
		{
			playerCircle->currentYPosition -= 3;
		}
		if (IsKeyDown(KEY_S) && circleBottomYEdge < game->SCREEN_HEIGHT)
		{
			playerCircle->currentYPosition += 3;
		}
		// --------------------------------------------------------------------------------------------



		if (!isCollidedWithRectangle)
		{
			// ------------------------------ MOVE RECTANGLE TO UP AND DOWN -------------------------------
			rectangle1.CurrentYPosition += rectangle1.DirectionY * rectangle1.MoveSpeed;

			if (rectangle1.CurrentYPosition > game->SCREEN_HEIGHT - rectangle1.Height || rectangle1.CurrentYPosition < 0)
			{
				rectangle1.DirectionY = -rectangle1.DirectionY;
			}
			// --------------------------------------------------------------------------------------------


			// -------------------------------------- DRAW OBJECTS ----------------------------------------
			DrawCircle(playerCircle->currentXPosition, playerCircle->currentYPosition, playerCircle->RADIUS, PURPLE);

			DrawRectangle(rectangle1.CurrentXPosition, rectangle1.CurrentYPosition,
				rectangle1.Width, rectangle1.Height, rectangle1.ObjectColor);
			// --------------------------------------------------------------------------------------------
		}
		else
		{
			DrawText("GAME OVER!", 420, 325, 25, RED);

			DrawText("PRESS ENTER TO TRY AGAIN", 315, 375, 25, GREEN);

			if (IsKeyPressed(KEY_ENTER))
			{
				playerCircle->currentXPosition = playerCircle->START_POSITION_X;
				playerCircle->currentYPosition = playerCircle->START_POSITION_Y;
				isCollidedWithRectangle = false;
			}
		}


		if (circleUpperYEdge <= rectangleBottomYEdge &&
			circleBottomYEdge >= rectangleUpperYEdge &&
			circleRightXEdge >= rectangleLeftXEdge &&
			circleLeftXEdge <= rectangleRightXEdge)
		{
			isCollidedWithRectangle = true;
		}


		// ------------------------------------- GAME LOGIC END ---------------------------------------

		EndDrawing();
	}
	// ----------------------------------------- GAME LOOP END ----------------------------------------

	CloseWindow();
}