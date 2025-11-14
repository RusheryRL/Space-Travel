#include "gameplay.h"

#include "consts.h"

namespace run
{
	void gameplay(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles, Texture2D background, Texture2D midground, Texture2D foreground)
	{
		basicFunctionsGameplay::update(currentScreen, player, player2, obstacles);

		basicFunctionsGameplay::draw(currentScreen, player, player2, obstacles, background, midground, foreground);
	}
}

namespace basicFunctionsGameplay
{
	void update(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles)
	{
		float deltaTime = GetFrameTime();

		if (player.isActive && !player.hasLose)
		{
			playerFunctions::move(player, deltaTime);
			playerFunctions::rotate(player, deltaTime);

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
				player.hasLose = true;

			if (IsKeyPressed(KEY_ESCAPE))
				currentScreen = EXIT;
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				player.isActive = true;

				if (currentScreen == GAMEPLAYCOOP)
					player2.isActive = true;
			}
		}

		if (currentScreen == GAMEPLAYCOOP)
		{
			if (player2.isActive && !player2.hasLose && !player.hasLose)
			{
				playerFunctions::moveP2(player2, deltaTime);
				playerFunctions::rotate(player2, deltaTime);
				if (gameplayFunctions::checkPlayerObstacleCollition(obstacles, player2) || player2.hitbox.y + (player2.hitbox.height / 2) > screen::height)
					player.hasLose = true;
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

					playerFunctions::setDefault(player);
					playerFunctions::setDefault(player2);

					gameplayFunctions::despawnAllObstacles(obstacles);
				}

				if (IsKeyPressed(KEY_S))
				{
					player.isActive = false;
					player2.isActive = false;
					player.hasLose = false;
					player2.hasLose = false;

					playerFunctions::setDefault(player);
					playerFunctions::setDefault(player2);

					gameplayFunctions::despawnAllObstacles(obstacles);

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

					playerFunctions::setDefault(player);

					gameplayFunctions::despawnAllObstacles(obstacles);
				}

				if (IsKeyPressed(KEY_S))
				{
					player.isActive = false;
					player.hasLose = false;

					playerFunctions::setDefault(player);

					gameplayFunctions::despawnAllObstacles(obstacles);

					currentScreen = MAIN_MENU;
				}
			}
		}
	}

	void draw(SCREENS& currentScreen, object::Player player, object::Player player2, std::vector <object::Obstacle> obstacles, Texture2D back, Texture2D mid, Texture2D front)
	{
		int startingTextLenght = MeasureText("Presione ENTER para iniciar", texts::mediumSize);
		int resetTextLenght = MeasureText("Has perdido, presione ENTER para reiniciar", texts::mediumSize);
		int returnTextLenght = MeasureText("o presiona S para salir", texts::mediumSize);

		backgroundGameplay::drawBackground(back);
		backgroundGameplay::drawMidground(mid);
		backgroundGameplay::drawForeground(front);

		playerFunctions::draw(player);

		if (currentScreen == GAMEPLAYCOOP)
			playerFunctions::draw(player2);

		for (unsigned int i = 0; i < obstacles.size(); i++)
			obstacleFunctions::draw(obstacles.at(i));
		if (!player.isActive)
			DrawText("Presione ENTER para iniciar", (screen::width / 2) - (startingTextLenght / 2), screen::height / 2, texts::mediumSize, BLUE);

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
}

float backgroundGameplay::updateBackgorund(Texture2D back, float& deltaTime)
{
	float scrollingBack = 0.0f;

	scrollingBack -= 1.0f * deltaTime;

	if (scrollingBack <= -back.width * 2)
		scrollingBack = 0;

	return scrollingBack;
}

float backgroundGameplay::updateMidgorund(Texture2D mid, float& deltaTime)
{
	float scrollingMid = 0.0f;

	scrollingMid -= 5.0f * deltaTime;

	if (scrollingMid <= -mid.width * 2)
		scrollingMid = 0;

	return scrollingMid;
}

float backgroundGameplay::updateForegorund(Texture2D front, float& deltaTime)
{
	float scrollingFront = 0.0f;

	scrollingFront -= 10.0f * deltaTime;

	if (scrollingFront <= -front.width * 2)
		scrollingFront = 0;

	return scrollingFront;
}

void backgroundGameplay::drawBackground(Texture2D back)
{
	float deltaTime = GetFrameTime();

	DrawTextureEx(back, { updateBackgorund(back, deltaTime), parallax::backY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(back, { back.width * 2.0f + updateBackgorund(back, deltaTime), parallax::backY }, 0.0f, parallax::backgroundScale, WHITE);
}

void backgroundGameplay::drawMidground(Texture2D mid)
{
	float deltaTime = GetFrameTime();

	DrawTextureEx(mid, { updateMidgorund(mid, deltaTime), parallax::midY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(mid, { mid.width * 2.0f + updateMidgorund(mid, deltaTime), parallax::midY }, 0.0f, parallax::backgroundScale, WHITE);
}

void backgroundGameplay::drawForeground(Texture2D front)
{
	float deltaTime = GetFrameTime();

	DrawTextureEx(front, { updateForegorund(front, deltaTime), parallax::frontY }, 0.0f, parallax::backgroundScale, WHITE);
	DrawTextureEx(front, { front.width * 2.0f + updateForegorund(front, deltaTime), parallax::frontY }, 0.0f, parallax::backgroundScale, WHITE);
}
