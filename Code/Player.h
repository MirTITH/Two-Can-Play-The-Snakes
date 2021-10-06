#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"
#include "snake.h"
#include "skill.h"

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
	void Tick();

	void GetInput();

	string name;

	uint32_t ID;

	px_color defaultColor;

	Snake snake;

	/**
	* @brief 设置运动周期
	* @param newT 新的周期
	* @param _tick 该周期持续多久（单位tick）
	*/
	void SetT(int newT, int _tick);
private:
	/**
	* @brief 更新运动周期，每个tick执行一次
	*/
	void UpdateT();

	/**
	* @brief 技能：加速
	*/
	void SpeedUp();

	Direct dir; // 即将向该方向移动
	KeyInput input;// 按键输入与输出
	KeyMap keyMap;
	int nowTick;
	int T; // 当前运动周期
	int defaultT; // 默认运动周期
	int T_tick; // 还剩多久回到 defaultT
	bool isInited; // 是否初始化
	Skill skill_speed_up;
};
