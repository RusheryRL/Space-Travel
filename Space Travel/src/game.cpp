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
		object::Player player2;

		std::vector <object::Obstacle> obstacles = { };

		playerFunctions::setDefault(player);
		playerFunctions::setDefault(player2);

		Texture2D background = LoadTexture("res/textures/gameplay/background_layer_1.png");
		Texture2D midground = LoadTexture("res/textures/gameplay/background_layer_2.png");
		Texture2D foreground = LoadTexture("res/textures/gameplay/background_layer_3.png");

		bool shouldClose = false;

		int creditsLenght = MeasureText("Creado por Zomblack3 (Santiago Britos)", texts::basicSize);
		int returnLenght = MeasureText("Presione ENTER para volver", texts::basicSize);

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
				
				run::gameplay(currentScreen, player, player2, obstacles, background, midground, foreground);
				
				break;
			case GAMEPLAYCOOP:

				run::gameplay(currentScreen, player, player2, obstacles, background, midground, foreground);

				break;
			case CREDITS:

				DrawText("Creado por Zomblack3 (Santiago Britos)", (screen::width / 2) - (creditsLenght / 2), screen::height / 2, texts::basicSize, WHITE);
				DrawText("Presione ENTER para volver", (screen::width / 2) - (returnLenght / 2), screen::height / 2 + texts::spaceBetweenY * 2, texts::basicSize, WHITE);

				if (IsKeyPressed(KEY_ENTER))
					currentScreen = MAIN_MENU;

				break;
			case EXIT:				
				
				shouldClose = true;
				
				break;
			default:
				break;
			}

			EndDrawing();

			if (shouldClose)
				CloseWindow();
		}
	}
}