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
	}

	void draw()
	{
		int gameplayInstrutionLenght = MeasureText("Presione S para iniciar", texts::basicSize);
		int creditsInstrutionLenght = MeasureText("Presione C para ver los creditos", texts::basicSize);
		int exitInstrutionLenght = MeasureText("Presione E para salir", texts::basicSize);

		DrawText("Presione S para iniciar", (screen::width / 2) - (gameplayInstrutionLenght / 2), screen::height / 2, texts::basicSize, WHITE);
		DrawText("Presione C para ver los creditos", (screen::width / 2) - (creditsInstrutionLenght / 2), screen::height / 2 + texts::spaceBetweenY, texts::basicSize, WHITE);
		DrawText("Presione E para salir", (screen::width / 2) - (exitInstrutionLenght / 2), (screen::height / 2) + (texts::spaceBetweenY * 2), texts::basicSize, WHITE);
		DrawText("Version 0.3", 10, screen::height - 30, 20, RED);
	}
}
