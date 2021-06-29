#include "myheadfile.h"
#include "PainterEngine_Application.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include "cursor.h"
#include "keyboard.h"
using namespace std;
PX_Application App;
POINTER_POS cursor = { 0,0 };
POINTER_POS ball_pos = { PX_APPLICATION_SURFACE_HEIGHT / 2, PX_APPLICATION_SURFACE_WIDTH / 2 };
char text[20];

KeyInput Player1_Input;
KeyInput Player2_Input;

KeyMap Player1_KeyMap;
KeyMap Player2_KeyMap;


//POINTER_POS pt_last = { 0,0 };

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	if (!PX_FontModuleInitialize(&pApp->runtime.mp_resources, &pApp->fm)) return PX_FALSE;//字模
	if (!PX_LoadFontModuleFromFile(&pApp->fm, "../../Resource/gbk_32.pxf")) return PX_FALSE;//加载中文字模
	cursor_init();
	Player1_KeyMap.up = 87;
	Player1_KeyMap.down = 83;
	Player1_KeyMap.left = 65;
	Player1_KeyMap.right = 68;
	Player2_KeyMap.up = VK_UP;
	Player2_KeyMap.down = VK_DOWN;
	Player2_KeyMap.left = VK_LEFT;
	Player2_KeyMap.right = VK_RIGHT;
	//keyboard_init();
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	//GetCursorPos(&pt); //Windows 函数，获取鼠标绝对坐标
	//Sleep(1000/10);

	Player1_Input.up(GetKeyState(Player1_KeyMap.up) & 0x8000);
	Player1_Input.down(GetKeyState(Player1_KeyMap.down) & 0x8000);
	Player1_Input.left(GetKeyState(Player1_KeyMap.left) & 0x8000);
	Player1_Input.right(GetKeyState(Player1_KeyMap.right) & 0x8000);

	Player2_Input.up(GetKeyState(Player2_KeyMap.up) & 0x8000);
	Player2_Input.down(GetKeyState(Player2_KeyMap.down) & 0x8000);
	Player2_Input.left(GetKeyState(Player2_KeyMap.left) & 0x8000);
	Player2_Input.right(GetKeyState(Player2_KeyMap.right) & 0x8000);

	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 255, 255, 255));
	PX_GeoDrawRect(pRenderSurface, 0, 0, 1279, 799, PX_COLOR(255, 55, 44, 77));
	PX_GeoDrawCircle(pRenderSurface, (px_int)ball_pos.x, (px_int)ball_pos.y, (px_int)5, 4, PX_COLOR(255, 145, 224, 200));

	

	sprintf_s(text,"%d", Player1_Input.GetDir());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 100, PX_ALIGN_LEFTTOP, text, PX_COLOR(255, 255, 255, 255));

	cursor_draw(pRenderSurface); //请保持鼠标最后绘制
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	
	switch (e.Event)
	{
	case PX_OBJECT_EVENT_CURSORMOVE:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDRAG:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDOWN:
		cursor_CURSORDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORUP:
		cursor_CURSORUP();
		break;
	case PX_OBJECT_EVENT_CURSORRDOWN:
		cursor_CURSORRDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORRUP:
		cursor_CURSORRUP();
		break;
	default:
		break;
	}

	//if (e.Event == PX_OBJECT_EVENT_KEYDOWN)
	//{
	//	keyboard.put(PX_Object_Event_GetKeyDown(e));
	//	/*switch ()
	//	{
	//	case 87:
	//		ball_pos.y -= 5;
	//		break;
	//	case 83:
	//		ball_pos.y += 5;
	//		break;
	//	case 65:
	//		ball_pos.x -= 5;
	//		break;
	//	case 68:
	//		ball_pos.x += 5;
	//		break;
	//	default:
	//		break;
	//	}*/
	//	
	//}

	//pt_last.x = pt.x;
	//pt_last.y = pt.y;

	
}

