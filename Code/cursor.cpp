#include "myheadfile.h"
#include "cursor.h"
#include <Windows.h>

px_int cursor_r = cursor_r_default;
extern POINTER_POS cursor;

px_color cursor_color;
int cursor_color_A = Default_cursor_color_A;
int cursor_color_R = Default_cursor_color_R;
int cursor_color_G = Default_cursor_color_G;
int cursor_color_B = Default_cursor_color_B;

void cursor_init()
{
	cursor_color = PX_COLOR(cursor_color_A, cursor_color_R, cursor_color_G, cursor_color_B);
	ShowCursor(FALSE); //Òþ²ØwindowsÊó±ê
}

void cursor_draw(px_surface* psurface)
{
	cursor_color = PX_COLOR(cursor_color_A, cursor_color_R, cursor_color_G, cursor_color_B);
	PX_GeoDrawCircle(psurface, (px_int)cursor.x, (px_int)cursor.y, (px_int)cursor_r, 4, cursor_color);
	PX_GeoDrawLine(psurface, cursor.x - 4, cursor.y, cursor.x + 4, cursor.y, 1, cursor_color);
	PX_GeoDrawLine(psurface, cursor.x, cursor.y - 4, cursor.x, cursor.y + 4, 1, cursor_color);
}

void cursor_CURSORDOWN()
{
	cursor_r = 0.8 * cursor_r_default;
}

void cursor_CURSORUP()
{
	cursor_r = cursor_r_default;
}

void cursor_CURSORRDOWN()
{
	cursor_r = 1.2 * cursor_r_default;
}

void cursor_CURSORRUP()
{
	cursor_r = cursor_r_default;
}