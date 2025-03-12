#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace constants
{
inline constexpr int MIN_RADIX = 2;
inline constexpr int MAX_RADIX = 36;
inline constexpr int DECIMAL = 10;
} // namespace constants

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
	return constants::MIN_RADIX <= radix && radix <= constants::MAX_RADIX;
}

int ParseStringWithRadix(const std::string& str, int radix)
{
	if (str.empty())
	{
		throw std::runtime_error("Empty string");
	}

	bool isNegative = false;
	size_t startIndex = 0;

	if (str[startIndex] == '-')
	{
		isNegative = true;
		++startIndex;
	}

	unsigned int result = 0;
	for (size_t i = startIndex; i < str.size(); ++i)
	{
		int digit = CharToDigit(str[i]);
		if (digit >= radix)
		{
			throw std::runtime_error(
				"The symbol of the number being translated does not match its range");
		}

		if (result > (std::numeric_limits<unsigned int>::max() - digit) / radix)
		{
			throw std::runtime_error("Overflow during calculation");
		}

		result = result * radix + digit;
	}

	if (isNegative)
	{
		if (result > static_cast<unsigned int>(std::numeric_limits<int>::max()) + 1)
		{
			throw std::runtime_error("Overflow - number out of int range");
		}
		return -static_cast<int>(result);
	}

	if (result > static_cast<unsigned int>(std::numeric_limits<int>::max()))
	{
		throw std::runtime_error("Overflow - number out of int range");
	}

	return static_cast<int>(result);
}

int StringToInt(const std::string& str, int radix) { return ParseStringWithRadix(str, radix); }

void CheckCorrectRadix(int destinationRadix, int sourceRadix)
{
	if (!IsCorrectRadix(destinationRadix))
	{
		throw std::runtime_error("Invalid <destination notation>");
	}
	if (!IsCorrectRadix(sourceRadix))
	{
		throw std::runtime_error("Invalid <source notation>");
	}
}

std::string IntToString(int number, int radix)
{
	bool isNegative = number < 0;
	unsigned int absNumber;

	if (isNegative)
	{
		if (number == std::numeric_limits<int>::min())
		{
			absNumber = static_cast<unsigned int>(std::numeric_limits<int>::max()) + 1;
		}
		else
		{
			absNumber = static_cast<unsigned int>(-number);
		}
	}
	else
	{
		absNumber = static_cast<unsigned int>(number);
	}

	std::string result;
	do
	{
		int remainder = absNumber % radix;
		char digit;
		if (remainder < constants::DECIMAL)
		{
			digit = ('0' + remainder);
		}
		else
		{
			digit = ('A' + remainder - constants::DECIMAL);
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

	args.sourceNotation = StringToInt(argv[1], constants::DECIMAL);
	args.destinationNotation = StringToInt(argv[2], constants::DECIMAL);
	args.value = argv[3];
	return true;
}

int main(int argc, char* argv[])
{
	Arguments args;
	try
	{
		ParseArguments(argc, argv, args);
		CheckCorrectRadix(args.destinationNotation, args.sourceNotation);
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