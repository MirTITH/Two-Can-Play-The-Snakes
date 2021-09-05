#pragma once

#include "PainterEngine_Application.h"
#include "snake.h"
#include "Player.h"

#define MAP_DISPLAY_X 1000
#define MAP_DISPLAY_Y 720

#define MAP_SIZE_X (MAP_DISPLAY_X / 8)
#define MAP_SIZE_Y (MAP_DISPLAY_Y / 8)

const int MAP_EDGE_TO_SCREEN_L = (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// 地图左边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_U = (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// 地图上边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_R = PX_APPLICATION_SURFACE_WIDTH - 1 - (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// 地图右边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_D = PX_APPLICATION_SURFACE_HEIGHT - 1 - (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// 地图下边界对应的屏幕坐标

/**
* @brief 将地图上的点映射到屏幕上
*/
px_int MapToScreen_x(int x);

/**
* @brief 将地图上的点映射到屏幕上
*/
px_int MapToScreen_y(int y);

// 地图的一块
typedef struct
{
	bool tryTake; // 如果蛇要占用该块，先将tryTake设为true并赋值snake_Player
	bool isExistSnake; // 是否存在蛇
	Player* snake_Player; // 该处蛇的玩家ID
	SnakeBlock* snakeBlock;

	bool isExistObstacle; // 是否存在障碍物
	px_color obstacle_color; // 障碍物的颜色
}MapBlock;

class GameMap
{
public:
	/**
	* 地图
	*/
	GameMap();

	/**
	* @return 地图的x轴长度
	*/
	int Size_x()
	{
		return MAP_DISPLAY_X;
	}

	/**
	* @return 地图的y轴长度
	*/
	int Size_y()
	{
		return MAP_DISPLAY_Y;
	}

	/**
	* @brief 向地图中添加一个蛇节
	* @return 0 成功；1 已被蛇占用；2 存在障碍物
	*/
	int AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock);

	void Update()
	{
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			player[i].Tick();
		}

		// 蛇头与蛇头相撞
		for (int x = 0; x < PLAYER_NUM - 1; x++)
		{
			for (int y = x + 1; y < PLAYER_NUM; y++)
			{
				if (player[x].snake.Get(0)->x == player[y].snake.Get(0)->x && player[x].snake.Get(0)->y == player[y].snake.Get(0)->y)
				{
					player[x].snake.DelHead();
					player[y].snake.DelHead();
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
						player[s0].snake.DelHead();
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
					player[s].snake.DelHead();
				}

				i++;
				p = player[s].snake.Get(i);
			}
		}

		/*for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int y = 0; y < MAP_SIZE_Y; y++)
			{
				if (mapBlock[x][y].tryTake == true)
				{
					mapBlock[x][y].tryTake = false;
					mapBlock[x][y].isExistSnake = true;
				}
			}
		}*/
	}

	/**
	* @brief 从地图中删除一个蛇节
	* @return 被删除的蛇节，出错则返回NULL
	*/
	SnakeBlock* DelSnakeBlock(int x, int y);

	MapBlock GetMapBlock(int x, int y)
	{
		return mapBlock[x][y];
	}

	Player player[PLAYER_NUM];

private:
	MapBlock mapBlock[MAP_SIZE_X][MAP_SIZE_Y];
};