#include "Vector.h"
#include <iostream>

template <typename T>
void PrintVector(const T& vector)
{
	std::cout << "Содержимое вектора:" << std::endl;
	for (size_t i = 0; i < vector.GetSize(); ++i)
	{
		std::cout << vector[i] << std::endl;
	}
	std::cout << "------------------" << std::endl;
}

int main()
{
	std::cout << "[ vector ]" << std::endl;
	// std::vector<std::string> test;

	std::string dog = "Sharik";
	std::string cat = "Murka";

	Vector<std::string> homePets;

	homePets.PushBack(dog);
	homePets.PushBack(cat);
	PrintVector(homePets);

	return EXIT_SUCCESS;
}
