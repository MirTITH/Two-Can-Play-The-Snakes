#pragma once

class Skill
{
public:
	/**
	* @brief 创建技能，之后需要执行Init()
	*/
	Skill();
	/**
	* @brief 初始化技能
	* @param _energy 技能所需的能量（不需要设为0）
	*/
	void Init(int _cd, int _energy);

	void Tick();

	/**
	* @brief 增加技能能量，总能量不会低于0，不会超过total_energy
	* @param num 增加的值，为负则减少能量
	*/
	void EnergyAdd(int num);

	/**
	* @brief 使用技能
	* @return true 成功使用技能 false 无法使用技能
	*/
	bool Use();

	/**
	* @return 当前技能是否可用
	*/
	bool IsAvailable();

	int energy; //技能当前能量
	int total_energy; //技能施放所需能量

	int remain_cd; //技能剩余cd (tick)
	int total_cd; //技能总cd
private:
};