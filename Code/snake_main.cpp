#include "snake_main.h"
#include <Windows.h>
#include <thread>

Player::Player(int PlayerID)
{
	snake_head = new Snake;

	switch (PlayerID)
	{
	case 1:
		keymap.up = 87;//w
		keymap.down = 83;//s
		keymap.left = 65;//a
		keymap.right = 68;//d
		keymap.accelerate = 16;//shift
		keymap.skill_1 = 69;//e
		keymap.skill_2 = 81;//q
		keymap.slowdown = 32;//space

		snake_head->color = PX_COLOR(255, 30, 132, 244);
		snake_head->Dir = direct::up;
		snake_head->food = 50;
		snake_head->next = NULL;
		T = 2;
		snake_head->x = MAP_SIZE_X / 2;
		snake_head->y = MAP_SIZE_Y / 4;
		break;
	case 2:
		keymap.up = VK_UP;
		keymap.down = VK_DOWN;
		keymap.left = VK_LEFT;
		keymap.right = VK_RIGHT;

		snake_head->color = PX_COLOR(255, 224, 99, 131);
		snake_head->Dir = direct::up;
		snake_head->food = 1;
		snake_head->next = NULL;
		T = 10;
		snake_head->x = MAP_SIZE_X / 2;
		snake_head->y = MAP_SIZE_Y / 1.5;
		break;
	default:

		break;
	}
}

Player::~Player()
{

}

void Player::get_input()
{
	this->input.up(GetKeyState(this->keymap.up) & 0x8000);
	this->input.down(GetKeyState(this->keymap.down) & 0x8000);
	this->input.left(GetKeyState(this->keymap.left) & 0x8000);
	this->input.right(GetKeyState(this->keymap.right) & 0x8000);
}

Snake* Player::snake(int length)
{
	Snake* pointer = snake_head;

	if (length > 0)
	{
		for (int i = 0; i < length; i++)
		{
			pointer = pointer->next;
			if (pointer == NULL)
			{
				break;
			}
		}
	}
	else if (length < 0)
	{
		int max_length;
		for (int i = 1; ; i++)
		{
			pointer = pointer->next;
			if (pointer == NULL)
			{
				max_length = i;
				break;
			}
		}

		if (max_length + length < 0) return NULL;
		pointer = snake_head;
		for (int i = 0; i < max_length + length; i++)
		{
			pointer = pointer->next;
			if (pointer == NULL)
			{
				break;
			}
		}
	}
	
	return pointer;
}

void Player::snake_addtotail(Snake* NewSnake)
{
	Snake* tail = snake(-1);
	tail->next = NewSnake;

}

int Player::snake_delfromhead(int num)
{
	Snake* pointer = NULL;
	Snake* pointertodel = NULL;
	for (int i = 1; i <= num; i++)
	{
		pointer = snake(1);
		if (pointer == NULL)
		{
			return i;
		}
		pointertodel = snake_head;
		delete pointertodel;
		snake_head = pointer;
	}

	return num;
}

int Player::move()
{
	static int timer = 0;
	timer++;
	if (timer < T)
	{
		return 0;
	}

	timer = 0;



	Snake* pointer = NULL;
	Snake* NewSnake = NULL;

	if (input.GetDir() != direct::unassign)
	{
		snake_head->Dir = input.GetDir();
	}

	pointer = snake(-1);
	if (pointer->food > 0)
	{
		pointer->food--;
		NewSnake = new Snake;
		NewSnake->color = pointer->color;
		NewSnake->Dir = pointer->Dir;
		NewSnake->food = pointer->food;
		NewSnake->next = NULL;
		NewSnake->x = pointer->x;
		NewSnake->y = pointer->y;
	}

	switch (snake_head->Dir)
	{
	case direct::up:
		snake_head->y--;
		break;
	case direct::down:
		snake_head->y++;
		break;
	case direct::left:
		snake_head->x--;
		break;
	case direct::right:
		snake_head->x++;
		break;
	default:
		break;
	}

	direct last_dir1 = snake_head->Dir;
	direct last_dir2 = snake_head->Dir;

	for (int i = 1; ; i++)
	{
		pointer = snake(i);
		if (pointer == NULL) break;

		last_dir1 = pointer->Dir;

		switch (pointer->Dir)
		{
		case direct::up:
			pointer->y--;
			pointer->Dir = last_dir2;
			break;
		case direct::down:
			pointer->y++;
			pointer->Dir = last_dir2;
			break;
		case direct::left:
			pointer->x--;
			pointer->Dir = last_dir2;
			break;
		case direct::right:
			pointer->x++;
			pointer->Dir = last_dir2;
			break;
		default:
			break;
		}

		last_dir2 = last_dir1;
	}

	if (NewSnake != NULL)
	{
		snake_addtotail(NewSnake);
	}

	return 1;
}