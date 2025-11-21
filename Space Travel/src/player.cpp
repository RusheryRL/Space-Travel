#include "player.h"

#include "consts.h"

namespace playerFunctions
{
	void setDefault(object::Player& player, Texture2D idlePlayer)
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

		player.currentTexture = idlePlayer;
	}

	void move(object::Player& player, float deltaTime, Texture2D textureInput, Texture2D textureIdle, Sound playerJump, Sound playerIdle)
	{
		const float jumpRotation = 30.0f;
		const float baseJumpingTime = 0.5f;
		
		float gravity = 500.0f;
		float jumpStrenght = -150.0f;
		float fallSpeed = jumpStrenght;

		if (!player.isJumping)
		{
			PlaySound(playerIdle);

			fallSpeed += gravity * deltaTime;
			player.hitbox.y -= fallSpeed * deltaTime;

			player.currentTexture = textureIdle;
		}
		else
		{
			player.hitbox.y -= (jumpStrenght * -1.0f) * deltaTime;
			player.jumpingTimer -= deltaTime;
		}

		if (IsKeyPressed(KEY_W))
		{
			PlaySound(playerJump);

			fallSpeed = jumpStrenght;

			player.currentTexture = textureInput;

			player.isJumping = true;
			player.jumpingTimer = baseJumpingTime;
			
			player.rotation = jumpRotation;
		}

		if (player.jumpingTimer < 0)
			player.isJumping = false;
	}

	void moveP2(object::Player& player, float deltaTime, Texture2D textureInput, Texture2D textureIdle, Sound playerJump, Sound playerIdle)
	{
		const float jumpRotation = 30.0f;
		const float baseJumpingTime = 0.5f;

		float gravity = 500.0f;
		float jumpStrenght = -150.0f;
		float fallSpeed = jumpStrenght;

		if (!player.isJumping)
		{
			PlaySound(playerIdle);

			fallSpeed += gravity * deltaTime;
			player.hitbox.y -= fallSpeed * deltaTime;

			player.currentTexture = textureIdle;
		}
		else
		{
			player.hitbox.y -= (jumpStrenght * -1.0f) * deltaTime;
			player.jumpingTimer -= deltaTime;
		}

		if (IsKeyPressed(KEY_UP))
		{
			PlaySound(playerJump);

			fallSpeed = jumpStrenght;

			player.currentTexture = textureInput;

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
		Rectangle shipRec = {0,0,35,35};
		Rectangle shipRecDest = {player.hitbox.x,player.hitbox.y,35,35};

		DrawTexturePro(player.currentTexture, shipRec, shipRecDest, player.origin, player.rotation, player.color);
	}
}
