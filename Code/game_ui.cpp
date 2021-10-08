#include "game_ui.h"

GameMap* gameMap;

Page page;

string text[PLAYER_NUM];

PX_Object* object_pause, * object_button_pause, * object_button_continue, * object_button_MainMenu;

PX_Object* object_MainMenu, * object_MainMenu_Text, * object_MainMenu_Title, * object_MainMenu_button_Muiti_Player, * object_MainMenu_button_EXIT;

PX_Object* object_Name[PLAYER_NUM], * object_Name_InputBox[PLAYER_NUM], * object_Name_Text[PLAYER_NUM], * object_Name_NAME[PLAYER_NUM], * object_Name_COLOR[PLAYER_NUM],
* object_Name_R[PLAYER_NUM],
* object_Name_G[PLAYER_NUM],
* object_Name_B[PLAYER_NUM];

PX_Object* object_Welcome, * object_Welcome_Text, * object_Welcome_PRESENT;

PX_Partical_Launcher partical_launcher[PLAYER_NUM];
px_texture partical_tex;

int tick_remain;

int mainMenu_alpha;

int welcome_alpha;

bool welcome_flag;

bool end_tick;

bool pause_tick = false;

void Button_Remake(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void Button_Continue(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void Button_Playing_to_MainMenu(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void Botton_EXIT(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void Botton_TWO_CAN_PLAY(PX_Object* pObject, PX_Object_Event e, px_void* pApp);
void GameExit();
void gameMap_Init();
void Playing_Start();
void Playing_EXIT();
void pauseMenu_Init(PX_Application* pApp);

void MainMenu_Init(PX_Application* pApp)
{
	object_MainMenu = PX_ObjectCreate(&pApp->runtime.mp_ui, PX_NULL, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, 0, 0, 0, 0);
	object_MainMenu_Title = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_MainMenu, -150, -150, 300, 40, "Two Can Play The Snakes!", &pApp->fm, PX_COLOR(255, 255, 255, 255));
	PX_Object_LabelSetAlign(object_MainMenu_Title, PX_ALIGN_MIDTOP);
	object_MainMenu_Text = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_MainMenu, -80, -80, 160, 40, "MAIN MENU", &pApp->fm, PX_COLOR(200, 255, 255, 255));
	PX_Object_LabelSetAlign(object_MainMenu_Text, PX_ALIGN_MIDTOP);
	object_MainMenu_Text = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_MainMenu, -125, 400, 250, 40, "Copyright (c) 2021 X. Y. GAMES", PX_NULL, PX_COLOR(200, 255, 255, 255));
	PX_Object_LabelSetAlign(object_MainMenu_Text, PX_ALIGN_MIDTOP);

	//按钮：Two Can Play!
	object_MainMenu_button_Muiti_Player = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_MainMenu, -100, 60, 200, 60, "Play!", &pApp->fm);
	PX_Object_PushButtonSetBackgroundColor(object_MainMenu_button_Muiti_Player, PX_COLOR(200, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_MainMenu_button_Muiti_Player, PX_COLOR(200, 11 * 2, 33 * 2, 22 * 2));
	PX_Object_PushButtonSetPushColor(object_MainMenu_button_Muiti_Player, PX_COLOR(200, 11 * 3, 33 * 3, 22 * 3));
	PX_ObjectRegisterEvent(object_MainMenu_button_Muiti_Player, PX_OBJECT_EVENT_EXECUTE, Botton_TWO_CAN_PLAY, pApp);

	//按钮：EXIT
	object_MainMenu_button_EXIT = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_MainMenu, -100, 200, 200, 60, "EXIT", &pApp->fm);
	PX_Object_PushButtonSetBackgroundColor(object_MainMenu_button_EXIT, PX_COLOR(200, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_MainMenu_button_EXIT, PX_COLOR(200, 11 * 2, 33 * 2, 22 * 2));
	PX_Object_PushButtonSetPushColor(object_MainMenu_button_EXIT, PX_COLOR(200, 11 * 3, 33 * 3, 22 * 3));
	PX_ObjectRegisterEvent(object_MainMenu_button_EXIT, PX_OBJECT_EVENT_EXECUTE, Botton_EXIT, pApp);

	// 昵称输入框
	object_Name[0] = PX_ObjectCreate(&pApp->runtime.mp_ui, object_MainMenu, -300, 30, 0, 0, 0, 0);
	object_Name[1] = PX_ObjectCreate(&pApp->runtime.mp_ui, object_MainMenu, 300, 30, 0, 0, 0, 0);
	string text[2];
	text[0] = "P1:";
	text[1] = "P2:";

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		
		object_Name_Text[i] = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_Name[i], -80, -40, 160, 40, text[i].c_str(), &pApp->fm, player_color[i]);
		object_Name_NAME[i] = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_Name[i], -80, 20, 160, 40, "NAME:", &pApp->fm, player_color[i]);
		object_Name_InputBox[i] = PX_Object_EditCreate(&pApp->runtime.mp_ui, object_Name[i], -80, 60, 160, 40, &pApp->fm);
		PX_Object_EditSetText(object_Name_InputBox[i], player_name[i].c_str());
		PX_Object_EditSetBackgroundColor(object_Name_InputBox[i], PX_COLOR(200, 11, 33, 33));
		PX_Object_EditSetTextColor(object_Name_InputBox[i], player_color[i]);

		object_Name_COLOR[i] = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_Name[i], -80, 120, 160, 40, "COLOR:", &pApp->fm, player_color[i]);
		object_Name_R[i] = PX_Object_EditCreate(&pApp->runtime.mp_ui, object_Name[i], -80, 160, 50, 40, &pApp->fm);
		object_Name_G[i] = PX_Object_EditCreate(&pApp->runtime.mp_ui, object_Name[i], -25, 160, 50, 40, &pApp->fm);
		object_Name_B[i] = PX_Object_EditCreate(&pApp->runtime.mp_ui, object_Name[i], 30, 160, 50, 40, &pApp->fm);
		PX_Object_EditSetText(object_Name_R[i], to_string(player_color[i]._argb.r).c_str());
		PX_Object_EditSetText(object_Name_G[i], to_string(player_color[i]._argb.g).c_str());
		PX_Object_EditSetText(object_Name_B[i], to_string(player_color[i]._argb.b).c_str());
		PX_Object_EditSetBackgroundColor(object_Name_R[i], PX_COLOR(255, 100, 50, 50));
		PX_Object_EditSetBackgroundColor(object_Name_G[i], PX_COLOR(255, 50, 100, 50));
		PX_Object_EditSetBackgroundColor(object_Name_B[i], PX_COLOR(255, 50, 50, 100));
		PX_Object_EditSetLimit(object_Name_R[i], "0123456789");
		PX_Object_EditSetLimit(object_Name_G[i], "0123456789");
		PX_Object_EditSetLimit(object_Name_B[i], "0123456789");
	}
	

	object_MainMenu->Visible = FALSE;
}

void MainMenu_Draw(PX_Application* pApp, px_dword elpased)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player_color[i]._argb.r = PX_atoi((PX_Object_EditGetText(object_Name_R[i])));
		player_color[i]._argb.g = PX_atoi((PX_Object_EditGetText(object_Name_G[i])));
		player_color[i]._argb.b = PX_atoi((PX_Object_EditGetText(object_Name_B[i])));
		PX_Object_LabelSetTextColor(object_Name_Text[i], player_color[i]);
		PX_Object_LabelSetTextColor(object_Name_NAME[i], player_color[i]);
		PX_Object_LabelSetTextColor(object_Name_COLOR[i], player_color[i]);
		PX_Object_EditSetTextColor(object_Name_InputBox[i], player_color[i]);
	}
	
	PX_GeoDrawRect(&pApp->runtime.RenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 77, 66));
	PX_ObjectRender(&pApp->runtime.RenderSurface, object_MainMenu, elpased);
	cursor_draw(&pApp->runtime.RenderSurface);
	PX_GeoDrawRect(&pApp->runtime.RenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(mainMenu_alpha, 11, 33, 33));

	if (mainMenu_alpha > 1)
	{
		mainMenu_alpha -= 2;
	}
}

void MainMenu_Post_Event(PX_Object_Event e)
{
	PX_ObjectPostEvent(object_MainMenu, e);
}

void MainMenu_Start()
{
	mainMenu_alpha = 255;
	object_MainMenu->Visible = TRUE;
	page = Page::main_menu;
}

void MainMenu_End()
{
	object_MainMenu->Visible = FALSE;
}

void Playing_Init(PX_Application* pApp)
{
	pauseMenu_Init(pApp);// 初始化暂停菜单
}

void Playing_Start()
{
	GetAsyncKeyState(VK_SPACE);
	GetAsyncKeyState(VK_NUMPAD0);
	gameMap_Init();
	thread sys_tick(Sys_tick_f);
	sys_tick.detach();
	page = Page::playing;
}

void Playing_EXIT()
{
	end_tick = true;
	object_pause->Visible = FALSE;
	delete gameMap;
}

void gameMap_Init()
{
	gameMap = new GameMap;
	if (PLAYER_NUM > 0) // 初始化玩家1
	{
		// 配置按键映射
		KeyMap keyMap_1;
		keyMap_1.up = 87;//w
		keyMap_1.down = 83;//s
		keyMap_1.left = 65;//a
		keyMap_1.right = 68;//d
		keyMap_1.accelerate = 32; //space
		keyMap_1.skill_1 = 69;//e
		keyMap_1.skill_2 = 81;//q
		keyMap_1.slowdown = VK_LSHIFT;

		gameMap->player[0].Init(0, keyMap_1, MAP_SIZE_X / 3, MAP_SIZE_Y / 2, 20, player_color[0]);
		gameMap->player[0].name = player_name[0];

		partical_launcher[0].LauncherInfo.hdrR = (px_float)player_color[0]._argb.r / 255;
		partical_launcher[0].LauncherInfo.hdrG = (px_float)player_color[0]._argb.g / 255;
		partical_launcher[0].LauncherInfo.hdrB = (px_float)player_color[0]._argb.b / 255;
	}

	if (PLAYER_NUM > 1) // 初始化玩家2
	{
		// 配置按键映射
		KeyMap keyMap_2;
		keyMap_2.up = VK_UP;
		keyMap_2.down = VK_DOWN;
		keyMap_2.left = VK_LEFT;
		keyMap_2.right = VK_RIGHT;
		keyMap_2.accelerate = VK_NUMPAD0;
		keyMap_2.skill_1 = VK_NUMPAD1;
		keyMap_2.skill_2 = VK_NUMPAD2;
		keyMap_2.slowdown = VK_RCONTROL;

		gameMap->player[1].Init(1, keyMap_2, (int)(MAP_SIZE_X / 1.5), MAP_SIZE_Y / 2, 20, player_color[1]);
		gameMap->player[1].name = player_name[1];

		partical_launcher[1].LauncherInfo.hdrR = (px_float)player_color[1]._argb.r / 255;
		partical_launcher[1].LauncherInfo.hdrG = (px_float)player_color[1]._argb.g / 255;
		partical_launcher[1].LauncherInfo.hdrB = (px_float)player_color[1]._argb.b / 255;
	}

	tick_remain = 60000;
}

void pauseMenu_Init(PX_Application* pApp)
{
	object_pause = PX_ObjectCreate(&pApp->runtime.mp_ui, PX_NULL, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, 0, 0, 0, 0);

	object_button_continue = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_pause, -100, 60, 200, 60, "CONTINUE", &pApp->fm);
	PX_Object_PushButtonSetBackgroundColor(object_button_continue, PX_COLOR(128, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_button_continue, PX_COLOR(128, 22, 66, 66));
	PX_Object_PushButtonSetPushColor(object_button_continue, PX_COLOR(128, 11 * 3, 33 * 3, 33 * 3));
	PX_ObjectRegisterEvent(object_button_continue, PX_OBJECT_EVENT_EXECUTE, Button_Continue, pApp);

	object_button_pause = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_pause, -100, 150, 200, 60, "REMAKE", &pApp->fm);
	//PX_Object_PushButtonSetStyle(object_button_pause, PX_OBJECT_PUSHBUTTON_STYLE_ROUNDRECT);
	PX_Object_PushButtonSetBackgroundColor(object_button_pause, PX_COLOR(128, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_button_pause, PX_COLOR(128, 22, 66, 66));
	PX_Object_PushButtonSetPushColor(object_button_pause, PX_COLOR(128, 11 * 3, 33 * 3, 33 * 3));
	PX_ObjectRegisterEvent(object_button_pause, PX_OBJECT_EVENT_EXECUTE, Button_Remake, pApp);

	object_button_MainMenu = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, object_pause, -100, 240, 200, 60, "MAIN MENU", &pApp->fm);
	//PX_Object_PushButtonSetStyle(object_button_pause, PX_OBJECT_PUSHBUTTON_STYLE_ROUNDRECT);
	PX_Object_PushButtonSetBackgroundColor(object_button_MainMenu, PX_COLOR(128, 11, 33, 33));
	PX_Object_PushButtonSetCursorColor(object_button_MainMenu, PX_COLOR(128, 22, 66, 66));
	PX_Object_PushButtonSetPushColor(object_button_MainMenu, PX_COLOR(128, 11 * 3, 33 * 3, 33 * 3));
	PX_ObjectRegisterEvent(object_button_MainMenu, PX_OBJECT_EVENT_EXECUTE, Button_Playing_to_MainMenu, pApp);

	object_pause->Visible = PX_FALSE;
}

void Playing_PostEvent(PX_Object_Event e)
{
	PX_ObjectPostEvent(object_pause, e);
}

void Playing_KeyEsc()
{
	switch (page)
	{
	case Page::playing:
		if (pause_tick == true)
		{
			Playing_Continue();
		}
		else
		{
			Playing_Pause();
		}
		break;
	case Page::counting:
		break;
	default:
		break;
	}

}

void Playing_Pause()
{
	pause_tick = true;
	object_pause->Visible = PX_TRUE;
}

void Playing_Continue()
{
	pause_tick = false;
	object_pause->Visible = PX_FALSE;
	page = Page::playing;
}

void Playing_GetInput()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		gameMap->player[i].GetInput();
	}
}

void Counting_Init()
{
	page = Page::counting;
	Playing_Pause();

}

void Counting_PostEvent(PX_Object_Event e)
{
	PX_ObjectPostEvent(object_pause, e);
}

void Counting_Draw(PX_Application* pApp, px_dword elpased)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	DrawPlayerInfo(pApp);// 绘制玩家信息

	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(100, 255, 255, 255));

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	PX_ObjectRender(&pApp->runtime.RenderSurface, object_pause, elpased);

	int winner;

	if (gameMap->player[0].snake.GetLength() > gameMap->player[1].snake.GetLength())
	{
		winner = 0;
	}
	else if (gameMap->player[0].snake.GetLength() < gameMap->player[1].snake.GetLength())
	{
		winner = 1;
	}
	else
	{
		winner = -1; // 平局
	}

	if (winner >= 0)
	{
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3 - 40, PX_ALIGN_MIDTOP, "WINNER", PX_COLOR(180, 255, 255, 255));
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, gameMap->player[winner].name.c_str(), gameMap->player[winner].defaultColor);
	}
	else
	{
		PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, "平局", PX_COLOR(180, 255, 255, 255));
	}

	cursor_draw(pRenderSurface); //绘制鼠标，请保持鼠标最后绘制
}

void Playing_Pause_Draw(PX_Application* pApp, px_dword elpased)
{
	PX_FontModuleDrawText(&pApp->runtime.RenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 3, PX_ALIGN_MIDTOP, "PAUSE", PX_COLOR(180, 255, 255, 255));
	PX_ObjectRender(&pApp->runtime.RenderSurface, object_pause, elpased);
}

/**
* @brief 绘制游戏时画面
*/
void Playing_Draw(PX_Application* pApp, px_dword elpased)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// 绘制背景
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 77, 66));

	Partical_Draw(pApp, elpased);

	DrawSnake(pApp);// 绘制蛇

	DrawFood(pApp);

	DrawPlayerInfo(pApp);// 绘制玩家信息

	// 倒计时
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH / 2, 10, PX_ALIGN_LEFTTOP, to_string(tick_remain / 1000).c_str(), PX_COLOR(180, 255, 255, 255));

	if (pause_tick)
	{
		Playing_Pause_Draw(pApp, elpased);
	}
	else
	{
		if (cursor_color_A > 0)
		{
			cursor_color_A--;
		}
	}


	cursor_draw(pRenderSurface); //绘制鼠标，请保持鼠标最后绘制
}

void DrawSnake(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int pOrder = 0; pOrder < PLAYER_NUM; pOrder++)
	{
		SnakeBlock* snakeBlock;

		px_int r;
		px_int lineWidth;

		for (int i = 0; ; i++)
		{
			snakeBlock = gameMap->player[pOrder].snake.Get(i);
			if (snakeBlock == NULL) break;

			// 绘制蛇
			if (gameMap->player[pOrder].snake.Get(i)->food == 0)
			{
				if (i == 0) // 蛇头
				{
					r = 3;
					lineWidth = 1;
				}
				else
				{
					r = 2;
					lineWidth = 1;
				}
			}
			else
			{
				r = 3;
				lineWidth = 2;
			}

			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), r, lineWidth, gameMap->player[pOrder].snake.GetColor(i));
		}
	}
}

void DrawPlayerInfo(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	text[0] = "P1\n" + gameMap->player[0].name + "\nLENGTH: " + to_string(gameMap->player[0].snake.GetLength());
	text[1] = "P2\n" + gameMap->player[1].name + "\nLENGTH: " + to_string(gameMap->player[1].snake.GetLength());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 40, PX_ALIGN_LEFTTOP, text[0].c_str(), gameMap->player[0].defaultColor);
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH - 130, 40, PX_ALIGN_LEFTTOP, text[1].c_str(), gameMap->player[1].defaultColor);
}

void DrawFood(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			if (gameMap->GetMapBlock(x, y).foodNum != 0)
			{
				PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(x), MapToScreen_y(y), (px_int)6, 3, gameMap->GetMapBlock(x, y).food_color);
			}
		}
	}
}

void Sys_tick_f()
{
	chrono::system_clock::time_point until;
	end_tick = false;

	while (!end_tick)
	{
		while (pause_tick)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
		}

		until = chrono::system_clock::now();
		until += chrono::milliseconds(1);

		gameMap->Update();
		tick_remain--;

		if (page == Page::playing && tick_remain == 0)
		{
			Counting_Init();
		}

		//Sleep(10);
		while (until > chrono::system_clock::now());
	}
}

void Button_Remake(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	//cout << "Hello" << endl;
	delete gameMap;
	this_thread::sleep_for(chrono::milliseconds(500));
	gameMap_Init();
	Playing_Continue();
}

void Button_Continue(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	Playing_Continue();
}

void Button_Playing_to_MainMenu(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	Playing_Continue();
	this_thread::sleep_for(chrono::milliseconds(200));
	Playing_EXIT();
	MainMenu_Start();
}

void Botton_EXIT(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	page = Page::exit;
	thread game_exit(GameExit);
	game_exit.detach();
}

void Botton_TWO_CAN_PLAY(PX_Object* pObject, PX_Object_Event e, px_void* pApp)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player_name[i] = PX_Object_EditGetText(object_Name_InputBox[i]);
	}
	
	MainMenu_End();
	Playing_Start();
}

void GameExit()
{
	this_thread::sleep_for(chrono::milliseconds(1000));
	exit(0);
}

void Partical_Init(PX_Application* pApp)
{
	PX_ParticalLauncher_InitializeInfo partical_info;
	PX_LoadTextureFromFile(&pApp->runtime.mp_resources, &partical_tex, "../../Resource/particle_1.traw");
	PX_ParticalLauncherInitializeDefault(&partical_info);
	partical_info.tex = &partical_tex;
	partical_info.position.x = PX_APPLICATION_SURFACE_WIDTH / 2;
	partical_info.position.y = PX_APPLICATION_SURFACE_HEIGHT / 2;
	partical_info.direction = PX_POINT(0, -1, 0);
	partical_info.velocity = 80;
	partical_info.deviation_velocity = 20;
	partical_info.ak = 0.995;
	partical_info.generateDuration = 10;
	partical_info.maxCount = 300;
	partical_info.alive = 2000;
	partical_info.deviation_rangAngle = 30;
	partical_info.alpha = 0.5;
	partical_info.atomsize = 0.3;
	partical_info.sizeincrease = 0.3;
	partical_info.deviation_atomsize = 0.1;
	partical_info.alphaincrease = -0.3;
	partical_info.launchCount = 0;

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		PX_ParticalLauncherCreate(&partical_launcher[i], &pApp->runtime.mp_game, partical_info);
	}
}

void Partical_Draw(PX_Application* pApp, px_dword elpased)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		PX_ParticalLauncherRender(&pApp->runtime.RenderSurface, &partical_launcher[i], elpased);
	}
	
}

void Welcome_Init(PX_Application* pApp)
{
	object_Welcome = PX_ObjectCreate(&pApp->runtime.mp_ui, PX_NULL, PX_APPLICATION_SURFACE_WIDTH / 2, PX_APPLICATION_SURFACE_HEIGHT / 2, 0, 0, 0, 0);
	object_Welcome_Text = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_Welcome, -80, -60, 160, 40, "X. Y. GAMES", &pApp->fm, PX_COLOR(200, 255, 255, 255));
	PX_Object_LabelSetAlign(object_Welcome_Text, PX_ALIGN_CENTER);

	object_Welcome_PRESENT = PX_Object_LabelCreate(&pApp->runtime.mp_ui, object_Welcome, -80, 60, 160, 40, "PRESENT", &pApp->fm, PX_COLOR(200, 255, 255, 255));
	PX_Object_LabelSetAlign(object_Welcome_PRESENT, PX_ALIGN_CENTER);
	object_Welcome->Visible = FALSE;
}

void Welcome_Draw(PX_Application* pApp, px_dword elpased)
{
	if (welcome_flag)
	{
		if (welcome_alpha < 252)
		{
			welcome_alpha += 2;
		}
		else
		{
			this_thread::sleep_for(chrono::milliseconds(1000));
			welcome_flag = false;
		}
	}
	else
	{
		if (welcome_alpha > 3)
		{
			welcome_alpha -= 4;
		}
		else
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			MainMenu_Start();
		}
	}
	


	PX_Object_LabelSetTextColor(object_Welcome_Text, PX_COLOR(welcome_alpha,255,255,255));
	PX_Object_LabelSetTextColor(object_Welcome_PRESENT, PX_COLOR(welcome_alpha, 255, 255, 255));

	PX_ObjectRender(&pApp->runtime.RenderSurface, object_Welcome, elpased);
}

void Welcome_Start()
{
	welcome_flag = true;
	welcome_alpha = 0;
	object_Welcome->Visible = TRUE;
	page = Page::welcome;
}