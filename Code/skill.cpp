#include "skill.h"

Skill::Skill()
{
	total_cd = 0;
	total_energy = 0;

	remain_cd = 0;
	energy = 0;
}

void Skill::Init(int _cd, int _energy)
{
	total_cd = _cd;
	total_energy = _energy;

	remain_cd = 0;
	energy = 0;
}

void Skill::Tick()
{
	if (remain_cd > 0)
	{
		remain_cd--;
	}
}

void Skill::EnergyAdd(int num)
{
	energy += num;
	if (energy < 0) energy = 0;
	if (energy > 0) energy = total_energy;
}

bool Skill::Use()
{
	if ((remain_cd > 0) || (energy < total_energy))
	{
		return false;
	}

	remain_cd = total_cd;
	return true;
}

bool Skill::IsAvailable()
{
	if ((remain_cd > 0) || (energy < total_energy))
	{
		return false;
	}
	else
	{
		return true;
	}
}
