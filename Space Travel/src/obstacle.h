#pragma once

#include <raylib.h>

namespace object
{
	struct Obstacle
	{
		Rectangle hitbox1 = { };
		Rectangle hitbox2 = { };

		Color color = GRAY;

		float distanceBetweenHitboxes = 175.0f;
		float speed = 0.0f;

		bool isActive = true;
		bool passed = false;
	};
}

namespace obstacleFunctions
{
	object::Obstacle createAnObstacle();

	void move(object::Obstacle& obstacle, float deltaTime);
	void draw(object::Obstacle obstacle, Texture2D obstacleTexture);
}