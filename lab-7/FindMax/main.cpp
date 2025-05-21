#include <iostream>

#include <stdexcept> // для std::invalid_argument
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false; // пустой вектор — максимума нет
	}

	auto itMax = arr.begin();
	try
	{
		for (auto it = arr.begin() + 1; it != arr.end(); ++it)
		{
			if (less(*itMax, *it))
			{
				itMax = it;
			}
		}
		maxValue = *itMax; // копирование значения только после нахождения максимума
	}
	catch (...)
	{
		// Если возникло исключение (например, при сравнении или копировании),
		// состояние maxValue не изменено (гарантия строгой безопасности исключений)
		return false;
	}

	return true;
}

#include <string>

struct Athlete
{
	std::string name;
	double height; // рост (см)
	double weight; // вес (кг)
};

int main()
{

	std::vector<Athlete> athletes = { { "Иван Иванов", 185.0, 80.5 },
		{ "Петр Петров", 190.0, 85.2 }, { "Алексей Сидоров", 178.0, 90.1 } };

	Athlete tallest;
	if (FindMaxEx(athletes, tallest,
			[](Athlete const& a, Athlete const& b) { return a.height < b.height; }))
	{
		std::cout << "Самый высокий: " << tallest.name << " (" << tallest.height
				  << " см)\n";
	}

	Athlete heaviest;
	if (FindMaxEx(athletes, heaviest,
			[](Athlete const& a, Athlete const& b) { return a.weight < b.weight; }))
	{
		std::cout << "Самый тяжелый: " << heaviest.name << " (" << heaviest.weight
				  << " кг)\n";
	}
	return EXIT_SUCCESS;
}