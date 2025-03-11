#include <iostream>
#include "raylib.h"

class PlayerCircle
{
public:
	const int START_POSITION_X = 30;
	const int START_POSITION_Y = 375;
	const int RADIUS = 25.00f;

	int currentXPosition = 30;
	int currentYPosition = 375;
};

class GameSettings
{
public:
	const int SCREEN_WIDTH = 1440;
	const int SCREEN_HEIGHT = 900;
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

void GameLoop();

int main()
{
	// ------------------------------------------ GAME LOOP START -------------------------------------
	GameLoop();

	// ----------------------------------------- GAME LOOP END ----------------------------------------
	CloseWindow();
}


void GameLoop()
{
	auto* gameSettings = new GameSettings();
	auto* playerCircle = new PlayerCircle();
	const auto* rectangleObject = new RectangleObject[5];

	RectangleObject rectangle1 = rectangleObject[0];
	rectangle1.MoveSpeed = 12;

	InitWindow(gameSettings->SCREEN_WIDTH, gameSettings->SCREEN_HEIGHT, "Cross Over");
	SetTargetFPS(144);

	bool isCollidedWithRectangle = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------


		// --------------------------------- SET PLAYER CIRCLE EDGES ----------------------------------
		const int circleUpperEdge = playerCircle->currentYPosition - playerCircle->RADIUS;
		const int circleBottomEdge = playerCircle->currentYPosition + playerCircle->RADIUS;
		const int circleRightEdge = playerCircle->currentXPosition + playerCircle->RADIUS;
		const int circleLeftEdge = playerCircle->currentXPosition - playerCircle->RADIUS;
		// --------------------------------------------------------------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const int rectangleUpperEdge = rectangle1.CurrentYPosition;
		const int rectangleBottomEdge = rectangle1.CurrentYPosition + rectangle1.Height;
		const int rectangleRightEdge = rectangle1.CurrentXPosition + rectangle1.Width;
		const int rectangleLeftEdge = rectangle1.CurrentXPosition;
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- MOVEMENT INPUTS --------------------------------------
		if (IsKeyDown(KEY_D) && circleRightEdge < gameSettings->SCREEN_WIDTH)
		{
			playerCircle->currentXPosition += 3;
		}
		if (IsKeyDown(KEY_A) && circleLeftEdge > 0)
		{
			playerCircle->currentXPosition -= 3;
		}
		if (IsKeyDown(KEY_W) && circleUpperEdge > 0)
		{
			playerCircle->currentYPosition -= 3;
		}
		if (IsKeyDown(KEY_S) && circleBottomEdge < gameSettings->SCREEN_HEIGHT)
		{
			playerCircle->currentYPosition += 3;
		}
		// --------------------------------------------------------------------------------------------



		if (!isCollidedWithRectangle)
		{
			// ------------------------------ MOVE RECTANGLE TO UP AND DOWN -------------------------------
			rectangle1.CurrentYPosition += rectangle1.DirectionY * rectangle1.MoveSpeed;

			if (rectangle1.CurrentYPosition > gameSettings->SCREEN_HEIGHT - rectangle1.Height || rectangle1.CurrentYPosition < 0)
			{
				rectangle1.DirectionY = -rectangle1.DirectionY;
			}
			// --------------------------------------------------------------------------------------------

			if (circleUpperEdge <= rectangleBottomEdge && circleBottomEdge >= rectangleUpperEdge &&
				circleRightEdge >= rectangleLeftEdge && circleLeftEdge <= rectangleRightEdge)
			{
				isCollidedWithRectangle = true;
			}

			// -------------------------------------- DRAW OBJECTS ----------------------------------------
			DrawCircle(playerCircle->currentXPosition, playerCircle->currentYPosition, playerCircle->RADIUS, PURPLE);

			DrawRectangle(rectangle1.CurrentXPosition, rectangle1.CurrentYPosition,
				rectangle1.Width, rectangle1.Height, rectangle1.ObjectColor);
			// --------------------------------------------------------------------------------------------
		}
		else
		{
			DrawText("GAME OVER!", (gameSettings->SCREEN_WIDTH / 2) - 75, gameSettings->SCREEN_HEIGHT / 2, 25, RED);

			DrawText("PRESS ENTER TO TRY AGAIN", (gameSettings->SCREEN_WIDTH / 2) - 185, (gameSettings->SCREEN_HEIGHT / 2) + 50, 25, GREEN);

			if (IsKeyPressed(KEY_ENTER))
			{
				playerCircle->currentXPosition = playerCircle->START_POSITION_X;
				playerCircle->currentYPosition = playerCircle->START_POSITION_Y;
				isCollidedWithRectangle = false;
			}
		}




		// ------------------------------------- GAME LOGIC END ---------------------------------------
		EndDrawing();
	}
}