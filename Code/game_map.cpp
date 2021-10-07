#include "game_map.h"

random_device randDevice; //随机数生成设备（用于产生种子）
default_random_engine randEngine(randDevice()); // 伪随机数生成引擎

uniform_int_distribution<unsigned> rand_map_x(0, MAP_SIZE_X - 1);
uniform_int_distribution<unsigned> rand_map_y(0, MAP_SIZE_Y - 1);

px_int MapToScreen_x(int x)
{
	return (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X + MAP_DISPLAY_X / MAP_SIZE_X) / 2 + MAP_DISPLAY_X * x / MAP_SIZE_X;
}

px_int MapToScreen_y(int y)
{
	return (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y + MAP_DISPLAY_Y / MAP_SIZE_Y) / 2 + MAP_DISPLAY_Y * y / MAP_SIZE_Y;
}

GameMap::GameMap()
{
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			//mapBlock[x][y].tryTake = false;
			mapBlock[x][y].isExistObstacle = false;
			//mapBlock[x][y].isExistSnake = false;
			mapBlock[x][y].obstacle_color = PX_COLOR(255, 0, 0, 0);
			//mapBlock[x][y].snakeBlock = NULL;
			//mapBlock[x][y].snake_Player = NULL;

			mapBlock[x][y].foodNum = 0;
			mapBlock[x][y].food_color = PX_COLOR(255, 199, 168, 244);
			totalFoodNum = 0;
		}
	}
}

void GameMap::Update()
{
	// 生成食物

	if (totalFoodNum < 2)
	{
		GenerateFood();
	}

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player[i].Tick();
	}
	
	

	// 吃到食物
	for (int s = 0; s < PLAYER_NUM; s++)
	{
		SnakeBlock* p = player[s].snake.Get(0);
		int num;

		num = GetFood(p->x, p->y);
		if (num != 0)
		{
			p->food += num;
			DelFood(p->x, p->y);
		}

		num = GetFood(p->x+1, p->y);
		if (num != 0)
		{
			p->food += num;
			DelFood(p->x+1, p->y);
		}

		num = GetFood(p->x-1, p->y);
		if (num != 0)
		{
			p->food += num;
			DelFood(p->x-1, p->y);
		}

		num = GetFood(p->x, p->y+1);
		if (num != 0)
		{
			p->food += num;
			DelFood(p->x, p->y+1);
		}

		num = GetFood(p->x, p->y-1);
		if (num != 0)
		{
			p->food += num;
			DelFood(p->x, p->y-1);
		}

		//if (p->food > 10)
		//{
		//	cout << "Err. Too much food." << endl;
		//	cin.get();
		//}
	}

	// 蛇头与蛇头相撞
	for (int x = 0; x < PLAYER_NUM - 1; x++)
	{
		for (int y = x + 1; y < PLAYER_NUM; y++)
		{
			if (player[x].snake.Get(0)->x == player[y].snake.Get(0)->x && player[x].snake.Get(0)->y == player[y].snake.Get(0)->y)
			{
				player[x].DelHead();
				player[y].DelHead();
			}
		}
	}

	// 蛇头与别的蛇身相撞
	for (int s0 = 0; s0 < PLAYER_NUM; s0++)
	{
		for (int s1 = 0; s1 < PLAYER_NUM; s1++)
		{
			if (s1 == s0)
			{
				continue;
			}

			int i = 0;
			int x0 = player[s0].snake.Get(0)->x;
			int y0 = player[s0].snake.Get(0)->y;
			SnakeBlock* p = player[s1].snake.Get(0);

			while (p != NULL)
			{
				if (p->x == x0 && p->y == y0)
				{
					player[s0].DelHead();
				}

				i++;
				p = player[s1].snake.Get(i);
			}
		}
	}

	// 蛇头与自己相撞
	for (int s = 0; s < PLAYER_NUM; s++)
	{
		int i = 1;
		int x0 = player[s].snake.Get(0)->x;
		int y0 = player[s].snake.Get(0)->y;
		SnakeBlock* p = player[s].snake.Get(i);

		while (p != NULL)
		{
			if (p->x == x0 && p->y == y0)
			{
				player[s].DelHead();
			}

			i++;
			p = player[s].snake.Get(i);
		}
	}
}

void GameMap::GenerateFood()
{
	int x;
	int y;
	while (true)
	{
		x = rand_map_x(randEngine);
		y = rand_map_y(randEngine);

		if (mapBlock[x][y].foodNum == 0)
		{
			mapBlock[x][y].foodNum = 5;
			totalFoodNum++;
			break;
		}
	}
}

void GameMap::DelFood(int x, int y)
{
	if (x * MAP_SIZE_Y + y >= MAP_SIZE_X * MAP_SIZE_Y || x * MAP_SIZE_Y + y < 0)
	{
		return;
	}
	mapBlock[x][y].foodNum = 0;
	totalFoodNum--;
	return;
}

int GameMap::GetFood(int x, int y)
{
	if (x * MAP_SIZE_Y + y >= MAP_SIZE_X * MAP_SIZE_Y || x * MAP_SIZE_Y + y < 0)
	{
		return 0;
	}

	return mapBlock[x][y].foodNum;
}

//SnakeBlock* GameMap::DelSnakeBlock(int x, int y)
//{
//	SnakeBlock* result = mapBlock[x][y].snakeBlock;
//	mapBlock[x][y].isExistSnake = false;
//	mapBlock[x][y].snakeBlock = NULL;
//	mapBlock[x][y].snake_Player = NULL;
//	return result;
//}