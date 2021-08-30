#include <iostream>
#include "keyboard.h"
#include "PainterEngine_Application.h"

using namespace std;

void KeyInput::up(bool IsDown)
{
	if (IsDown && key_up) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::up;
		}
	}
	else if (IsDown && !key_up) // 按下瞬间
	{
		dir = Direct::up;
	}
	else // 未按下
	{
	}

	key_up = IsDown;
	return;
}

void KeyInput::down(bool IsDown)
{
	if (IsDown && key_down) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::down;
		}
	}
	else if (IsDown && !key_down) // 按下瞬间
	{
		dir = Direct::down;
	}
	else // 未按下
	{
	}

	key_down = IsDown;
	return;
}

void KeyInput::left(bool IsDown)
{
	if (IsDown && key_left) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::left;
		}
	}
	else if (IsDown && !key_left) // 按下瞬间
	{
		dir = Direct::left;
	}
	else // 未按下
	{
	}

	key_left = IsDown;
	return;
}

void KeyInput::right(bool IsDown)
{
	if (IsDown && key_right) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::right;
		}
	}
	else if (IsDown && !key_right) // 按下瞬间
	{
		dir = Direct::right;
	}
	else // 未按下
	{
	}

	key_right = IsDown;
	return;
}

Direct KeyInput::GetDir()
{
	if (GetDirKeyNum() != 0)
	{
		return dir;
	}

	return Direct::unassign;
}

int KeyInput::GetDirKeyNum()
{
	int result = 0;
	if (key_right) result++;
	if (key_left) result++;
	if (key_up) result++;
	if (key_down) result++;
	return result;
}