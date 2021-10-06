#include "game_ui.h"

string text[PLAYER_NUM];

/**
* @brief 绘制游戏时画面
*/
void Draw_Playing(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// 绘制背景
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 44, 77));

	DrawSnake(pApp);// 绘制蛇

	DrawPlayerInfo(pApp);// 绘制玩家信息

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
			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), (px_int)2, 1, snakeBlock->color);
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