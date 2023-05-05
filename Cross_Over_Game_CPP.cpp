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

	SetTargetFPS(144);

	// ------------------------------------------ GAME LOOP START -------------------------------------
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------


		// ------------------------------- SET PLAYER CIRCLE COLLISION --------------------------------
		const int circleUpCollision = playerCircle->currentYPosition - playerCircle->RADIUS;
		const int circleDownCollision = playerCircle->currentYPosition + playerCircle->RADIUS;
		const int circleRightCollision = playerCircle->currentXPosition + playerCircle->RADIUS;
		const int circleLeftCollision = playerCircle->currentXPosition - playerCircle->RADIUS;
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- MOVEMENT INPUTS --------------------------------------
		if (IsKeyDown(KEY_D) && circleRightCollision < game->SCREEN_WIDTH)
		{
			playerCircle->currentXPosition += 3;
		}
		if (IsKeyDown(KEY_A) && circleLeftCollision > 0)
		{
			playerCircle->currentXPosition -= 3;
		}
		if (IsKeyDown(KEY_W) && circleUpCollision > 0)
		{
			playerCircle->currentYPosition -= 3;
		}
		if (IsKeyDown(KEY_S) && circleDownCollision < game->SCREEN_HEIGHT)
		{
			playerCircle->currentYPosition += 3;
		}
		// --------------------------------------------------------------------------------------------


		// ------------------------------ MOVE RECTANGLE TO UP AND DOWN -------------------------------
		rectangle1.RectangleObjectPositionY += rectangle1.DirectionY * rectangle1.MoveSpeed;

		if (rectangle1.RectangleObjectPositionY > game->SCREEN_HEIGHT - rectangle1.RectangleObjectHeight || rectangle1.RectangleObjectPositionY < 0)
		{
			rectangle1.DirectionY = -rectangle1.DirectionY;
		}
		// --------------------------------------------------------------------------------------------


		// -------------------------------------- DRAW OBJECTS ----------------------------------------
		DrawRectangle(rectangle1.RectangleObjectPositionX, rectangle1.RectangleObjectPositionY,
			rectangle1.RectangleObjectWidth, rectangle1.RectangleObjectHeight, rectangle1.RectangleObjectColor);

		DrawCircle(playerCircle->currentXPosition, playerCircle->currentYPosition, playerCircle->RADIUS, PURPLE);
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- GAME LOGIC END ---------------------------------------

		EndDrawing();
	}
	// ----------------------------------------- GAME LOOP END ----------------------------------------
}