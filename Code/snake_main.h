#pragma once

#include "PainterEngine_Application.h"
#include "keyboard.h"

#define MAP_SIZE_X (PX_APPLICATION_SURFACE_HEIGHT / 2)
#define MAP_SIZE_Y (PX_APPLICATION_SURFACE_WIDTH / 2)

struct Snake_Unit
{
	int x;// x坐标
	int y;// y坐标
	Direct Dir = Direct::unassign;// 运行方向
	int food; //这一节的食物数
	px_color color; //颜色 
	Snake_Unit* next;
};

class Player
{
public:
	Player(int PlayerID); //PlayerID 为 1 或 2
	~Player();
	void get_input();
	KeyInput input;// 按键输入与输出
	KeyMap keymap;// 键位映射
	Snake_Unit* snake(int length);// 头length=0，尾length = -1，返回NULL表示不存在
	void snake_addtotail(Snake_Unit* NewSnake); // 在尾部增加
	int snake_delfromhead(int num);// 从头部删除num节，返回成功删除的节数

	/*
		移动，此函数要执行T次后才会移动一格
		返回状态
			0 未移动
			1 成功移动一格
	*/
	int move(); 
	int T = 1; //多少周期后前进一格
private:
	Snake_Unit* snake_head = NULL; //蛇头
	int timer = 0;
};

int Snake_main_init();

class Snake
{
public:
	Snake(int x, int y, int length, px_color color);
	~Snake();

	// 头length=0，尾length = -1，返回NULL表示不存在
	Snake_Unit* Get(int length);

	// 获取蛇的长度
	int Length();

	// 在尾部增加
	void AddToTail(Snake_Unit* NewSnake); 
	
	// 从头部删除num节，返回成功删除的节数
	int DelFromHead(int num);

	// 向设定的方向移动，需要执行T次才移动一格
	int move();

	Direct dir = Direct::up; //蛇头运行方向
	int T = 10; //多少周期后前进一格
private:
	Snake_Unit* snake_head = NULL; //蛇头
	int timer = 0;
};
