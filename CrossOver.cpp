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
	int RectangleObjectPositionX = 120;
	int RectangleObjectPositionY = 0;
	int RectangleObjectWidth = 50;
	int RectangleObjectHeight = 50;
	int DirectionX = 1;
	int DirectionY = 1;
	int MoveSpeed = 10;
	Color RectangleObjectColor{ RED };

	RectangleObject() = default;

	RectangleObject(int startPositionX, int startPositionY, const int width, const int height, int directionX, int directionY, int moveSpeed, const Color color)
	{
		RectangleObjectPositionX = startPositionX;
		RectangleObjectPositionY = startPositionY;
		RectangleObjectWidth = width;
		RectangleObjectHeight = height;
		DirectionX = directionX;
		DirectionY = directionY;
		MoveSpeed = moveSpeed;
		RectangleObjectColor = color;
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
	bool isCollidedWithRectangle = false;
	SetTargetFPS(144);

	// ------------------------------------------ GAME LOOP START -------------------------------------
	while (WindowShouldClose() == false)
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
		const int rectangleUpperYEdge = rectangle1.RectangleObjectPositionY;
		const int rectangleBottomYEdge = rectangle1.RectangleObjectPositionY + rectangle1.RectangleObjectHeight;
		const int rectangleRightXEdge = rectangle1.RectangleObjectPositionX + rectangle1.RectangleObjectWidth;
		const int rectangleLeftXEdge = rectangle1.RectangleObjectPositionX;
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
			rectangle1.RectangleObjectPositionY += rectangle1.DirectionY * rectangle1.MoveSpeed;

			if (rectangle1.RectangleObjectPositionY > game->SCREEN_HEIGHT - rectangle1.RectangleObjectHeight || rectangle1.RectangleObjectPositionY < 0)
			{
				rectangle1.DirectionY = -rectangle1.DirectionY;
			}
			// --------------------------------------------------------------------------------------------


			// -------------------------------------- DRAW OBJECTS ----------------------------------------
			DrawCircle(playerCircle->currentXPosition, playerCircle->currentYPosition, playerCircle->RADIUS, PURPLE);

			DrawRectangle(rectangle1.RectangleObjectPositionX, rectangle1.RectangleObjectPositionY,
				rectangle1.RectangleObjectWidth, rectangle1.RectangleObjectHeight, rectangle1.RectangleObjectColor);
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
}