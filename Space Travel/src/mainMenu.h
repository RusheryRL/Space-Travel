#pragma once

#include "screens.h"

#include <raylib.h>

#include "button.h"

namespace run
{
	void mainMenu(SCREENS& currentScreen, Texture2D logo, Texture2D background, Sound music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton);
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen, Sound music, Sound buttonSFX, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton);
	void draw(Texture2D logo, Texture2D background, button::Button singleplayerButton, button::Button multiplayerButton, button::Button creditsButton, button::Button exitButton);
}