#include "keyboard.h"

#include <iostream>
#include <thread>
#include "PainterEngine_Application.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

std::atomic<bool> kb_w(true);

//bool kb_w = true;

void keyboard_processor();

void keyboard_init()
{
	thread keyboard(keyboard_processor);
	keyboard.detach();
	return;
}

void keyboard_processor()
{
	while (true)
	{
		if (_kbhit())
		{
			kb_w = true;
		}
		else
		{
			kb_w = false;
		}
		Sleep(100);
	}
	
}

int KeyQueue::get()
{
	int result = -1;

	if (Key[0] != 0)
	{
		result = Key[0];
		for (int i = 0; i < MAX_Queue - 1; i++)
		{
			Key[i] = Key[i + 1];
		}
	}

	return result;
}

int KeyQueue::put(int n)
{
	for (int i = 0; i < MAX_Queue; i++)
	{
		if (Key[i] == 0)
		{
			Key[i] = n;
			return 0;
		}
			
	}
	return -1;
}