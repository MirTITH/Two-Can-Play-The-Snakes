#include "snake_main.h"
#include <Windows.h>
#include <thread>

using namespace std;

Player::Player(int PlayerID)
{
	snakeHead = new Snake_Unit;

	switch (PlayerID)
	{
	case 1:
		keyMap.up = 87;//w
		keyMap.down = 83;//s
		keyMap.left = 65;//a
		keyMap.right = 68;//d
		keyMap.accelerate = 16;//shift
		keyMap.skill_1 = 69;//e
		keyMap.skill_2 = 81;//q
		keyMap.slowdown = 32;//space

		snakeHead->color = PX_COLOR(255, 30, 132, 244);
		snakeHead->Dir = Direct::up;
		snakeHead->food = 150;
		snakeHead->next = NULL;
		T = 10;
		snakeHead->x = MAP_SIZE_X / 3;
		snakeHead->y = MAP_SIZE_Y / 4;
		break;
	case 2:
		this->keyMap.up = VK_UP;
		this->keyMap.down = VK_DOWN;
		this->keyMap.left = VK_LEFT;
		this->keyMap.right = VK_RIGHT;

		this->snakeHead->color = PX_COLOR(255, 30, 132, 244);
		this->snakeHead->Dir = Direct::up;
		this->snakeHead->food = 150;
		this->snakeHead->next = NULL;
		this->T = 20;
		this->snakeHead->x = MAP_SIZE_X / 1.5;
		this->snakeHead->y = MAP_SIZE_Y / 4;



		//keyMap.up = VK_UP;
		//keyMap.down = VK_DOWN;
		//keyMap.left = VK_LEFT;
		//keyMap.right = VK_RIGHT;
		//keyMap.skill_1 = 69;//e
		//keyMap.skill_2 = 81;//q
		//keyMap.slowdown = 32;//space

		//snakeHead->color = PX_COLOR(255, 224, 99, 131);
		//snakeHead->Dir = Direct::left;
		//snakeHead->food = 50;
		//snakeHead->next = NULL;
		//T = 2;
		//snakeHead->x = MAP_SIZE_X / 2;
		//snakeHead->y = MAP_SIZE_Y / 4;
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
	input.up(GetAsyncKeyState(keyMap.up));
	input.down(GetAsyncKeyState(keyMap.down));
	input.left(GetAsyncKeyState(keyMap.left));
	input.right(GetAsyncKeyState(keyMap.right));
}

Snake_Unit* Player::snake(int length)
{
	Snake_Unit* pointer = snakeHead;

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
		pointer = snakeHead;
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

void Player::snake_addtotail(Snake_Unit* NewSnake)
{
	Snake_Unit* tail = snake(-1);
	tail->next = NewSnake;

}

int Player::snake_delfromhead(int num)
{
	Snake_Unit* pointer = NULL;
	Snake_Unit* pointertodel = NULL;
	for (int i = 1; i <= num; i++)
	{
		pointer = snake(1);
		if (pointer == NULL)
		{
			return i;
		}
		pointertodel = snakeHead;
		delete pointertodel;
		snakeHead = pointer;
	}

	return num;
}

int Player::move()
{
	timer++;
	if (timer < T)
	{
		return 0;
	}

	timer = 0;



	Snake_Unit* pointer = NULL;
	Snake_Unit* NewSnake = NULL;

	if (input.GetDir() != Direct::unassign)
	{
		snakeHead->Dir = input.GetDir();
	}

	pointer = snake(-1);
	if (pointer->food > 0)
	{
		pointer->food--;
		NewSnake = new Snake_Unit;
		NewSnake->color = pointer->color;
		NewSnake->Dir = pointer->Dir;
		NewSnake->food = pointer->food;
		NewSnake->next = NULL;
		NewSnake->x = pointer->x;
		NewSnake->y = pointer->y;
	}

	switch (snakeHead->Dir)
	{
	case Direct::up:
		snakeHead->y--;

		break;
	case Direct::down:
		snakeHead->y++;
		break;
	case Direct::left:
		snakeHead->x--;
		break;
	case Direct::right:
		snakeHead->x++;
		break;
	default:
		break;
	}

	Direct last_dir1 = snakeHead->Dir;
	Direct last_dir2 = snakeHead->Dir;

	for (int i = 1; ; i++)
	{
		pointer = snake(i);
		if (pointer == NULL) break;

		last_dir1 = pointer->Dir;

		switch (pointer->Dir)
		{
		case Direct::up:
			pointer->y--;
			pointer->Dir = last_dir2;
			break;
		case Direct::down:
			pointer->y++;
			pointer->Dir = last_dir2;
			break;
		case Direct::left:
			pointer->x--;
			pointer->Dir = last_dir2;
			break;
		case Direct::right:
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

Snake::Snake(int x, int y, int length, px_color color)
{
	this->dir = Direct::up;

	snakeHead = new Snake_Unit;

	//snakeHead->color = PX_COLOR(255, 30, 132, 244);
	snakeHead->color = color;
	snakeHead->Dir = Direct::up;
	snakeHead->food = length;
	snakeHead->next = NULL;
	//snakeHead->x = MAP_SIZE_X / 3;
	//snakeHead->y = MAP_SIZE_Y / 4;
	snakeHead->x = x;
	snakeHead->y = y;
}

Snake_Unit* Snake::Get(int length)
{
	Snake_Unit* pointer = snakeHead;

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
		pointer = snakeHead;
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

int Snake::move()
{
	timer++;
	if (timer < T)
	{
		return 0;
	}

	timer = 0;


	Snake_Unit* tail_pre = NULL; // 倒数第二节
	Snake_Unit* tail_this = NULL; // 蛇尾巴
	Snake_Unit* tail_new = NULL; // 新尾巴


	tail_this = this->Get(-1);
	tail_pre = this->Get(-2);

	if (tail_pre == NULL) // 说明蛇的长度为1
	{
		if (tail_this->food > 0)
		{
			tail_new = new Snake_Unit;

			tail_new->color = tail_this->color;
			tail_new->Dir = tail_this->Dir;
			tail_new->food = tail_this->food - 1;
			tail_this->food = 0;
			tail_new->next = NULL;
			tail_new->x = tail_this->x;
			tail_new->y = tail_this->y;
			tail_this->next = tail_new;
		}

		switch (this->dir)
		{
		case Direct::up:
			//tail_this->y = snakeHead->y - 1;
			tail_this->y--;
			break;
		case Direct::down:
			//tail_this->y = snakeHead->y + 1;
			tail_this->y++;
			break;
		case Direct::left:
			//tail_this->x = snakeHead->x - 1;
			tail_this->x--;
			break;
		case Direct::right:
			//tail_this->x = snakeHead->x + 1;
			tail_this->x++;
			break;
		default:
			break;
		}
		
	}
	else
	{
		if (tail_this->food > 0)
		{
			tail_new = new Snake_Unit;

			tail_new->color = tail_this->color;
			tail_new->Dir = tail_this->Dir;
			tail_new->food = tail_this->food - 1;
			tail_this->food = 0;
			tail_new->next = NULL;
			tail_new->x = tail_this->x;
			tail_new->y = tail_this->y;
			tail_pre->next = tail_new;
		}

		switch (this->dir)
		{
		case Direct::up:
			tail_this->y = snakeHead->y - 1;
			//snakeHead->y--;
			break;
		case Direct::down:
			tail_this->y = snakeHead->y + 1;
			//snakeHead->y++;
			break;
		case Direct::left:
			tail_this->x = snakeHead->x - 1;
			//snakeHead->x--;
			break;
		case Direct::right:
			tail_this->x = snakeHead->x + 1;
			//snakeHead->x++;
			break;
		default:
			break;
		}

		tail_this->next = this->snakeHead;
		this->snakeHead = tail_this;
	}

	return 1;
}