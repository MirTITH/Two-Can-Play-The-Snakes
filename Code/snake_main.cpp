#include "snake_main.h"
#include <Windows.h>
#include <thread>

using namespace std;

Player::Player(int PlayerID)
{
	snake_head = new Snake_Unit;

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
		snake_head->Dir = Direct::up;
		snake_head->food = 150;
		snake_head->next = NULL;
		T = 10;
		snake_head->x = MAP_SIZE_X / 3;
		snake_head->y = MAP_SIZE_Y / 4;
		break;
	case 2:
		this->keymap.up = VK_UP;
		this->keymap.down = VK_DOWN;
		this->keymap.left = VK_LEFT;
		this->keymap.right = VK_RIGHT;

		this->snake_head->color = PX_COLOR(255, 30, 132, 244);
		this->snake_head->Dir = Direct::up;
		this->snake_head->food = 150;
		this->snake_head->next = NULL;
		this->T = 20;
		this->snake_head->x = MAP_SIZE_X / 1.5;
		this->snake_head->y = MAP_SIZE_Y / 4;



		//keymap.up = VK_UP;
		//keymap.down = VK_DOWN;
		//keymap.left = VK_LEFT;
		//keymap.right = VK_RIGHT;
		//keymap.skill_1 = 69;//e
		//keymap.skill_2 = 81;//q
		//keymap.slowdown = 32;//space

		//snake_head->color = PX_COLOR(255, 224, 99, 131);
		//snake_head->Dir = Direct::left;
		//snake_head->food = 50;
		//snake_head->next = NULL;
		//T = 2;
		//snake_head->x = MAP_SIZE_X / 2;
		//snake_head->y = MAP_SIZE_Y / 4;
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
	input.up(GetAsyncKeyState(keymap.up));
	input.down(GetAsyncKeyState(keymap.down));
	input.left(GetAsyncKeyState(keymap.left));
	input.right(GetAsyncKeyState(keymap.right));
}

Snake_Unit* Player::snake(int length)
{
	Snake_Unit* pointer = snake_head;

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
		pointertodel = snake_head;
		delete pointertodel;
		snake_head = pointer;
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
		snake_head->Dir = input.GetDir();
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

	switch (snake_head->Dir)
	{
	case Direct::up:
		snake_head->y--;

		break;
	case Direct::down:
		snake_head->y++;
		break;
	case Direct::left:
		snake_head->x--;
		break;
	case Direct::right:
		snake_head->x++;
		break;
	default:
		break;
	}

	Direct last_dir1 = snake_head->Dir;
	Direct last_dir2 = snake_head->Dir;

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

	snake_head = new Snake_Unit;

	//snake_head->color = PX_COLOR(255, 30, 132, 244);
	snake_head->color = color;
	snake_head->Dir = Direct::up;
	snake_head->food = length;
	snake_head->next = NULL;
	//snake_head->x = MAP_SIZE_X / 3;
	//snake_head->y = MAP_SIZE_Y / 4;
	snake_head->x = x;
	snake_head->y = y;
}

Snake_Unit* Snake::Get(int length)
{
	Snake_Unit* pointer = snake_head;

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
			//tail_this->y = snake_head->y - 1;
			tail_this->y--;
			break;
		case Direct::down:
			//tail_this->y = snake_head->y + 1;
			tail_this->y++;
			break;
		case Direct::left:
			//tail_this->x = snake_head->x - 1;
			tail_this->x--;
			break;
		case Direct::right:
			//tail_this->x = snake_head->x + 1;
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
			tail_this->y = snake_head->y - 1;
			//snake_head->y--;
			break;
		case Direct::down:
			tail_this->y = snake_head->y + 1;
			//snake_head->y++;
			break;
		case Direct::left:
			tail_this->x = snake_head->x - 1;
			//snake_head->x--;
			break;
		case Direct::right:
			tail_this->x = snake_head->x + 1;
			//snake_head->x++;
			break;
		default:
			break;
		}

		tail_this->next = this->snake_head;
		this->snake_head = tail_this;
	}

	return 1;
}