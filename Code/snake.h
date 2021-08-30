#pragma once
#include "PainterEngine_Application.h"
#include "keyboard.h"

// 蛇的一节
struct SnakeBlock
{
	int x; // x坐标
	int y; // y坐标
	px_color color;
	int food;
	SnakeBlock* next;
};

// 大小为世界大小，提高搜索碰撞体的效率
//extern SnakeBlock* world_space[][];

class Snake
{
public:
	/**
	* @brief 定义一条蛇，之后需要执行Init()初始化
	* @param num 蛇的初始长度
	* @param color 蛇的初始颜色
	*/
	Snake()
	{
		snakeHead = NULL;
		//if (snakeHead == NULL)
		//{
		//	cerr << "Err. [Snake::Snake] snakeHead = new SnakeBlock fail" << endl;
		//}

		defaultColor = PX_COLOR(255, 30, 132, 244);

		chainLength = 0;
		lastDir = Direct::unassign;

		//snakeHead->color = defaultColor;
		//snakeHead->food = num;
		//snakeHead->next = NULL;

		////snakeHead->x = MAP_SIZE_X / 3;
		////snakeHead->y = MAP_SIZE_Y / 4;
	}

	~Snake();

	/**
	* @brief 初始化一条蛇，只能在初始化后立即执行
	* @param x,y 坐标
	* @param num 蛇的初始长度
	* @param color 蛇的初始颜色
	*/
	void Init(int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244));

	// 执行一次就向 dir 方向移动一次
	void Move(Direct dir);

	/**
	* @param order 蛇节的序数，0表示第1节，-1表示倒数第一节
	* @return 返回指定蛇节的指针，无则返回NULL
	*/
	SnakeBlock* Get(int order);

	/**
	* @brief 在蛇尾加蛇节，并使snakeLength + 1
	* @param snakeBlock	把该蛇节添加到蛇尾
	* @return 0 成功; 1 获取蛇尾错误
	*/
	int AddToTail(SnakeBlock* snakeBlock);

	/**
	* @brief 从order处开始向后删除所有蛇节，order也被删除
	* @param order 蛇节的序数，0表示第1节，-1表示倒数第一节
	* @return 删除的节数
	*/
	int Del(int order);

	/**
	* @brief 删除坐标为(x,y)及其之后的所有蛇节
	* @return 删除的节数
	*/
	int Del(int x, int y);

	/**
	* @brief 获得上次蛇的移动方向
	* @return
	*/
	Direct GetLastDir()
	{
		return lastDir;
	}

	/**
	* @brief 获得上次蛇的反移动方向
	* @return
	*/
	Direct GetReverseLastDir();


	/**
	* @brief 检测(x,y)处是否有蛇
	* @return 有则返回蛇节的指针，无则返回NULL
	*/
	SnakeBlock* GetSnakeBlockPos(int x, int y);
private:
	SnakeBlock* snakeHead;
	Direct lastDir; // 上次移动的方向
	px_color defaultColor;
	int chainLength; // 蛇的长度（不计算食物，即链表的长度）
};