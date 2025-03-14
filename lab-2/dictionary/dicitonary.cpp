#include "lib.h"
#include <iostream>
#include <map>

using Dictionary = std::map<std::string, std::string>;

int main()
{

	Dictionary dictionary;

	dictionary.insert({ "cat", "кошка" });
	dictionary["cat"] = "кошак";
	dictionary["apple"] = "яблоко";
	dictionary["banana"] = "банан";
	dictionary["orange"] = "апельсин";

	for (const auto& [eng, ru] : dictionary)
	{
		std::cout << eng << " " << ru << '\n';
	}

	std::string userMessage;
	try
	{
		// getDictionary(filename);
		do
		{
			/* code */
		} while ((userMessage = getUserMessage()) != "...");

		//
	}
	catch (const std::exception& errorMessage)
	{
		std::cerr << errorMessage.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}