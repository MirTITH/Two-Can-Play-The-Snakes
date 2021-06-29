#pragma once

#include "PainterEngine_Application.h"
#include "keyboard.h"

#define MAP_SIZE_X (PX_APPLICATION_SURFACE_HEIGHT / 2)
#define MAP_SIZE_Y (PX_APPLICATION_SURFACE_WIDTH / 2)

struct Snake
{
	int x;// x坐标
	int y;// y坐标
	direct Dir;// 运行方向
	int food; //这一节的食物数
	px_color color; //颜色 
	Snake* next;
};

class Player
{
public:
	Player(int PlayerID); //PlayerID 为 1 或 2
	~Player();
	void get_input();
	KeyInput input;// 按键输入与输出
	KeyMap keymap;// 键位映射
	Snake* snake(int length);// 头length=0，尾length = -1，返回NULL表示不存在
	void snake_addtotail(Snake* NewSnake); // 在尾部增加
	int snake_delfromhead(int num);// 从头部删除num节，返回成功删除的节数

	/*
		移动，此函数要执行T次后才会移动一格
		返回状态
			0 未移动
			1 成功移动一格
	*/
	int move(); 
	int T; //多少周期后前进一格
private:
	Snake* snake_head = NULL; //蛇头
};

