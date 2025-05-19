#include "class-canvas/Canvas.h"
#include "class-shape-controller/ShapeController.h"
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

struct Args
{
	std::string input = "../../test/";
	std::string output = "../../test/";
};

Args ParseArgs(int argc, char* argv[])
{
	Args args;

	if (argc != 3)
	{
		throw std::invalid_argument("Usage: program <input_file> <output_file>");
	}

	args.input += argv[1];
	args.output += argv[2];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		std::ifstream inputFile(args.input);
		AssertIsValidIstream(inputFile);
		std::ofstream outputFile(args.output);
		AssertIsValidOstream(outputFile);

		ShapeController shapeController(inputFile, outputFile);

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