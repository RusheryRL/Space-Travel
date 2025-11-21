#pragma once

#include "screens.h"

#include <raylib.h>

namespace run
{
	void mainMenu(SCREENS& currentScreen, Texture2D logo, Texture2D background, Sound music, Sound buttonSFX);
}

namespace basicFunctionsMM
{
	void update(SCREENS& currentScreen, Sound music, Sound buttonSFX);
	void draw(Texture2D logo, Texture2D background);
}