#pragma once

/**
* @brief 从begin 到 end 线性变化
* @param pos 线性变化的位置，范围：[0,1]
* @return 类型为 (begin - end) 的类型
*/
template<typename Tb, typename Te>
auto LinearlyChange(Tb begin, Te end, double pos)
{
	auto delta = end - begin;
	auto result = delta * pos + begin;
	delta = result;
	return delta;
}