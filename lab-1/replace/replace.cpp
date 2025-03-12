#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

enum class AppMode
{
	CommandLine,
	Stdin,
	Help,
	Invalid
};

AppMode DefineMode(int argc, char* argv[])
{
	if (argc == 5)
	{
		return AppMode::CommandLine;
	}
	else if (argc == 1)
	{
		return AppMode::Stdin;
	}
	else if (argc == 2
		&& (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
	{
		return AppMode::Help;
	}
	else
	{
		return AppMode::Invalid;
	}
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty() || searchString == replacementString)
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		std::size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos);
			break;
		}
		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

void CopyFileWithReplacement(const std::string& inputFileName,
	const std::string& outputFileName, const std::string& search,
	const std::string& replace)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open input file: " + inputFileName);
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error(
			"Failed to open // create output file: " + outputFileName);
	}

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);

	inputFile.close();
	outputFile.close();
}

void ProcessStreamWithReplacement()
{
	std::string search;
	if (!std::getline(std::cin, search) || search.empty())
	{
		std::cerr << "ERROR";
		exit(EXIT_SUCCESS);
	}

	std::string replace;
	if (!std::getline(std::cin, replace))
	{
		std::cerr << "ERROR";
		exit(EXIT_SUCCESS);
	}

	std::string line;
	bool hasInput = false;
	while (std::getline(std::cin, line))
	{
		hasInput = true;
		std::cout << ReplaceString(line, search, replace) << '\n';
	}

	if (!hasInput)
	{
		std::cerr << "ERROR";
		exit(EXIT_SUCCESS);
	}
}

void PrintHelp()
{
	std::cout
		<< "Usage: replace.exe <inputFile> <outputFile> <searchString> "
		   "<replacementString>\n\n"

		   "The program replaces all occurrences of<search String>"
		   "with<replacement String> in the text file<input File>"
		   "and saves the result to<outputFile>.\n\n"

		   "Operating modes :\n"
		   "1. With the parameters : pass the file names, the desired string "
		   "and the string to replace.\n"
		   "2. Without parameters : enter the desired string, the string to "
		   "replace and the text via stdin.\n\n"

		   "Mistakes :\n"
		   " - If the files do not open, the program outputs "
		   "ERROR"
		   "\n"
		   " - If the input via stdin is interrupted, the program outputs "
		   "ERROR"
		   " and ends.\n";
}

void PrintInvalidArgumentCount()
{
	std::cout << "Invalid argument count\n"
			  << "Usage: replace.exe <inputFile> <outputFile> <searchString> "
				 "<replacementString>\n";
}

int main(int argc, char* argv[])
{
	AppMode mode = DefineMode(argc, argv);

	try
	{
		switch (mode)
		{
		case AppMode::CommandLine:
			CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
			break;

		case AppMode::Stdin:
			ProcessStreamWithReplacement();
			break;

		case AppMode::Help:
			PrintHelp();
			break;

		default:
			PrintInvalidArgumentCount();
			return EXIT_FAILURE;
		}
	}
	catch (const std::exception& exсeption_massage)
	{
		std::cerr << "ERROR\n";

		if (mode == AppMode::CommandLine)
		{
			return EXIT_FAILURE;
		}
		else if (mode == AppMode::Stdin)
		{
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}