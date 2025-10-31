#include "game.h"

#include <raylib.h>

#include "consts.h"
#include "screens.h"

#include "gameplay.h"

namespace run
{
	void game()
	{
		InitWindow(screen::width, screen::height, "SPACE TRAVEL");

		SCREENS currentScreen = GAMEPLAY;

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case MAIN_MENU:



				break;
			case GAMEPLAY:
				
				run::gameplay(currentScreen);
				
				break;
			case EXIT:
				
				
				
				break;
			default:
				break;
			}
		}
	}
}