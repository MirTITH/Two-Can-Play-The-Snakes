#include "Player.h"
#include <Windows.h>
#include "game_map.h"

void Player::GetInput()
{
	input.up(GetAsyncKeyState(keyMap.up));
	input.down(GetAsyncKeyState(keyMap.down));
	input.left(GetAsyncKeyState(keyMap.left));
	input.right(GetAsyncKeyState(keyMap.right));
}