#include "game_ui.h"

string text[PLAYER_NUM];

int tick_remain = 90000;

/**
* @brief 绘制游戏时画面
*/
void Draw_Playing(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// 绘制背景
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 77, 66));

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	DrawPlayerInfo(pApp);// 绘制玩家信息

	// 倒计时
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, 10, PX_ALIGN_LEFTTOP, to_string(tick_remain / 1000).c_str(), PX_COLOR(180,255,255,255));

	cursor_draw(pRenderSurface); //绘制鼠标，请保持鼠标最后绘制
}

void DrawSnake(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int pOrder = 0; pOrder < PLAYER_NUM; pOrder++)
	{
		SnakeBlock* snakeBlock;
		for (int i = 0; ; i++)
		{
			snakeBlock = gameMap.player[pOrder].snake.Get(i);
			if (snakeBlock == NULL) break;
			// 绘制蛇
			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), (px_int)2, 1, gameMap.player[pOrder].snake.GetColor(i));
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