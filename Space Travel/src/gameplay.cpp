#include "gameplay.h"

#include "consts.h"

namespace run
{
	void gameplay(SCREENS& currentScreen, object::Player& player, std::vector <object::Obstacle>& obstacles)
	{
		basicFunctionsGameplay::update(currentScreen, player, obstacles);

		basicFunctionsGameplay::draw(player, obstacles);
	}
}

namespace basicFunctionsGameplay
{
	void update(SCREENS& currentScreen, object::Player& player, std::vector <object::Obstacle>& obstacles)
	{
		float deltaTime = GetFrameTime();

		if (player.isActive)
		{
			if (!player.hasLose)
			{
				playerFunctions::move(player, deltaTime);
				playerFunctions::rotate(player, deltaTime);

				if (obstacles.size() > 0)
				{
					for (int i = 0; i < obstacles.size(); i++)
					{
						obstacleFunctions::move(obstacles.at(i), deltaTime);

						gameplayFunctions::despawnObstacle(obstacles, i);
					}
				}

				gameplayFunctions::spawnObstacle(obstacles, deltaTime);

				if (gameplayFunctions::checkPlayerObstacleCollition(obstacles, player))
					player.hasLose = true;

				if (IsKeyPressed(KEY_ESCAPE))
					currentScreen = EXIT;
			}
			else
				if (IsKeyPressed(KEY_ENTER))
				{
					player.isActive = false;
					player.hasLose = false;

					playerFunctions::setDefault(player);

					gameplayFunctions::despawnAllObstacles(obstacles);
				}
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
				player.isActive = true;
		}
	}

	void draw(object::Player player, std::vector <object::Obstacle> obstacles)
	{
		int startingTextLenght = MeasureText("Presione ENTER para iniciar", 40);
		int loseTextLenght = MeasureText("Has perdido, presione ENTER para reiniciar", 40);

		BeginDrawing();

		ClearBackground(BLACK);

		playerFunctions::draw(player);

		for (int i = 0; i < obstacles.size(); i++)
			obstacleFunctions::draw(obstacles.at(i));

		if (!player.isActive)
			DrawText("Presione ENTER para iniciar", (screen::width / 2) - (startingTextLenght / 2), screen::height / 2, 40, BLUE);

		if (player.hasLose)
			DrawText("Has perdido, presione ENTER para reiniciar", (screen::width / 2) - (loseTextLenght / 2), screen::height / 2, 40, BLUE);

		DrawText("Version 0.1", 10, screen::height - 30, 20, RED);

		EndDrawing();
	}
}

namespace gameplayFunctions
{
	float spawnTimer = 0.0f;

	void spawnObstacle(std::vector <object::Obstacle>& obstacles, float deltaTime)
	{
		const float baseSpawnTimer = 35.0f;

		if (spawnTimer <= 0.0f)
		{
			obstacles.push_back(obstacleFunctions::createAnObstacle());

			spawnTimer = baseSpawnTimer;
		}
		else
			spawnTimer -= deltaTime * 10.0f;
	}

	void despawnObstacle(std::vector <object::Obstacle>& obstacles, int index)
	{
		if (!obstacles.at(index).isActive)
			obstacles.erase(obstacles.begin() + index);
	}

	void despawnAllObstacles(std::vector<object::Obstacle>& obstacles)
	{
		for (int i = 0; i < obstacles.size();)
			if (obstacles.size() > 0)
				obstacles.erase(obstacles.begin());
	}

	bool checkPlayerObstacleCollition(std::vector<object::Obstacle>& obstacles, object::Player& player)
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (player.hitbox.x + player.hitbox.width >= obstacles.at(i).hitbox1.x &&
				player.hitbox.x <= obstacles.at(i).hitbox1.x + obstacles.at(i).hitbox1.width &&
				player.hitbox.y + player.hitbox.height >= obstacles.at(i).hitbox1.y &&
				player.hitbox.y <= obstacles.at(i).hitbox1.y + obstacles.at(i).hitbox1.height)
				return true;

			if (player.hitbox.x + player.hitbox.width >= obstacles.at(i).hitbox2.x &&
				player.hitbox.x <= obstacles.at(i).hitbox2.x + obstacles.at(i).hitbox2.width &&
				player.hitbox.y + player.hitbox.height >= obstacles.at(i).hitbox2.y &&
				player.hitbox.y <= obstacles.at(i).hitbox2.y + obstacles.at(i).hitbox2.height)
				return true;
		}

		return false;
	}
}