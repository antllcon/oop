#include "Vector.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Coords
{
	double x = 0;
	double y = 0;
	double z = 0;
	int* m_memoryBlock;

	Coords()
	{
		m_memoryBlock = new int[5];
	}

	Coords(double transformation)
		: x(transformation)
		, y(transformation)
		, z(transformation)
	{
		m_memoryBlock = new int[5];
	}

	Coords(double x, double y, double z)
		: x(x)
		, y(y)
		, z(z)
	{
		m_memoryBlock = new int[5];
	}

	Coords(const Coords& other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
		std::cout << "copy" << std::endl;
	}

	Coords(Coords&& other) noexcept
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{

		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		std::cout << "move" << std::endl;
	}

	~Coords()
	{
		delete[] m_memoryBlock;
		std::cout << "destroy" << std::endl;
	}

	Coords& operator=(const Coords& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			std::cout << "copy assign" << std::endl;
		}
		return *this;
	}

	Coords& operator=(Coords&& other) noexcept
	{

		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;

		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			std::cout << "move assign" << std::endl;
		}
		return *this;
	}
};

template <typename T>
void PrintVector(const T& vector)
{
	std::cout << "Содержимое вектора:" << std::endl;
	for (size_t i = 0; i < vector.GetSize(); ++i)
	{
		std::cout << vector[i] << std::endl;
	}
	std::cout << "---------" << std::endl;
}

template <>
void PrintVector(const Vector<Coords>& vector)
{
	std::cout << "Содержимое Coords:" << std::endl;
	for (size_t i = 0; i < vector.GetSize(); ++i)
	{
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
	}
	std::cout << "---------" << std::endl;
}

int main()
{
	std::cout << "[ vector ]" << std::endl;

	// std::string dog = "Sharik";
	// std::string cat = "Murka";

	// Vector<std::string> homePets;

	// homePets.PushBack(dog);
	// homePets.PushBack(cat);
	// PrintVector(homePets);

	// std::cout << "Размер: " << homePets.GetSize() << std::endl;
	{

		Vector<Coords> coordsVector;
		coordsVector.PushBack(Coords(4.0, 2.0, 3.0));
		coordsVector.PushBack(Coords());
		coordsVector.PushBack(Coords(1));

		PrintVector(coordsVector);
		coordsVector.Clear();

		PrintVector(coordsVector);
	}
	return EXIT_SUCCESS;
}