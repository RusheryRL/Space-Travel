#include "gameplay.h"

#include "consts.h"

float scrollingBack = 0.0f;
float scrollingMid = 0.0f;
float scrollingFore = 0.0f;

namespace run
{
	void gameplay(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles, Texture2D& background, Texture2D& midground, Texture2D& foreground, Texture2D& playerTextureIdle, Texture2D& playerTextureInput, Texture2D obstacleTexture, Sound playerIdleSFX, Sound playerJumpSFX, Sound playerCrashSFX, Sound playerPointSFX)
	{
		basicFunctionsGameplay::update(currentScreen, player, player2, obstacles, playerTextureIdle, playerTextureInput, playerIdleSFX, playerJumpSFX, playerCrashSFX, playerPointSFX);

		basicFunctionsGameplay::draw(currentScreen, player, player2, obstacles, background, midground, foreground, obstacleTexture);
	}
}

namespace basicFunctionsGameplay
{
	void update(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles, Texture2D& playerTextureIdle, Texture2D& playerTextureInput, Sound playerIdleSFX, Sound playerJumpSFX, Sound playerCrashSFX, Sound playerPointSFX)
	{
		float deltaTime = GetFrameTime();

		if (player.isActive && !player.hasLose)
		{
			playerFunctions::move(player, deltaTime, playerTextureInput, playerTextureIdle, playerJumpSFX, playerIdleSFX);
			playerFunctions::rotate(player, deltaTime);

			gameplayFunctions::gainPointsPlayer(player, playerPointSFX, obstacles);
			gameplayFunctions::checkPlayerScreenCollition(player);

			if (obstacles.size() > 0)
			{
				for (unsigned int i = 0; i < obstacles.size(); i++)
				{
					obstacleFunctions::move(obstacles.at(i), deltaTime);

					gameplayFunctions::despawnObstacle(obstacles, i);
				}
			}

			gameplayFunctions::spawnObstacle(obstacles, deltaTime);

			if (gameplayFunctions::checkPlayerObstacleCollition(obstacles, player) || player.hitbox.y + (player.hitbox.height / 2) > screen::height)
			{
				PlaySound(playerCrashSFX);
				player.hasLose = true;
			}

			if (IsKeyPressed(KEY_ESCAPE))
				currentScreen = EXIT;
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				player.isActive = true;

				if (currentScreen == GAMEPLAYCOOP)
				{
					player2.isActive = true;
					player2.color = RED;
				}
			}
		}

		if (currentScreen == GAMEPLAYCOOP)
		{
			if (player2.isActive && !player2.hasLose && !player.hasLose)
			{
				player2.color = RED;

				playerFunctions::moveP2(player2, deltaTime, playerTextureInput, playerTextureIdle, playerJumpSFX, playerIdleSFX);
				playerFunctions::rotate(player2, deltaTime);

				gameplayFunctions::gainPointsPlayer(player2, playerPointSFX, obstacles);
				gameplayFunctions::checkPlayerScreenCollition(player2);

				if (gameplayFunctions::checkPlayerObstacleCollition(obstacles, player2) || player2.hitbox.y + (player2.hitbox.height / 2) > screen::height)
				{
					PlaySound(playerCrashSFX);
					player.hasLose = true;
				}
			}
		}

		if (currentScreen == GAMEPLAYCOOP)
		{
			if (player.hasLose || player2.hasLose)
			{

				if (IsKeyPressed(KEY_ENTER))
				{
					player.isActive = false;
					player.hasLose = false;
					player2.isActive = false;
					player2.hasLose = false;

					playerFunctions::setDefault(player, playerTextureIdle);
					playerFunctions::setDefault(player2, playerTextureIdle);

					gameplayFunctions::despawnAllObstacles(obstacles);
				}

				if (IsKeyPressed(KEY_S))
				{
					player.isActive = false;
					player2.isActive = false;
					player.hasLose = false;
					player2.hasLose = false;

					playerFunctions::setDefault(player, playerTextureIdle);
					playerFunctions::setDefault(player2, playerTextureIdle);

					gameplayFunctions::despawnAllObstacles(obstacles);

					StopSound(playerCrashSFX);

					currentScreen = MAIN_MENU;
				}
			}
		}
		else
		{
			if (player.hasLose)
			{
				if (IsKeyPressed(KEY_ENTER))
				{
					player.isActive = false;
					player.hasLose = false;

					playerFunctions::setDefault(player, playerTextureIdle);
					playerFunctions::setDefault(player2, playerTextureIdle);

					gameplayFunctions::despawnAllObstacles(obstacles);
				}

				if (IsKeyPressed(KEY_S))
				{
					player.isActive = false;
					player.hasLose = false;

					playerFunctions::setDefault(player, playerTextureIdle);
					playerFunctions::setDefault(player2, playerTextureIdle);

					gameplayFunctions::despawnAllObstacles(obstacles);

					StopSound(playerCrashSFX);

					currentScreen = MAIN_MENU;
				}
			}
		}
	}

	void draw(SCREENS currentScreen, object::Player player, object::Player player2, std::vector <object::Obstacle> obstacles, Texture2D back, Texture2D mid, Texture2D front, Texture2D obstacleTexture)
	{
		int startingTextLenght = MeasureText("Presione ENTER para iniciar", texts::mediumSize);
		int resetTextLenght = MeasureText("Has perdido, presione ENTER para reiniciar", texts::mediumSize);
		int returnTextLenght = MeasureText("o presiona S para salir", texts::mediumSize);
		int playerPointsLenght = MeasureText("Puntos Player: ", texts::mediumSize);
		int player2HowToPlayLenght = MeasureText("Press UP Button to Jump!", texts::mediumSize);
		float deltaTime = GetFrameTime();

		backgroundGameplay::drawBackground(back, deltaTime);
		backgroundGameplay::drawMidground(mid, deltaTime);
		backgroundGameplay::drawForeground(front, deltaTime);

		playerFunctions::draw(player);
		gameplayFunctions::drawPlayerPoints(player);

		if (currentScreen == GAMEPLAYCOOP)
			playerFunctions::draw(player2);

		for (unsigned int i = 0; i < obstacles.size(); i++)
			obstacleFunctions::draw(obstacles.at(i), obstacleTexture);

		gameplayFunctions::drawPlayerPoints(player);

		if (currentScreen == GAMEPLAYCOOP)
			gameplayFunctions::drawPlayer2Points(player2, playerPointsLenght);

		if (!player.isActive)
		{
			DrawText("Presione ENTER para iniciar", (screen::width / 2) - (startingTextLenght / 2), screen::height / 2, texts::mediumSize, BLUE);
			DrawText("Press W to Jump!", 0, screen::height - texts::mediumSize, texts::mediumSize, BLUE);

			if (currentScreen == GAMEPLAYCOOP)
				DrawText("Press UP to Jump!", screen::width - player2HowToPlayLenght , screen::height - texts::mediumSize, texts::mediumSize, RED);
		}

		if (player.hasLose)
		{
			DrawText("Has perdido, presione ENTER para reiniciar", (screen::width / 2) - (resetTextLenght / 2), screen::height / 2, texts::mediumSize, BLUE);
			DrawText("o presiona S para salir", (screen::width / 2) - (returnTextLenght / 2), screen::height / 2 + 50, texts::mediumSize, BLUE);
		}
	}
}

namespace gameplayFunctions
{
	float spawnTimer = 0.0f;
	float spawnTimerSpeed = 10.0f;

	void spawnObstacle(std::vector <object::Obstacle>& obstacles, float deltaTime)
	{
		const float baseSpawnTimer = 35.0f;

		if (spawnTimer <= 0.0f)
		{
			obstacles.push_back(obstacleFunctions::createAnObstacle());

			spawnTimer = baseSpawnTimer;
		}
		else
			spawnTimer -= deltaTime * spawnTimerSpeed;
	}

	void despawnObstacle(std::vector <object::Obstacle>& obstacles, int index)
	{
		if (!obstacles.at(index).isActive)
			obstacles.erase(obstacles.begin() + index);
	}

	void despawnAllObstacles(std::vector<object::Obstacle>& obstacles)
	{
		for (unsigned int i = 0; i < obstacles.size();)
			if (obstacles.size() > 0)
				obstacles.erase(obstacles.begin());
	}

	bool checkPlayerObstacleCollition(std::vector<object::Obstacle>& obstacles, object::Player& player)
	{
		for (unsigned int i = 0; i < obstacles.size(); i++)
		{
			if (player.hitbox.x + (player.hitbox.width / 2.0f) >= obstacles.at(i).hitbox1.x &&
				player.hitbox.x <= obstacles.at(i).hitbox1.x + obstacles.at(i).hitbox1.width &&
				player.hitbox.y + (player.hitbox.height / 2.0f) >= obstacles.at(i).hitbox1.y &&
				player.hitbox.y <= obstacles.at(i).hitbox1.y + obstacles.at(i).hitbox1.height)
				return true;

			if (player.hitbox.x + (player.hitbox.width / 2.0f) >= obstacles.at(i).hitbox2.x &&
				player.hitbox.x <= obstacles.at(i).hitbox2.x + obstacles.at(i).hitbox2.width &&
				player.hitbox.y + (player.hitbox.height / 2.0f) >= obstacles.at(i).hitbox2.y &&
				player.hitbox.y <= obstacles.at(i).hitbox2.y + obstacles.at(i).hitbox2.height)
				return true;
		}

		return false;
	}
	void checkPlayerScreenCollition(object::Player& player)
	{
		if (player.hitbox.y <= 0.0f)
			player.hitbox.y = 0.0f;
	}
	void gainPointsPlayer(object::Player& player, Sound pointSFX, std::vector <object::Obstacle> obstacles)
	{
		for (unsigned int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles.at(i).passed)
				continue;

			float obstacleRight = obstacles.at(i).hitbox1.x + obstacles.at(i).hitbox1.width;

			if (player.hitbox.x > obstacleRight)
			{
				PlaySound(pointSFX);
				obstacles.at(i).passed = true;
			}

			if (obstacles.at(i).passed)
			{
				player.points++;
			}
		}
	}
	void drawPlayerPoints(object::Player player)
	{
		DrawText(TextFormat("Puntos Player: %i", player.points), 0, texts::basicSize, texts::basicSize, BLUE);
	}
	void drawPlayer2Points(object::Player player2, int textLenght)
	{
		DrawText(TextFormat("Puntos Player2: %i", player2.points), textLenght, texts::basicSize, texts::basicSize, RED);

	}
}

void backgroundGameplay::drawBackground(Texture2D& back, float& deltaTime)
{
	scrollingBack -= 10.0f * deltaTime;

	if (scrollingBack <= -back.width * 2)
		scrollingBack = 0;

	DrawTextureEx(back, { scrollingBack, parallax::backY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(back, { back.width * 2.0f + scrollingBack, parallax::backY }, 0.0f, parallax::backgroundScale, WHITE);
}

void backgroundGameplay::drawMidground(Texture2D& mid, float& deltaTime)
{
	scrollingMid -= 50.0f * deltaTime;

	if (scrollingMid <= -mid.width * 2)
		scrollingMid = 0;

	DrawTextureEx(mid, { scrollingMid, parallax::midY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(mid, { mid.width * 2.0f + scrollingMid, parallax::midY }, 0.0f, parallax::backgroundScale, WHITE);
}

void backgroundGameplay::drawForeground(Texture2D& front, float& deltaTime)
{
	scrollingFore -= 100.0f * deltaTime;

	if (scrollingFore <= -front.width * 2)
		scrollingFore = 0;

	DrawTextureEx(front, { scrollingFore, parallax::frontY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(front, { front.width * 2.0f + scrollingFore, parallax::frontY }, 0.0f, parallax::backgroundScale, WHITE);
}
