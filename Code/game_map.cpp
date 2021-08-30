#include "game_map.h"

px_int MapToScreen_x(int x)
{
	return (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X + MAP_DISPLAY_X / MAP_SIZE_X) / 2 + MAP_DISPLAY_X * x / MAP_SIZE_X;
}

px_int MapToScreen_y(int y)
{
	return (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y + MAP_DISPLAY_Y / MAP_SIZE_Y) / 2 + MAP_DISPLAY_Y * y / MAP_SIZE_Y;
}