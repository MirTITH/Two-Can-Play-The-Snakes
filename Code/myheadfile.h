#pragma once

#include "PainterEngine_Application.h"

// 鼠标位置
typedef struct pointer_pos
{
	px_float x;
	px_float y;
}POINTER_POS;

enum class Direct
{
	unassign,
	up,
	down,
	left,
	right
};

// 系统时钟计时函数
void Sys_tick_f();