#pragma once

#include <vector>

#include "screens.h"

#include "player.h"
#include "obstacle.h"

namespace run
{
	void gameplay(SCREENS& currentScreen, object::Player& player, std::vector <object::Obstacle>& obstacles);
}

namespace basicFunctionsGameplay
{
	void update(SCREENS& currentScreen, object::Player& player, std::vector <object::Obstacle>& obstacles);
	void draw(object::Player player, std::vector <object::Obstacle> obstacles);
}

namespace gameplayFunctions
{
	void spawnObstacle(std::vector <object::Obstacle>& obstacles, float deltaTime);
	void despawnObstacle(std::vector <object::Obstacle>& obstacles, int index);
	void despawnAllObstacles(std::vector <object::Obstacle>& obstacles);
	
	bool checkPlayerObstacleCollition(std::vector <object::Obstacle>& obstacles, object::Player& player);
}