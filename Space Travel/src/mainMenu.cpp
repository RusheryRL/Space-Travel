#include "mainMenu.h"

#include <raylib.h>

#include "consts.h"

namespace run
{
	void mainMenu(SCREENS& currentScreen) 
	{
		basicFunctionsMM::update(currentScreen);
		basicFunctionsMM::draw();
	}
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen)
	{
		if (IsKeyPressed(KEY_S))
			currentScreen = GAMEPLAY;

		if (IsKeyPressed(KEY_C))
			currentScreen = CREDITS;

		if (IsKeyPressed(KEY_E))
			currentScreen = EXIT;

		if (IsKeyPressed(KEY_Q))
		{
			currentScreen = GAMEPLAYCOOP;
		}
	}

	void draw()
	{
		int gameplayInstrutionLenght = MeasureText("Play Singeplayer", texts::basicSize);
		int gameplay2sInstrutionLenght = MeasureText("Play multiplayer", texts::basicSize);
		int creditsInstrutionLenght = MeasureText("Credits", texts::basicSize);
		int exitInstrutionLenght = MeasureText("Exit", texts::basicSize);

		DrawText("Play Singeplayer", (screen::width / 2) - (gameplayInstrutionLenght / 2), screen::height / 2, texts::basicSize, WHITE);
		DrawText("Credits", (screen::width / 2) - (creditsInstrutionLenght / 2), screen::height / 2 + texts::spaceBetweenY, texts::basicSize, WHITE);
		DrawText("Exit", (screen::width / 2) - (exitInstrutionLenght / 2), (screen::height / 2) + (texts::spaceBetweenY * 2), texts::basicSize, WHITE);
		DrawText("Play multiplayer", (screen::width / 2) - (gameplay2sInstrutionLenght / 2), (screen::height / 2) + (texts::spaceBetweenY * 3), texts::basicSize, WHITE);
		DrawText("Version 0.5", 10, screen::height - 30, 20, RED);
	}
}
