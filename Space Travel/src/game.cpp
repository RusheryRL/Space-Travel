#include "game.h"

#include <raylib.h>

#include "consts.h"
#include "screens.h"

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
				
				
				
				break;
			case EXIT:
				
				
				
				break;
			default:
				break;
			}
		}
	}
}