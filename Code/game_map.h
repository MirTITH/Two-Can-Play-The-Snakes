#pragma once

#include "PainterEngine_Application.h"

#define MAP_DISPLAY_X 1000
#define MAP_DISPLAY_Y 720

#define MAP_SIZE_X (MAP_DISPLAY_X / 8)
#define MAP_SIZE_Y (MAP_DISPLAY_Y / 8)

const int MAP_EDGE_TO_SCREEN_L = (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// 地图左边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_U = (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// 地图上边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_R = PX_APPLICATION_SURFACE_WIDTH - 1 - (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// 地图右边界对应的屏幕坐标
const int MAP_EDGE_TO_SCREEN_D = PX_APPLICATION_SURFACE_HEIGHT - 1 - (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// 地图下边界对应的屏幕坐标

px_int MapToScreen_x(int x);

px_int MapToScreen_y(int y);