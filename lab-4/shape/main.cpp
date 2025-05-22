#include "Canvas/Canvas.h"
#include "ShapeController/ShapeController.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

namespace
{
void AssertIsValidIstream(std::istream& input)
{
	if (!input)
	{
		throw std::runtime_error("Не удалось открыть файл для чтения");
	}
}

void AssertIsValidOstream(std::ostream& output)
{
	if (!output)
	{
		throw std::runtime_error("Не удалось открыть файл для записи");
	}
}
} // namespace

const std::string& ParseArgs(int argc, const std::string& argv)
{
	if (argc != 2)
	{
		throw std::invalid_argument("Usage: program <input_file>");
	}

	return argv;
}

int main(int argc, char* argv[])
{
	try
	{
		std::string file = ParseArgs(argc, argv[1]);
		std::ifstream inputFile("../../test/" + file);
		AssertIsValidIstream(inputFile);

		ShapeController shapeController(inputFile);

		shapeController.ReadShapes();
		std::cout << "Shapes read successfully" << std::endl;

		auto maxAreaShape = shapeController.GetMaxAreaShape();
		auto minPerimeterShape = shapeController.GetMinPerimeterShape();

		std::cout << "Max area shape: " << maxAreaShape->ToString() << std::endl;
		std::cout << "Min perimeter shape: " << minPerimeterShape->ToString()
				  << std::endl;

		sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shapes");
		Canvas canvas(window);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			window.clear();
			shapeController.DrawShapes(canvas);
			window.display();
		}
	}
	catch (const std::exception& error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
	}

	return EXIT_SUCCESS;
}