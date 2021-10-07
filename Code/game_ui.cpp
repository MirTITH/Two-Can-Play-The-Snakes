#include "game_ui.h"

GameMap gameMap;

string text[PLAYER_NUM];

int tick_remain;

bool is_pause = false;

void Playing_init()
{
	tick_remain = 90000;
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

		gameMap.player[0].Init(1, keyMap_1, MAP_SIZE_X / 3, MAP_SIZE_Y / 2, 20, PX_COLOR(255, 255, 155, 144));
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

		gameMap.player[1].Init(2, keyMap_2, (int)(MAP_SIZE_X / 1.5), MAP_SIZE_Y / 2, 20, PX_COLOR(255, 144, 155, 255));
	}

	srand((int)time(NULL));

	thread sys_tick(Sys_tick_f);
	sys_tick.detach();

	cursor_init();
}

void Playing_GetInput()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		gameMap.player[i].GetInput();
	}
}

/**
* @brief 绘制游戏时画面
*/
void Playing_Draw(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// 绘制背景
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 77, 66));

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	DrawPlayerInfo(pApp);// 绘制玩家信息

	// 倒计时
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, 10, PX_ALIGN_LEFTTOP, to_string(tick_remain / 1000).c_str(), PX_COLOR(180,255,255,255));

	if (cursor_color_A > 0)
	{
		cursor_color_A--;
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
			snakeBlock = gameMap.player[pOrder].snake.Get(i);
			if (snakeBlock == NULL) break;

			// 绘制蛇
			if (gameMap.player[pOrder].snake.Get(i)->food == 0)
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

			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), r, lineWidth, gameMap.player[pOrder].snake.GetColor(i));
		}
	}
}

void DrawPlayerInfo(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	text[0] = "P1\n\n长度: " + to_string(gameMap.player[0].snake.GetLength());
	text[1] = "P2\n\n长度: " + to_string(gameMap.player[1].snake.GetLength());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 40, PX_ALIGN_LEFTTOP, text[0].c_str(), gameMap.player[0].defaultColor);
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH - 130, 40, PX_ALIGN_LEFTTOP, text[1].c_str(), gameMap.player[1].defaultColor);
}

void DrawFood(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			if (gameMap.GetMapBlock(x, y).foodNum != 0)
			{
				PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(x), MapToScreen_y(y), (px_int)6, 3, gameMap.GetMapBlock(x, y).food_color);
			}
		}
	}
}

void Sys_tick_f()
{
	chrono::system_clock::time_point until;
	while (!is_pause)
	{
		until = chrono::system_clock::now();
		until += chrono::milliseconds(1);

		gameMap.Update();
		tick_remain--;

		//Sleep(10);
		while (until > chrono::system_clock::now());
		//this_thread::sleep_for(chrono::milliseconds(1));
	}
}