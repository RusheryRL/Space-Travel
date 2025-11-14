#pragma once

#include <raylib.h>

namespace object
{
	struct Player
	{
		Vector2 origin = { };

		Rectangle hitbox = { };

		Color color = WHITE;

		float rotation = 0.0f;
		float jumpingTimer = 0.0f;

		bool isActive = false;
		bool isJumping = false;
		bool hasLose = false;
	};
}

namespace playerFunctions
{
	void setDefault(object::Player& player);
	void move(object::Player& player, float deltaTime);
	void moveP2(object::Player& player, float deltaTime);
	void rotate(object::Player& player, float deltaTime);
	void draw(object::Player& player);
}