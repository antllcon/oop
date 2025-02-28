#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>

namespace Constants
{
inline constexpr int MIN_RADIX = 2;
inline constexpr int MAX_RADIX = 36;
inline constexpr int DECIMAL = 10;
} // namespace Constants

struct Arguments
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

int CharToDigit(char ch)
{
	if ('0' <= ch && ch <= '9')
	{
		return ch - '0';
	}
	if ('A' <= ch && ch <= 'Z')
	{
		return ch - 'A' + 10;
	}
	throw std::runtime_error("Invalid character");
}

bool IsCorrectRadix(int radix)
{
	return Constants::MIN_RADIX <= radix && radix <= Constants::MAX_RADIX;
}

long long ParseStringWithRadix(const std::string& str, int radix)
{
	long long result = 0;
	for (const char& ch : str)
	{
		int digit = CharToDigit(ch);
		if (digit >= radix)
		{
			throw std::runtime_error(
				"The symbol of the number being translated does not match its range");
		}
		if (result > (std::numeric_limits<long long>::max() - digit) / radix)
		{
			throw std::runtime_error("Overflow during calculation");
		}
		result = result * radix + digit;
	}
	return result;
}

int StringToInt(const std::string& str, int radix)
{
	if (!IsCorrectRadix(radix))
	{
		throw std::runtime_error("Invalid <source notation>");
	}

	bool isNegative = false;
	int startIndex = 0;

	if (str[startIndex] == '-')
	{
		isNegative = true;
		++startIndex;
	}

	long long number = ParseStringWithRadix(str.substr(startIndex), radix);

	if (isNegative)
	{
		number = -number;
	}
	if (number < std::numeric_limits<int>::min() || number > std::numeric_limits<int>::max())
	{
		throw std::runtime_error("Overflow - number out of int range");
	}
	return static_cast<int>(number);
}

std::string IntToString(int number, int radix)
{
	if (!IsCorrectRadix(radix))
	{
		throw std::runtime_error("Invalid <destination notation>");
	}

	bool isNegative = number < 0;
	long long absNumber;

	if (isNegative)
	{
		absNumber = static_cast<unsigned long long>(-(static_cast<long long>(number)));
	}
	else
	{
		static_cast<unsigned long long>(number);
	}

	std::string result;
	do
	{
		int remainder = absNumber % radix;
		char digit;
		if (remainder < Constants::DECIMAL)
		{
			digit = ('0' + remainder);
		}
		else
		{
			digit = ('A' + remainder - Constants::DECIMAL);
		}
		result = digit + result;
		absNumber /= radix;
	} while (absNumber > 0);

	if (isNegative)
	{
		result = '-' + result;
	}
	return result;
}

bool ParseArguments(int argc, char* argv[], Arguments& args)
{
	if (argc != 4)
	{
		throw std::runtime_error("Usage: radix.exe <source notation>"
								 " <destination notation> <value>\n");
	}

	args.sourceNotation = StringToInt(argv[1], Constants::DECIMAL);
	args.destinationNotation = StringToInt(argv[2], Constants::DECIMAL);
	args.value = argv[3];
	return true;
}

int main(int argc, char* argv[])
{
	Arguments args;
	try
	{
		ParseArguments(argc, argv, args);
		int number = StringToInt(args.value, args.sourceNotation);
		std::string result = IntToString(number, args.destinationNotation);
		std::cout << result << '\n';
	}
	catch (const std::exception& error_message)
	{
		std::cerr << "Error: " << error_message.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}