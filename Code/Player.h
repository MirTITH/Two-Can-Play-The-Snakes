#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"
#include "snake.h"

#define PLAYER_NUM 2 // 玩家的数量

using namespace std;

class Player
{
public:
	/**
	* @brief 创建一位玩家，之后需要初始化
	*/
	Player();

	/**
	* @brief 初始化一位玩家
	* @param pid 玩家ID
	* @param _keyMap 键位映射
	* @param x,y 坐标
	* @param num 蛇初始长度
	* @param color 蛇的颜色
	*/
	void Init(uint32_t pid, KeyMap _keyMap, int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244));

	/**
	* @brief 节拍加1（节拍加T次后蛇移动一格）
	* @return void
	*/
	void Tick()
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

	void GetInput();

	KeyMap keyMap;

	string name;

	uint32_t ID;

	int T; // 运动周期

	px_color defaultColor;

	Snake snake;

	KeyInput input;// 按键输入与输出
private:
	Direct dir; // 即将向该方向移动
	int nowTick;
	bool isInited; // 是否初始化
};
