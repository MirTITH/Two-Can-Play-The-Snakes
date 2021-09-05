#include "game_map.h"

px_int MapToScreen_x(int x)
{
	return (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X + MAP_DISPLAY_X / MAP_SIZE_X) / 2 + MAP_DISPLAY_X * x / MAP_SIZE_X;
}

px_int MapToScreen_y(int y)
{
	return (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y + MAP_DISPLAY_Y / MAP_SIZE_Y) / 2 + MAP_DISPLAY_Y * y / MAP_SIZE_Y;
}

GameMap::GameMap()
{
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			mapBlock[x][y].tryTake = false;
			mapBlock[x][y].isExistObstacle = false;
			mapBlock[x][y].isExistSnake = false;
			mapBlock[x][y].obstacle_color = PX_COLOR(255, 0, 0, 0);
			mapBlock[x][y].snakeBlock = NULL;
			mapBlock[x][y].snake_Player = NULL;
		}
	}
}

int GameMap::AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock)
{
	if (mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake)
	{
		return 1;
	}

	if (mapBlock[_snakeBlock->x][_snakeBlock->y].isExistObstacle)
	{
		return 2;
	}

	if (mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake == false)
	{
		mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake = true;
		mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake = false;
		mapBlock[_snakeBlock->x][_snakeBlock->y].snakeBlock = _snakeBlock;
		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player = _snakePlayer;
	}
	else
	{
		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player->snake.DelHead();
		_snakePlayer->snake.DelHead();
		mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake = false;
		mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake = false;
		mapBlock[_snakeBlock->x][_snakeBlock->y].snakeBlock = NULL;
		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player = NULL;
	}

	return 0;
}

SnakeBlock* GameMap::DelSnakeBlock(int x, int y)
{
	SnakeBlock* result = mapBlock[x][y].snakeBlock;
	mapBlock[x][y].isExistSnake = false;
	mapBlock[x][y].snakeBlock = NULL;
	mapBlock[x][y].snake_Player = NULL;
	return result;
}