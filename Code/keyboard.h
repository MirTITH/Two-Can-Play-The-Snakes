#pragma once

#include "myheadfile.h"

//typedef struct student {
//	int score;
//	struct student* next;
//} LinkList;

// 按键映射
typedef struct key_map
{
	int up;//上
	int down;//下
	int left;//左
	int right;//右
	int accelerate;//加速
	int slowdown;//减速
	int skill_1;//小技能
	int skill_2;//大技能
}KeyMap;

class KeyInput
{
public:
	void up(bool IsDown);
	void down(bool IsDown);
	void left(bool IsDown);
	void right(bool IsDown);
	direct GetDir();//获取方向
	int GetDirKeyNum(); //获取同时按下的方向键数量
private:
	bool key_up = false;
	bool key_down = false;
	bool key_left = false;
	bool key_right = false;
	direct dir = direct::unassign;
};
