#include "button.h"

#include "consts.h"

button::Button buttonFunctions::initButton(int textLenght, float x, float y)
{
	button::Button newButton;

	newButton.hitbox.x = x;
	newButton.hitbox.y = y;
	newButton.hitbox.width = static_cast<float>(textLenght);
	newButton.hitbox.height = texts::basicSize;

	newButton.isPressed = false;

	newButton.color = WHITE;

	return newButton;
}

bool buttonFunctions::checkButtonMouseClick(button::Button& button, Vector2 mouse)
{
	if (mouse.x >= button.hitbox.x && mouse.x <= button.hitbox.x + button.hitbox.width &&
		mouse.y >= button.hitbox.y && mouse.y <= button.hitbox.y + button.hitbox.height)
	{
		button.isPressed = true;
		return true;
	}
	else
	{
		return false;
	}
}
