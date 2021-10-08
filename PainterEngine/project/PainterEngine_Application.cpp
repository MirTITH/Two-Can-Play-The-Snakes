#include <iostream>
#include "PainterEngine_Application.h"
#include <Windows.h>
#include "cursor.h"
#include "game_ui.h"

using namespace std;

PX_Application App;
POINTER_POS cursor = { 0,0 };

//POINTER_POS pt_last = { 0,0 };

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	if (!PX_FontModuleInitialize(&pApp->runtime.mp_resources, &pApp->fm)) return PX_FALSE;//字模
	if (!PX_LoadFontModuleFromFile(&pApp->fm, "../../Resource/gbk_32.pxf")) return PX_FALSE;//加载中文字模

	player_name[0] = "祐子";
	player_color[0] = PX_COLOR(255, 255, 200, 180);
	player_name[1] = "美绪";
	player_color[1] = PX_COLOR(255, 180, 200, 255);

	cursor_init();
	MainMenu_Init(pApp);
	Playing_Init(pApp);
	Partical_Init(pApp);
	MainMenu_Start();

	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	switch (page)
	{
	case Page::main_menu:
		break;
	case Page::playing:
		Playing_GetInput();
		break;
	case Page::counting:
		break;
	default:
		break;
	}
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	static int alpha = 0;
	//GetCursorPos(&pt); //Windows 函数，获取鼠标绝对坐标

	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 11, 33, 33));

	// 游戏时画面
	switch (page)
	{
	case Page::main_menu:
		MainMenu_Draw(pApp, elpased);
		break;
	case Page::playing:
		Playing_Draw(pApp, elpased);
		break;
	case Page::counting:
		Counting_Draw(pApp, elpased);
		break;
	case Page::exit:	
		if (alpha < 255)
		{
			alpha++;
		}
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 2, PX_ALIGN_MIDTOP, "SEE YOU NEXT TIME", PX_COLOR(alpha, 255, 255, 255));
		break;
	default:
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 2, PX_ALIGN_MIDTOP, "NO SIGNAL", PX_COLOR(180, 255, 255, 255));
		break;
	}
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);

	switch (page)
	{
	case Page::main_menu:
		MainMenu_Post_Event(e);
		break;
	case Page::playing:
		Playing_PostEvent(e);
		break;
	case Page::counting:
		Counting_PostEvent(e);
		break;
	default:
		break;
	}
	
	
	switch (e.Event)
	{
	case PX_OBJECT_EVENT_CURSORMOVE:
		cursor_color_A = Default_cursor_color_A;
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDRAG:
		cursor_color_A = Default_cursor_color_A;
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDOWN:
		cursor_color_A = Default_cursor_color_A;
		cursor_CURSORDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORUP:
		cursor_CURSORUP();
		break;
	case PX_OBJECT_EVENT_CURSORRDOWN:
		cursor_color_A = Default_cursor_color_A;
		cursor_CURSORRDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORRUP:
		cursor_CURSORRUP();
		break;
	case PX_OBJECT_EVENT_KEYDOWN:
		switch (PX_Object_Event_GetKeyDown(e))
		{
		case VK_ESCAPE:
			Playing_KeyEsc();
			break;
		case VK_ADD:
			break;
		default:
			break;
		}
	default:
		break;
	}
}
