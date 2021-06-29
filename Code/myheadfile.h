#pragma once

#include "PainterEngine_Application.h"

//  Û±ÍŒª÷√
typedef struct pointer_pos
{
	px_float x;
	px_float y;
}POINTER_POS;

enum class direct
{
	unassign,
	up,
	down,
	left,
	right
};