#include "player.h"

#include "consts.h"

namespace playerFunctions
{
	void setDefault(object::Player& player)
	{
		const float startingPosX = 50.0f;
		const float startingWidth = 35.0f;
		const float startingHeight = 35.0f;
		const float baseRotation = 90.0f;
		
		player.hitbox.x = startingPosX;
		player.hitbox.y = screen::height / 2.0f;
		player.hitbox.width = startingWidth;
		player.hitbox.height = startingHeight;

		player.origin.x = player.hitbox.width / 2.0f;
		player.origin.y = player.hitbox.height / 2.0f;

		player.rotation = baseRotation;

		player.color = WHITE;

		player.isActive = false;
	}

	void move(object::Player& player, float deltaTime)
	{
		const float jumpRotation = 30.0f;
		const float baseJumpingTime = 0.5f;
		
		float gravity = 500.0f;
		float jumpStrenght = -150.0f;
		float fallSpeed = jumpStrenght;

		if (!player.isJumping)
		{
			fallSpeed += gravity * deltaTime;
			player.hitbox.y -= fallSpeed * deltaTime;
		}
		else
		{
			player.hitbox.y -= (jumpStrenght * -1.0f) * deltaTime;
			player.jumpingTimer -= deltaTime;
		}

		if (IsKeyPressed(KEY_W))
		{
			fallSpeed = jumpStrenght;

			player.isJumping = true;
			player.jumpingTimer = baseJumpingTime;
			
			player.rotation = jumpRotation;
		}

		if (player.jumpingTimer < 0)
			player.isJumping = false;
	}

	void moveP2(object::Player& player, float deltaTime)
	{
		const float jumpRotation = 30.0f;
		const float baseJumpingTime = 0.5f;

		float gravity = 500.0f;
		float jumpStrenght = -150.0f;
		float fallSpeed = jumpStrenght;

		if (!player.isJumping)
		{
			fallSpeed += gravity * deltaTime;
			player.hitbox.y -= fallSpeed * deltaTime;
		}
		else
		{
			player.hitbox.y -= (jumpStrenght * -1.0f) * deltaTime;
			player.jumpingTimer -= deltaTime;
		}

		if (IsKeyPressed(KEY_UP))
		{
			fallSpeed = jumpStrenght;

			player.isJumping = true;
			player.jumpingTimer = baseJumpingTime;

			player.rotation = jumpRotation;
		}

		if (player.jumpingTimer < 0)
			player.isJumping = false;
	}

	void rotate(object::Player& player, float deltaTime)
	{
		const float rotationSpeed = 100.0f;
		const float maxRotation = 180.0f;

		if (player.rotation < maxRotation)
			player.rotation += rotationSpeed * deltaTime;
	}

	void draw(object::Player& player)
	{
		DrawRectanglePro(player.hitbox, player.origin, player.rotation, player.color);
	}
}
