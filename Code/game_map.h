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

// 地图的一块，只用来存障碍物
typedef struct
{
	//bool tryTake; // 如果蛇要占用该块，先将tryTake设为true并赋值snake_Player
	//bool isExistSnake; // 是否存在蛇
	//Player* snake_Player; // 该处蛇的玩家ID
	//SnakeBlock* snakeBlock;

	int foodNum;
	px_color food_color;

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

	///**
	//* @brief 向地图中添加一个蛇节
	//* @return 0 成功；1 已被蛇占用；2 存在障碍物
	//*/
	//int AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock);

	/**
	* @brief 每一个tick调用一次，进行蛇的tick自增以及碰撞判定
	*/
	void Update();

	///**
	//* @brief 从地图中删除一个蛇节
	//* @return 被删除的蛇节，出错则返回NULL
	//*/
	//SnakeBlock* DelSnakeBlock(int x, int y);

	MapBlock GetMapBlock(int x, int y)
	{
		return mapBlock[x][y];
	}

	/**
	* @brief 随机生成食物
	*/
	void GenerateFood();

	void DelFood(int x, int y);

	int GetFood(int x, int y);

	Player player[PLAYER_NUM];

private:
	MapBlock mapBlock[MAP_SIZE_X][MAP_SIZE_Y];

	int totalFoodNum; // 有食物的格子总数

	//int generateFood_T; //生成食物的周期
};