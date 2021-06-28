#include "myheadfile.h"
#include <Windows.h>
#include "cursor.h"

PX_Application App;
POINTER_POS pt = { 0,0 };
POINTER_POS ball_pos = { PX_APPLICATION_SURFACE_HEIGHT / 2, PX_APPLICATION_SURFACE_WIDTH / 2 };
//POINTER_POS pt_last = { 0,0 };

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	cursor_init();
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	//GetCursorPos(&pt); //Windows 函数，获取鼠标绝对坐标
	//Sleep(1000/5);
	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 255, 255, 255));
	PX_GeoDrawRect(pRenderSurface, 0, 0, 1279, 799, PX_COLOR(255, 55, 44, 77));
	PX_GeoDrawCircle(pRenderSurface, (px_int)ball_pos.x, (px_int)ball_pos.y, (px_int)5, 4, PX_COLOR(255, 145, 224, 200));
	cursor_draw(pRenderSurface); //请保持鼠标最后绘制
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	
	if (e.Event == PX_OBJECT_EVENT_CURSORMOVE || e.Event == PX_OBJECT_EVENT_CURSORDRAG)
	{
		pt.x = PX_Object_Event_GetCursorX(e);
		pt.y = PX_Object_Event_GetCursorY(e);
	}

	if (e.Event == PX_OBJECT_EVENT_CURSORDOWN)
	{
		cursor_CURSORDOWN();
	}

	if (e.Event == PX_OBJECT_EVENT_CURSORUP)
	{
		cursor_CURSORUP();
	}

	if (e.Event == PX_OBJECT_EVENT_CURSORRDOWN)
	{
		cursor_CURSORRDOWN();
	}

	if (e.Event == PX_OBJECT_EVENT_CURSORRUP)
	{
		cursor_CURSORRUP();
	}

	if (e.Event == PX_OBJECT_EVENT_KEYDOWN)
	{
		switch (PX_Object_Event_GetKeyDown(e))
		{
		case 87:
			ball_pos.y -= 5;
			break;
		case 83:
			ball_pos.y += 5;
			break;
		case 65:
			ball_pos.x -= 5;
			break;
		case 68:
			ball_pos.x += 5;
			break;
		default:
			break;
		}
		
	}

	//pt_last.x = pt.x;
	//pt_last.y = pt.y;

	
}

