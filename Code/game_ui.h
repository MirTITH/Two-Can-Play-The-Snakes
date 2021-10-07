#pragma once
#include <chrono>
#include <Windows.h>
#include <thread>
#include "myheadfile.h"
#include "Player.h"
#include "game_map.h"
#include "cursor.h"

extern int tick_remain;

void Playing_init();

/**
* @brief 获取玩家输入
*/
void Playing_GetInput();

void Playing_Draw(PX_Application* pApp);


/**
* 绘制蛇
*/
void DrawSnake(PX_Application* pApp);

void DrawPlayerInfo(PX_Application* pApp);

void DrawFood(PX_Application* pApp);

// 系统时钟计时函数
void Sys_tick_f();