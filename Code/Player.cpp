#include "Player.h"
#include <Windows.h>
#include "game_map.h"

Player::Player()
{
	isInited = false;
	ID = 0;
	T = 20;
	defaultT = T;
	T_tick = 0;
	lostControl_tick = 0;
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
	if (lostControl_tick > 0)
	{
		lostControl_tick--;
	}

	UpdateT();
	skill_speed_up.Tick();

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

	if (lostControl_tick <= 0)
	{
		input.up(GetAsyncKeyState(keyMap.up));
		input.down(GetAsyncKeyState(keyMap.down));
		input.left(GetAsyncKeyState(keyMap.left));
		input.right(GetAsyncKeyState(keyMap.right));
	}

	if (GetAsyncKeyState(keyMap.accelerate))
	{
		if (skill_speed_up.Use())
		{
			SpeedUp();
		}
	}
}

void Player::SetT(int newT, int _tick)
{
	T_tick = _tick;
	T = newT;
}

int Player::DelHead()
{
	lostControl_tick = defaultT;
	return snake.DelHead();
}

void Player::UpdateT()
{
	if (T_tick > 0)
	{
		T_tick--;
	}

	if (T_tick == 0)
	{
		T_tick--;
		T = defaultT;
	}
}

void Player::SpeedUp()
{
	int tick = 500;
	lostControl_tick = tick;
	SetT((int)(defaultT / 4), tick);
}

void Player::Init(uint32_t pid, KeyMap _keyMap, int x, int y, int num, px_color color)
{
	defaultColor = color;
	snake.Init(pid, x, y, num, defaultColor);
	ID = pid;

	T = 50;
	defaultT = T;
	T_tick = 0;

	dir = Direct::up;
	name = "id_" + to_string(ID);
	keyMap = _keyMap;
	nowTick = 0;
	lostControl_tick = 0;
	isInited = true;

	// 初始化技能
	skill_speed_up.Init(1100, 0);

	clog << hex << this << " Player [" << name << "] initialized." << endl;
}
