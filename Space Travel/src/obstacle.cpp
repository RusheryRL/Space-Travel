#include "obstacle.h"

#include <raylib.h>
#include <random>
#include <time.h>

#include "consts.h"

namespace obstacleFunctions
{
	object::Obstacle createAnObstacle()
	{
		const float hitboxWidth = 50.0f;
		const float baseSpeed = 100.0f;

		const int minHitboxHeight = 10;
		const int maxHitboxHeight = screen::height - 200;

		object::Obstacle finalObstacle = { };

		srand(time_t(NULL));

		int finalHitboxHeight = GetRandomValue(minHitboxHeight, maxHitboxHeight);

		finalObstacle.hitbox1.height = static_cast <float> (finalHitboxHeight);
		finalObstacle.hitbox1.width = hitboxWidth;
		finalObstacle.hitbox1.x = screen::width;
		finalObstacle.hitbox1.y = 0.0f;

		finalObstacle.hitbox2.height = static_cast <float> (finalHitboxHeight) + screen::height;
		finalObstacle.hitbox2.width = hitboxWidth;
		finalObstacle.hitbox2.x = screen::width;
		finalObstacle.hitbox2.y = (finalObstacle.hitbox1.y + finalObstacle.hitbox1.height) + finalObstacle.distanceBetweenHitboxes;

		finalObstacle.speed = baseSpeed;

		return finalObstacle;
	}

	void move(object::Obstacle& obstacle, float deltaTime)
	{
		if (obstacle.hitbox2.x + obstacle.hitbox2.width + 10.0f < 0.0f)
			obstacle.isActive = false;
		else
		{
			obstacle.hitbox1.x -= obstacle.speed * deltaTime;
			obstacle.hitbox2.x -= obstacle.speed * deltaTime;
		}
	}

	void draw(object::Obstacle obstacle, Texture2D obstacleTexture)
	{
		DrawTextureRec(obstacleTexture, obstacle.hitbox1, { obstacle.hitbox1.x , obstacle.hitbox1.y}, obstacle.color);
		DrawTextureRec(obstacleTexture, obstacle.hitbox2, { obstacle.hitbox2.x , obstacle.hitbox2.y }, obstacle.color);
	}
}