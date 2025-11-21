#include "mainMenu.h"

#include <raylib.h>

#include "consts.h"

namespace run
{
	void mainMenu(SCREENS& currentScreen, Texture2D logo, Texture2D background, Sound music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton)
	{
		basicFunctionsMM::update(currentScreen, music, buttonSFX, singleplayerButton, multiplayerButton, creditsButton, exitButton);
		basicFunctionsMM::draw(logo, background, singleplayerButton, multiplayerButton, creditsButton, exitButton);
	}
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen, Sound music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton)
	{
		PlaySound(music);

		Vector2 mouse = {};

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mouse = GetMousePosition();
		}

		if (buttonFunctions::checkButtonMouseClick(singleplayerButton, mouse))
		{
			PlaySound(buttonSFX);
			currentScreen = GAMEPLAY;
		}

		if (buttonFunctions::checkButtonMouseClick(creditsButton, mouse))
		{
			PlaySound(buttonSFX);
			currentScreen = CREDITS;
		}

		if (buttonFunctions::checkButtonMouseClick(exitButton, mouse))
		{
			PlaySound(buttonSFX);
			currentScreen = EXIT;
		}

		if (buttonFunctions::checkButtonMouseClick(multiplayerButton, mouse))
		{
			PlaySound(buttonSFX);
			currentScreen = GAMEPLAYCOOP;
		}
	}

	void draw(Texture2D logo, Texture2D background, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton)
	{
		DrawTexture(background, 0,0, WHITE);
		DrawTexture(logo, screen::width / 3, 0, WHITE);
		DrawText("Play Singeplayer", (screen::width / 2) - (static_cast<int>(singleplayerButton.hitbox.width / 2)), screen::height / 2, texts::basicSize, singleplayerButton.color);
		DrawText("Credits", (screen::width / 2) - (static_cast<int>(creditsButton.hitbox.width / 2)), screen::height / 2 + texts::spaceBetweenY, texts::basicSize, creditsButton.color);
		DrawText("Exit", (screen::width / 2) - (static_cast<int>(exitButton.hitbox.width / 2)), (screen::height / 2) + (texts::spaceBetweenY * 3), texts::basicSize, exitButton.color);
		DrawText("Play multiplayer", (screen::width / 2) - (static_cast<int>(multiplayerButton.hitbox.width / 2)), (screen::height / 2) + (texts::spaceBetweenY * 2), texts::basicSize, multiplayerButton.color);
		DrawText("Version 1.0", 10, screen::height - 30, 20, RED);
	}
}
