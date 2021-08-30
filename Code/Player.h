#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"

using namespace std;

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
	* @brief 初始化一条蛇
	* @param num 蛇的初始长度
	* @param color 蛇的初始颜色
	*/
	Snake(int num = 10, px_color color = PX_COLOR(255, 30, 132, 244))
	{
		snakeHead = new SnakeBlock;
		if (snakeHead == NULL)
		{
			cerr << "Err. [Snake::Snake] snakeHead = new SnakeBlock fail" << endl;
		}

		defaultColor = color;

		snakeLength = 1;
		lastDir = Direct::unassign;

		snakeHead->color = defaultColor;
		snakeHead->food = num;
		snakeHead->next = NULL;

		//snakeHead->x = MAP_SIZE_X / 3;
		//snakeHead->y = MAP_SIZE_Y / 4;
	}

	~Snake();

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
	* @return
	*/
	int AddToTail(SnakeBlock* snakeBlock);

	///**
	//* @brief 在蛇尾加蛇节，并使snakeLength + num
	//* @param num	增加的数目
	//* @param x,y	坐标
	//* @param food	食物数量
	//* @return
	//*/
	//int AddToTail(int num, int x, int y, int food);

	///**
	//* @brief 在蛇尾加蛇节，并使snakeLength + num
	//* @param snakeBlock	继承该蛇节的其他属性
	//* @param num	增加的数目
	//* @param x,y	坐标
	//* @param food	食物数量
	//* @return
	//*/
	//int AddToTail(SnakeBlock* snakeBlock, int num, int x, int y, int food);

	/**
	* @brief 从pos处开始向后删除num节
	* @return
	*/
	int Del(int pos, int num);

	/**
	* @brief 获得上次蛇的移动方向
	* @return 
	*/
	Direct Get_Dir_Last()
	{
		return lastDir;
	}


	/**
	* @brief 检测(x,y)处是否有蛇
	* @return 有则返回蛇节的指针，无则返回NULL
	*/
	SnakeBlock* IsExistPos(int x, int y);
private:
	SnakeBlock* snakeHead;
	Direct lastDir; // 上次移动的方向
	px_color defaultColor;
	int snakeLength; // 蛇的长度（不计算食物，即链表的长度）
};

class Player
{
public:
	Player()
	{

	}

	/**
	* @brief 节拍加1（节拍加T次后蛇移动一格）
	* @return void
	*/
	void tick();

	KeyMap keymap;

	string name;

	uint32_t ID;

	int T; // 运动周期

	Snake snake;
private:
	Direct dir; // 即将向该方向移动
};
