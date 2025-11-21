#include "mainMenu.h"

#include <raylib.h>

#include "consts.h"

namespace run
{
	void mainMenu(SCREENS& currentScreen, Texture2D logo, Texture2D background, Sound music, Sound buttonSFX)
	{
		basicFunctionsMM::update(currentScreen, music, buttonSFX);
		basicFunctionsMM::draw(logo, background);
	}
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen, Sound music, Sound buttonSFX)
	{
		PlaySound(music);

		if (IsKeyPressed(KEY_S))
		{
			PlaySound(buttonSFX);
			currentScreen = GAMEPLAY;
		}

		if (IsKeyPressed(KEY_C))
		{
			PlaySound(buttonSFX);
			currentScreen = CREDITS;
		}

		if (IsKeyPressed(KEY_E))
		{
			PlaySound(buttonSFX);
			currentScreen = EXIT;
		}

		if (IsKeyPressed(KEY_Q))
		{
			PlaySound(buttonSFX);
			currentScreen = GAMEPLAYCOOP;
		}
	}

	void draw(Texture2D logo, Texture2D background)
	{
		int gameplayInstrutionLenght = MeasureText("Play Singeplayer", texts::basicSize);
		int gameplay2sInstrutionLenght = MeasureText("Play multiplayer", texts::basicSize);
		int creditsInstrutionLenght = MeasureText("Credits", texts::basicSize);
		int exitInstrutionLenght = MeasureText("Exit", texts::basicSize);

		DrawTexture(background, 0,0, WHITE);
		DrawTexture(logo, screen::width / 3, 0, WHITE);
		DrawText("Play Singeplayer", (screen::width / 2) - (gameplayInstrutionLenght / 2), screen::height / 2, texts::basicSize, WHITE);
		DrawText("Credits", (screen::width / 2) - (creditsInstrutionLenght / 2), screen::height / 2 + texts::spaceBetweenY, texts::basicSize, WHITE);
		DrawText("Exit", (screen::width / 2) - (exitInstrutionLenght / 2), (screen::height / 2) + (texts::spaceBetweenY * 3), texts::basicSize, WHITE);
		DrawText("Play multiplayer", (screen::width / 2) - (gameplay2sInstrutionLenght / 2), (screen::height / 2) + (texts::spaceBetweenY * 2), texts::basicSize, WHITE);
		DrawText("Version 1.0", 10, screen::height - 30, 20, RED);
	}
}
