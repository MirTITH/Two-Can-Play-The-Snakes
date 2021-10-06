#pragma once
#include "myheadfile.h"
#include "Player.h"
#include "game_map.h"
#include "cursor.h"

extern GameMap gameMap;

void Draw_Playing(PX_Application* pApp);

/**
* ªÊ÷∆…ﬂ
*/
void DrawSnake(PX_Application* pApp);

void DrawPlayerInfo(PX_Application* pApp);

void DrawFood(PX_Application* pApp);
