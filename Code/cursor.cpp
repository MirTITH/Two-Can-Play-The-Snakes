#include "myheadfile.h"
#include "cursor.h"
#include <Windows.h>

px_int cursor_r = cursor_r_default;
extern POINTER_POS pt;

void cursor_init()
{
	ShowCursor(FALSE); //Òþ²ØwindowsÊó±ê
}

void cursor_draw(px_surface* psurface)
{
	PX_GeoDrawCircle(psurface, (px_int)pt.x, (px_int)pt.y, (px_int)cursor_r, 4, cursor_color);
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