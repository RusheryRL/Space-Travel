#include "game.h"

#include <raylib.h>

#include "consts.h"
#include "screens.h"

#include "mainMenu.h"
#include "gameplay.h"
#include "button.h"

namespace run
{
	void game()
	{
		InitWindow(screen::width, screen::height, "SPACE TRAVEL");
		InitAudioDevice();

		Texture2D background = LoadTexture("res/textures/gameplay/background_layer_1.png");
		Texture2D midground = LoadTexture("res/textures/gameplay/background_layer_2.png");
		Texture2D foreground = LoadTexture("res/textures/gameplay/background_layer_3.png");
		Texture2D spaceTravelLogo = LoadTexture("res/textures/menu/SpaceTravelLogoMenu.png");
		Texture2D spaceTravelMMBackground = LoadTexture("res/textures/menu/MMlogo.png");
		Texture2D playerTextureInput = LoadTexture("res/textures/gameplay/playerTexture.png");
		Texture2D playerTextureIdle = LoadTexture("res/textures/gameplay/playerTextureNoInput.png");
		Texture2D obstacleTexture = LoadTexture("res/textures/gameplay/obstacleTexture.png");

		InitAudioDevice();

		Sound playerJump = LoadSound("res/sound/SFX/cartoon-jump.mp3");
		Sound playerIdle = LoadSound("res/sound/SFX/ufo_floating.mp3");
		Sound playerLoose = LoadSound("res/sound/SFX/car-crash-sound.mp3");
		Sound playerPoint = LoadSound("res/sound/SFX/point.mp3");
		Sound pressButton = LoadSound("res/sound/SFX/button-pressed.mp3");
		Music menuMusic = LoadMusicStream("res/sound/music/main_theme.mp3");
		Music creditsMusic = LoadMusicStream("res/sound/music/space-simple-credits.mp3");

		PlayMusicStream(menuMusic);
		PlayMusicStream(creditsMusic);

		object::Player player;
		object::Player player2;

		std::vector <object::Obstacle> obstacles = {};

		playerFunctions::setDefault(player, playerTextureIdle);
		playerFunctions::setDefault(player2, playerTextureIdle);

		bool shouldClose = false;

		int devSectionLenght = MeasureText("Developers:", texts::basicSize);
		int returnLenght = MeasureText("Presione ENTER para volver", texts::basicSize);
		int gameplayInstrutionLenght = MeasureText("Play Singeplayer", texts::basicSize);
		int gameplay2sInstrutionLenght = MeasureText("Play multiplayer", texts::basicSize);
		int creditsInstrutionLenght = MeasureText("Credits", texts::basicSize);
		int exitInstrutionLenght = MeasureText("Exit", texts::basicSize);

		SCREENS currentScreen = MAIN_MENU;

		button::Button singleplayerButton = buttonFunctions::initButton(gameplayInstrutionLenght, (screen::width / 2) - static_cast<float>((gameplayInstrutionLenght / 2)), screen::height / 2);
		button::Button multiplayerButton = buttonFunctions::initButton(gameplay2sInstrutionLenght, (screen::width / 2) - static_cast<float>((gameplay2sInstrutionLenght / 2)), (screen::height / 2) + (texts::spaceBetweenY * 2));
		button::Button creditsButton = buttonFunctions::initButton(creditsInstrutionLenght, (screen::width / 2) - static_cast<float>((creditsInstrutionLenght / 2)), screen::height / 2 + texts::spaceBetweenY);
		button::Button exitButton = buttonFunctions::initButton(exitInstrutionLenght, (screen::width / 2) - static_cast<float>((exitInstrutionLenght / 2)), (screen::height / 2) + (texts::spaceBetweenY * 3));

		while (!WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			switch (currentScreen)
			{
			case MAIN_MENU:

				run::mainMenu(currentScreen, spaceTravelLogo, spaceTravelMMBackground, menuMusic, pressButton, singleplayerButton, multiplayerButton, creditsButton, exitButton);

				break;
			case GAMEPLAY:

				run::gameplay(currentScreen, player, player2, obstacles, background, midground, foreground, playerTextureIdle, playerTextureInput, obstacleTexture, playerIdle, playerJump, playerLoose, playerPoint);

				break;
			case GAMEPLAYCOOP:

				run::gameplay(currentScreen, player, player2, obstacles, background, midground, foreground, playerTextureIdle, playerTextureInput, obstacleTexture, playerIdle, playerJump, playerLoose, playerPoint);

				break;
			case CREDITS:
				UpdateMusicStream(creditsMusic);

				DrawText("Developers: ", devSectionLenght / 2, 0, texts::basicSize, WHITE);
				DrawText("Zomblack3 (Santiago Britos)", 0, texts::basicSize, texts::basicSize, WHITE);
				DrawText("Rushery (Juan Pablo Pivetta)", 0, texts::basicSize * 2, texts::basicSize, WHITE);
				DrawText("Art: ", 0, texts::basicSize * 4, texts::basicSize, WHITE);
				DrawText("Rushery (Juan Pablo Pivetta)", 0, texts::basicSize * 5 + texts::basicSize, texts::basicSize, WHITE);
				DrawText("Oriklo - Reddit Forum - Midground Parallax", 0, texts::basicSize * 6 + texts::basicSize * 2, texts::basicSize, WHITE);
				DrawText("Sound: ", 0, (screen::width / 3) - texts::basicSize, texts::basicSize, WHITE);
				DrawText("freesound_community - Pixabay - PlayerJump", 0, (screen::width / 3) - texts::basicSize / 3, texts::basicSize, WHITE);
				DrawText("freesound_community - Pixabay - buttonSelected", 0, (screen::width / 3) + texts::basicSize, texts::basicSize, WHITE);
				DrawText("freesound_community - Pixabay - Player SFX basic sound", 0, (screen::width / 3) + texts::basicSize * 2, texts::basicSize, WHITE);
				DrawText("DRAGON-STUDIO - Pixabay - Player Crash", 0, (screen::width / 3) + texts::basicSize * 3, texts::basicSize, WHITE);
				DrawText("lucadialessandro - Pixabay - Player pass obstacle", 0, (screen::width / 3) + texts::basicSize * 4, texts::basicSize, WHITE);
				DrawText("Music: ", 0, (screen::width / 2) + texts::basicSize, texts::basicSize, WHITE);
				DrawText("freesound_community - Pixabay - main theme", 0, (screen::width / 2) + texts::basicSize * 2, texts::basicSize, WHITE);
				DrawText("freesound_community - Pixabay - credits theme", 0, (screen::width / 2) + texts::basicSize * 3, texts::basicSize, WHITE);
				DrawText("Presione ENTER para volver", screen::width - returnLenght, screen::height - texts::basicSize, texts::basicSize, WHITE);

				if (IsKeyPressed(KEY_ENTER))
				{
					PlaySound(pressButton);
					currentScreen = MAIN_MENU;
				}

				break;
			case EXIT:

				shouldClose = true;

				break;
			default:
				break;
			}

			EndDrawing();

			if (shouldClose)
			{
				UnloadTexture(background);
				UnloadTexture(midground);
				UnloadTexture(foreground);
				UnloadTexture(spaceTravelLogo);
				UnloadTexture(playerTextureInput);
				UnloadTexture(playerTextureIdle);
				UnloadTexture(obstacleTexture);
				UnloadTexture(spaceTravelMMBackground);
				UnloadSound(playerJump);
				UnloadSound(playerIdle);
				UnloadSound(playerLoose);
				UnloadSound(playerPoint);
				UnloadSound(pressButton);
				UnloadMusicStream(menuMusic);
				UnloadMusicStream(creditsMusic);
				CloseAudioDevice();
				CloseWindow();
			}
		}
	}
}