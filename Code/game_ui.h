#pragma once

#include <chrono>
#include <Windows.h>
#include <thread>
#include "game_map.h"
#include "cursor.h"

enum class Page
{
	welcome,
	main_menu,
	playing,
	counting,
	exit
};


extern Page page;
extern int tick_remain;

void MainMenu_Init(PX_Application* pApp);

void MainMenu_Draw(PX_Application* pApp, px_dword elpased);

void MainMenu_Post_Event(PX_Object_Event e);

void MainMenu_Start();

void MainMenu_End();

void Playing_Init(PX_Application* pApp);

/**
* @brief 获取玩家输入
*/
void Playing_GetInput();

void Playing_Pause();

void Playing_Continue();

void Playing_KeyEsc();

void Playing_PostEvent(PX_Object_Event e);

void Playing_Draw(PX_Application* pApp, px_dword elpased);

/**
* 绘制蛇
*/
void DrawSnake(PX_Application* pApp);

void DrawPlayerInfo(PX_Application* pApp);

void Counting_PostEvent(PX_Object_Event e);

void Counting_Draw(PX_Application* pApp, px_dword elpased);

void DrawFood(PX_Application* pApp);

void Partical_Init(PX_Application* pApp);
void Partical_Draw(PX_Application* pApp, px_dword elpased);

void Welcome_Init(PX_Application* pApp);

void Welcome_Draw(PX_Application* pApp, px_dword elpased);

void Welcome_Start();

// 系统时钟计时函数
void Sys_tick_f();