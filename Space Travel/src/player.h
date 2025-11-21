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

		int points = 0;

		Texture2D currentTexture = {};
	};
}

namespace playerFunctions
{
	void setDefault(object::Player& player, Texture2D idlePlayer);
	void move(object::Player& player, float deltaTime, Texture2D textureInput, Texture2D textureIdle, Sound playerJump, Sound playerIdle);
	void moveP2(object::Player& player, float deltaTime, Texture2D textureInput, Texture2D textureIdle, Sound playerJump, Sound playerIdle);
	void rotate(object::Player& player, float deltaTime);
	void draw(object::Player& player);
}