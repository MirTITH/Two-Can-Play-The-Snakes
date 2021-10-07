#include "game_ui.h"

GameMap* gameMap;

Page page;

string text[PLAYER_NUM];

PX_Object* object_pause, * object_button_pause, * object_button_continue;

int tick_remain;

bool end_tick;

bool pause_tick = false;

void Button_Remake(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void Button_Continue(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void gameMap_Init();
void pauseMenu_Init(PX_Application* pApp);

void Playing_init(PX_Application* pApp)
{
	cursor_init();
	pauseMenu_Init(pApp);// 初始化暂停菜单
	gameMap_Init();


	thread sys_tick(Sys_tick_f);
	sys_tick.detach();
	page = Page::playing;
}

void gameMap_Init()
{
	gameMap = new GameMap;
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

		gameMap->player[0].Init(1, keyMap_1, MAP_SIZE_X / 3, MAP_SIZE_Y / 2, 20, PX_COLOR(255, 255, 155, 144));
		gameMap->player[0].name = "小红";
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

		gameMap->player[1].Init(2, keyMap_2, (int)(MAP_SIZE_X / 1.5), MAP_SIZE_Y / 2, 20, PX_COLOR(255, 144, 155, 255));
		gameMap->player[1].name = "小蓝";
	}

	tick_remain = 9000;
}

void pauseMenu_Init(PX_Application* pApp)
{
	object_pause = PX_ObjectCreate(&pApp->runtime.mp_ui, PX_NULL, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, 0, 0, 0, 0);
	object_button_pause = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_pause, -64, 40, 128, 40, "REMAKE", &pApp->fm);
	//PX_Object_PushButtonSetStyle(object_button_pause, PX_OBJECT_PUSHBUTTON_STYLE_ROUNDRECT);
	PX_Object_PushButtonSetBackgroundColor(object_button_pause, PX_COLOR(128, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_button_pause, PX_COLOR(128, 22, 66, 66));
	PX_Object_PushButtonSetPushColor(object_button_pause, PX_COLOR(128, 11 * 3, 33 * 3, 33 * 3));
	PX_ObjectRegisterEvent(object_button_pause, PX_OBJECT_EVENT_EXECUTE, Button_Remake, pApp);
	
	object_button_continue = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_pause, -64, 100, 128, 40, "CONTINUE", &pApp->fm);
	PX_Object_PushButtonSetBackgroundColor(object_button_continue, PX_COLOR(128, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_button_continue, PX_COLOR(128, 22, 66, 66));
	PX_Object_PushButtonSetPushColor(object_button_continue, PX_COLOR(128, 11 * 3, 33 * 3, 33 * 3));
	PX_ObjectRegisterEvent(object_button_continue, PX_OBJECT_EVENT_EXECUTE, Button_Continue, pApp);

	object_pause->Visible = PX_FALSE;
}

void Playing_PostEvent(PX_Object_Event e)
{
	PX_ObjectPostEvent(object_pause, e);
}

void Playing_KeyEsc()
{
	switch (page)
	{
	case Page::playing:
		if (pause_tick == true)
		{
			Playing_Continue();
		}
		else
		{
			Playing_Pause();
		}
		break;
	case Page::counting:
		break;
	default:
		break;
	}
	
}

void Playing_Pause()
{
	pause_tick = true;
	object_pause->Visible = PX_TRUE;
}

void Playing_Continue()
{
	pause_tick = false;
	object_pause->Visible = PX_FALSE;
	page = Page::playing;
}

void Playing_GetInput()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		gameMap->player[i].GetInput();
	}
}

void Counting_Init()
{
	page = Page::counting;
	Playing_Pause();

}

void Counting_Draw(PX_Application* pApp, px_dword elpased)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	DrawPlayerInfo(pApp);// 绘制玩家信息

	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(100, 255, 255, 255));

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	PX_ObjectRender(&pApp->runtime.RenderSurface, object_pause, elpased);

	int winner;

	if (gameMap->player[0].snake.GetLength() > gameMap->player[1].snake.GetLength())
	{
		winner = 0;
	}
	else if (gameMap->player[0].snake.GetLength() < gameMap->player[1].snake.GetLength())
	{
		winner = 1;
	}
	else
	{
		winner = -1; // 平局
	}

	if (winner >= 0)
	{
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3 - 40, PX_ALIGN_MIDTOP, "WINNER", PX_COLOR(180, 255, 255, 255));
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, gameMap->player[winner].name.c_str(), gameMap->player[winner].defaultColor);
	}
	else
	{
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, "平局", PX_COLOR(180, 255, 255, 255));
	}

	cursor_draw(pRenderSurface); //绘制鼠标，请保持鼠标最后绘制
}

void DrawPlaying_Pause(PX_Application* pApp, px_dword elpased)
{
	PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, "PAUSE", PX_COLOR(180, 255, 255, 255));
	PX_ObjectRender(&pApp->runtime.RenderSurface, object_pause, elpased);
}

/**
* @brief 绘制游戏时画面
*/
void Playing_Draw(PX_Application* pApp, px_dword elpased)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// 绘制背景
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 77, 66));

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	DrawPlayerInfo(pApp);// 绘制玩家信息

	// 倒计时
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, 10, PX_ALIGN_LEFTTOP, to_string(tick_remain / 1000).c_str(), PX_COLOR(180,255,255,255));

	if (pause_tick)
	{
		DrawPlaying_Pause(pApp, elpased);
	}
	else
	{
		if (cursor_color_A > 0)
		{
			cursor_color_A--;
		}
	}

	
	cursor_draw(pRenderSurface); //绘制鼠标，请保持鼠标最后绘制
}

void DrawSnake(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int pOrder = 0; pOrder < PLAYER_NUM; pOrder++)
	{
		SnakeBlock* snakeBlock;

		px_int r;
		px_int lineWidth;

		for (int i = 0; ; i++)
		{
			snakeBlock = gameMap->player[pOrder].snake.Get(i);
			if (snakeBlock == NULL) break;

			// 绘制蛇
			if (gameMap->player[pOrder].snake.Get(i)->food == 0)
			{
				if (i == 0) // 蛇头
				{
					r = 3;
					lineWidth = 1;
				}
				else
				{
					r = 2;
					lineWidth = 1;
				}
			}
			else
			{
				r = 3;
				lineWidth = 2;
			}

			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), r, lineWidth, gameMap->player[pOrder].snake.GetColor(i));
		}
	}
}

void DrawPlayerInfo(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	text[0] = "P1\n" + gameMap->player[0].name + "\n长度: " + to_string(gameMap->player[0].snake.GetLength());
	text[1] = "P2\n" + gameMap->player[1].name + "\n长度: " + to_string(gameMap->player[1].snake.GetLength());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 40, PX_ALIGN_LEFTTOP, text[0].c_str(), gameMap->player[0].defaultColor);
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH - 130, 40, PX_ALIGN_LEFTTOP, text[1].c_str(), gameMap->player[1].defaultColor);
}

void DrawFood(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			if (gameMap->GetMapBlock(x, y).foodNum != 0)
			{
				PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(x), MapToScreen_y(y), (px_int)6, 3, gameMap->GetMapBlock(x, y).food_color);
			}
		}
	}
}

void Sys_tick_f()
{
	chrono::system_clock::time_point until;
	end_tick = false;

	while (!end_tick)
	{
		while(pause_tick)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
		}

		until = chrono::system_clock::now();
		until += chrono::milliseconds(1);

		gameMap->Update();
		tick_remain--;

		if (page == Page::playing && tick_remain == 0)
		{
			Counting_Init();
		}

		//Sleep(10);
		while (until > chrono::system_clock::now());
	}
}

void Button_Remake(PX_Object *pObject, PX_Object_Event e, px_void *pApp)
{
	//cout << "Hello" << endl;
	delete gameMap;
	gameMap_Init();
	Playing_Continue();
}

void Button_Continue(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	Playing_Continue();
}