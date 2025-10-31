#include "game.h"

#include <raylib.h>

#include "consts.h"
#include "screens.h"

#include "mainMenu.h"
#include "gameplay.h"

namespace run
{
	void game()
	{
		InitWindow(screen::width, screen::height, "SPACE TRAVEL");

		object::Player player;

		std::vector <object::Obstacle> obstacles = { };

		playerFunctions::setDefault(player);

		bool shouldClose = false;

		int creditsLenght = MeasureText("Creado por Zomblack3 (Santiago Britos)", 30);
		int returnLenght = MeasureText("Presione ENTER para volver", 30);

		SCREENS currentScreen = MAIN_MENU;

		while (!WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			switch (currentScreen)
			{
			case MAIN_MENU:

				run::mainMenu(currentScreen);

				break;
			case GAMEPLAY:
				
				run::gameplay(currentScreen, player, obstacles);
				
				break;
			case CREDITS:

				DrawText("Creado por Zomblack3 (Santiago Britos)", (screen::width / 2) - (creditsLenght / 2), screen::height / 2, 30, WHITE);
				DrawText("Presione ENTER para volver", (screen::width / 2) - (returnLenght / 2), screen::height / 2 + 100, 30, WHITE);

				if (IsKeyPressed(KEY_ENTER))
					currentScreen = MAIN_MENU;

				break;
			case EXIT:				
				
				shouldClose = true;
				
				break;
			default:
				break;
			}

			DrawText("Version 0.1", 10, screen::height - 30, 20, RED);

			EndDrawing();

			if (shouldClose)
				CloseWindow();
		}
	}
}