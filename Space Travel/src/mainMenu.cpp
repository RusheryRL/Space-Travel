#include "mainMenu.h"

#include <raylib.h>

#include "consts.h"

namespace run
{
	void mainMenu(SCREENS& currentScreen, Texture2D logo, Texture2D background, Music music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton)
	{
		basicFunctionsMM::update(currentScreen, music, buttonSFX, singleplayerButton, multiplayerButton, creditsButton, exitButton);
		basicFunctionsMM::draw(logo, background, singleplayerButton, multiplayerButton, creditsButton, exitButton);
	}
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen, Music music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton)
	{
		UpdateMusicStream(music);

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
		DrawTexture(background, Diff::originDiff, Diff::originDiff, WHITE);
		DrawTexture(logo, screen::width / Diff::Diffx3, Diff::originDiff, WHITE);
		DrawText("Play Singeplayer", (screen::width / Diff::Diffx2) - (static_cast<int>(singleplayerButton.hitbox.width / Diff::Diffx2)), screen::height / Diff::Diffx2, texts::basicSize, singleplayerButton.color);
		DrawText("Credits", (screen::width / Diff::Diffx2) - (static_cast<int>(creditsButton.hitbox.width / Diff::Diffx2)), (screen::height / Diff::Diffx2) + (texts::spaceBetweenY * 2), texts::basicSize, creditsButton.color);
		DrawText("Exit", (screen::width / Diff::Diffx2) - (static_cast<int>(exitButton.hitbox.width / Diff::Diffx2)), (screen::height / Diff::Diffx2) + (texts::spaceBetweenY * Diff::Diffx3), texts::basicSize, exitButton.color);
		DrawText("Play multiplayer",(screen::width / Diff::Diffx2) - static_cast<int>(multiplayerButton.hitbox.width / Diff::Diffx2), (screen::height / 2) + texts::spaceBetweenY, texts::basicSize, multiplayerButton.color);
		DrawText("Version 1.0", textVersion::versionX, screen::height - texts::basicSize, texts::basicSize, RED);
	}
}
