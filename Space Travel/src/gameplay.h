#pragma once

#include <vector>

#include "screens.h"

#include "player.h"
#include "obstacle.h"

namespace run
{
	void gameplay(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles, Texture2D background, Texture2D midground, Texture2D foreground);
}

namespace basicFunctionsGameplay
{
	void update(SCREENS& currentScreen, object::Player& player, object::Player& player2, std::vector <object::Obstacle>& obstacles);
	void draw(object::Player player, object::Player player2, std::vector <object::Obstacle> obstacles, Texture2D back, Texture2D mid, Texture2D front);
}

namespace gameplayFunctions
{
	void spawnObstacle(std::vector <object::Obstacle>& obstacles, float deltaTime);
	void despawnObstacle(std::vector <object::Obstacle>& obstacles, int index);
	void despawnAllObstacles(std::vector <object::Obstacle>& obstacles);
	
	bool checkPlayerObstacleCollition(std::vector <object::Obstacle>& obstacles, object::Player& player);
}

namespace backgroundGameplay
{
	float updateBackgorund(Texture2D back, float& deltaTime);
	float updateMidgorund(Texture2D mid, float& deltaTime);
	float updateForegorund(Texture2D front, float& deltaTime);

	void drawBackground(Texture2D back);
	void drawMidground(Texture2D mid);
	void drawForeground(Texture2D front);
}