#include "FindMaxEx.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Sportsman
{
	std::string name;
	double height; // рост (см)
	double weight; // вес (кг)
};

void Print(const Sportsman& sportsman)
{
	const auto& [name, height, weight] = sportsman;

	std::cout << "Параметры " << name << ':' << std::endl;
	std::cout << "Рост: " << height << std::endl;
	std::cout << "Вес: " << weight << std::endl
			  << std::endl;
}

int main()
{
	try
	{

		std::vector<Sportsman> hokeyTeam = {
			{ "Овечкин", 193, 92 },
			{ "Дюбуа", 180, 80 },
		};

		std::cout << "Самый высокий" << std::endl;
		std::cout << "=============" << std::endl;
		Sportsman maxHeightSportsman;

		FindMaxEx(hokeyTeam, maxHeightSportsman, [](const Sportsman& a, const Sportsman& b) {
			return a.height < b.height;
		});

		Print(maxHeightSportsman);

		std::cout << "Самый тяжелый" << std::endl;
		std::cout << "=============" << std::endl;
		Sportsman maxWeightSportsman;

		FindMaxEx(hokeyTeam, maxWeightSportsman, [](const Sportsman& a, const Sportsman& b) {
			return a.weight < b.weight;
		});

		Print(maxWeightSportsman);
	}
	catch (const std::exception& exceptionMessage)
	{
		std::cerr << "Error: " << exceptionMessage.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}