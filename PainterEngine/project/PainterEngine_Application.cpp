#include "myheadfile.h"

PX_Application App;
POINTER_POS pt = { 0,0 };


px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	ShowCursor(FALSE); //Òþ²ØwindowsÊó±ê
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	//GetCursorPos(&pt);
	//Sleep(1000/144);
	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 0, 0, 0));
	PX_GeoDrawCircle(pRenderSurface, pt.x, pt.y, 20, 5, PX_COLOR(255, 102, 204, 255));
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	if (e.Event == PX_OBJECT_EVENT_CURSORMOVE)
	{
		pt.x = PX_Object_Event_GetCursorX(e);
		pt.y = PX_Object_Event_GetCursorY(e);
	}
}

