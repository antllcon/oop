#ifndef FIND_MAX_H
#define FIND_MAX_H

#include <algorithm>
#include <concepts>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMaxEx(const std::vector<T>& vec, T& maxValue, const Less& less = std::less<T>())
{
	static_assert(std::predicate<Less, const T&, const T&>,
		"Тип Less должен соответствовать концепции std::predicate"
		"(т.е. быть вызываемым с двумя const T& и возвращать bool)");

	if (auto maxIt = std::ranges::max_element(vec, less); maxIt != vec.end())
	{
		maxValue = *maxIt;
		return true;
	}

	return false;
}

#endif // FIND_MAX_H