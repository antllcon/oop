#include <iostream>

const std::string& ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Usage: program <filename>");
	}
	return argv[1];
}

int main(int argc, char* argv[])
{
	try
	{
		auto fileName = ParseArgs(argc, argv);
		// canvas = new Canvas(800, 600, fileName);
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}

	return EXIT_SUCCESS;
}