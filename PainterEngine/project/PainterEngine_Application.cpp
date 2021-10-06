#include "myheadfile.h"
#include "PainterEngine_Application.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include "cursor.h"
#include "keyboard.h"
//#include "snake_main.h"
#include "Player.h"
#include "game_map.h"
#include "game_ui.h"
#include <chrono>

using namespace std;

PX_Application App;
POINTER_POS cursor = { 0,0 };

GameMap gameMap;

CRITICAL_SECTION g_cs;

//POINTER_POS pt_last = { 0,0 };

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	if (!PX_FontModuleInitialize(&pApp->runtime.mp_resources, &pApp->fm)) return PX_FALSE;//字模
	if (!PX_LoadFontModuleFromFile(&pApp->fm, "../../Resource/gbk_32.pxf")) return PX_FALSE;//加载中文字模
	cursor_init();

	srand(time(NULL));


	if (PLAYER_NUM > 0) // 初始化玩家1
	{
		// 配置按键映射
		KeyMap keyMap_1;
		keyMap_1.up = 87;//w
		keyMap_1.down = 83;//s
		keyMap_1.left = 65;//a
		keyMap_1.right = 68;//d
		keyMap_1.accelerate = 32; //space
		keyMap_1.skill_1 = 69;//e
		keyMap_1.skill_2 = 81;//q
		keyMap_1.slowdown = VK_LSHIFT;

		gameMap.player[0].Init(1, keyMap_1, MAP_SIZE_X / 3, MAP_SIZE_Y / 2, 20, PX_COLOR(255, 255, 255, 255));
	}

	if (PLAYER_NUM > 1) // 初始化玩家2
	{
		// 配置按键映射
		KeyMap keyMap_2;
		keyMap_2.up = VK_UP;
		keyMap_2.down = VK_DOWN;
		keyMap_2.left = VK_LEFT;
		keyMap_2.right = VK_RIGHT;
		keyMap_2.accelerate = VK_NUMPAD0;
		keyMap_2.skill_1 = VK_NUMPAD1;
		keyMap_2.skill_2 = VK_NUMPAD2;
		keyMap_2.slowdown = VK_RCONTROL;
			
		gameMap.player[1].Init(2, keyMap_2, (int)(MAP_SIZE_X / 1.5), MAP_SIZE_Y / 2, 20, PX_COLOR(255, 157, 208, 136));
	}

	InitializeCriticalSection(&g_cs);//初始化临界区
	thread sys_tick(Sys_tick_f);
	sys_tick.detach();
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	// 获取玩家输入
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		gameMap.player[i].GetInput();
	}
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	//GetCursorPos(&pt); //Windows 函数，获取鼠标绝对坐标

	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 0, 0, 0));

	// 游戏时画面
	Draw_Playing(pApp);
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	
	switch (e.Event)
	{
	case PX_OBJECT_EVENT_CURSORMOVE:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDRAG:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDOWN:
		cursor_CURSORDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORUP:
		cursor_CURSORUP();
		break;
	case PX_OBJECT_EVENT_CURSORRDOWN:
		cursor_CURSORRDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORRUP:
		cursor_CURSORRUP();
		break;
	default:
		break;
	}

	//if (e.Event == PX_OBJECT_EVENT_KEYDOWN)
	//{
	//	keyboard.put(PX_Object_Event_GetKeyDown(e));
	//	/*switch ()
	//	{
	//	case 87:
	//		ball_pos.y -= 5;
	//		break;
	//	case 83:
	//		ball_pos.y += 5;
	//		break;
	//	case 65:
	//		ball_pos.x -= 5;
	//		break;
	//	case 68:
	//		ball_pos.x += 5;
	//		break;
	//	default:
	//		break;
	//	}*/
	//	
	//}

	//pt_last.x = pt.x;
	//pt_last.y = pt.y;

	
}

void Sys_tick_f()
{
	chrono::system_clock::time_point until;
	while (true)
	{
		until = chrono::system_clock::now();
		until += chrono::milliseconds(1);
		EnterCriticalSection(&g_cs);

		gameMap.Update();

		LeaveCriticalSection(&g_cs);
		while (until > chrono::system_clock::now());
		//this_thread::sleep_until(until);
	}
}