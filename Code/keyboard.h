#pragma once

#include <thread>

#define MAX_Queue 128

void keyboard_init();// ³õÊ¼»¯¼üÅÌ¼ì²â

extern std::atomic<bool> kb_w;

//typedef struct student {
//	int score;
//	struct student* next;
//} LinkList;

class KeyQueue
{
public:
	int put(int n);
	int get();
private:

	unsigned int Key[MAX_Queue] = {0};
};

