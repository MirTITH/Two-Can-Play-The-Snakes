#include "Player.h"
#include <Windows.h>
#include "game_map.h"

Player::Player()
{
	isInited = false;
	ID = 0;
	T = 20;
	dir = Direct::up;
	nowTick = 0;
	keyMap = { 0 };

	defaultColor = PX_COLOR(255, 255, 255, 255);

	clog << hex << this << " Player created." << endl;
}

void Player::Tick()
{
	if (!isInited)
	{
		cerr << hex << this << " Err. [Player::Tick()] Not initialized." << endl;
		return;
	}

	nowTick++;
	if (nowTick >= T)
	{
		nowTick = 0;

		Direct temp = input.GetDir();
		if (temp != Direct::unassign && temp != snake.GetReverseLastDir())
		{
			dir = temp;
		}
		snake.Move(dir);
	}
}

void Player::GetInput()
{
	if (!isInited)
	{
		cerr << hex << this << " Err. [Player::GetInput()] Not initialized." << endl;
		return;
	}

	input.up(GetAsyncKeyState(keyMap.up));
	input.down(GetAsyncKeyState(keyMap.down));
	input.left(GetAsyncKeyState(keyMap.left));
	input.right(GetAsyncKeyState(keyMap.right));
}

void Player::Init(uint32_t pid, KeyMap _keyMap, int x, int y, int num, px_color color)
{
	defaultColor = color;
	snake.Init(pid, x, y, num, defaultColor);
	ID = pid;
	T = 50;
	dir = Direct::up;
	name = "id_" + to_string(ID);
	keyMap = _keyMap;
	nowTick = 0;
	isInited = true;

	clog << hex << this << " Player [" << name << "] initialized." << endl;
}
