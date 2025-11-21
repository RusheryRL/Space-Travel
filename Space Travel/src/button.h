#pragma once

#include <raylib.h>

namespace button
{
	struct Button
	{
		Rectangle hitbox;

		bool isPressed;

		Color color;
	};
}

namespace buttonFunctions
{
	button::Button initButton(int textLenght, float x, float y);
	bool checkButtonMouseClick(button::Button& button, Vector2 mouse);
}