#include <fstream>
#include <iostream>

namespace constants
{
inline const std::string CRYPT = "crypt";
inline const std::string DECRYPT = "decrypt";
inline constexpr int DECIMAL = 10;
inline constexpr int MIN_KEY = 0;
inline constexpr int MAX_KEY = 255;
} // namespace constants

namespace bytes
{
inline constexpr unsigned char FIRST = 0b00000001;
inline constexpr unsigned char SECOND = 0b00000010;
inline constexpr unsigned char THIRD = 0b00000100;
inline constexpr unsigned char FOURTH = 0b00001000;
inline constexpr unsigned char FIFTH = 0b00010000;
inline constexpr unsigned char SIXTH = 0b00100000;
inline constexpr unsigned char SEVENTH = 0b01000000;
inline constexpr unsigned char EIGHTH = 0b10000000;
} // namespace bytes

enum class ModeType
{
	Crypt,
	Decript
};

struct Arguments
{
	ModeType mode;
	std::ifstream inputFile;
	std::ofstream outputFile;
	unsigned char key;
};

void AssertNumberArguments(int argc)
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			"Программа ожидает: start crypt <input file> <output file> <key> ");
	}
}

void AssertDecimal(const std::string& numberString)
{
	for (const auto& ch : numberString)
	{
		if (!std::isdigit(ch))
		{
			throw std::invalid_argument("Не десятичное число!");
		}
	}
}

void AssertKeyValue(int keyValue, const std::string& keyString, size_t pos)
{
	if (pos != keyString.size() || keyValue < constants::MIN_KEY || keyValue > constants::MAX_KEY)
	{
		throw std::out_of_range("Ключ должен быть от 0 до 255!");
	}
}

void OpenFile(const std::string& filename, std::ifstream& file)
{
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Не удалось открыть входной файл: " + filename + '!');
	}
}

void OpenFile(const std::string& filename, std::ofstream& file)
{
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Не удалось создать выходной файл: " + filename + '!');
	}
}

ModeType GetMode(const std::string& modeString)
{
	if (modeString == constants::CRYPT)
	{
		return ModeType::Crypt;
	}
	if (modeString == constants::DECRYPT)
	{
		return ModeType::Decript;
	}
	throw std::invalid_argument("Некорректный режим!");
}

unsigned char GetKey(const std::string& keyString)
{
	AssertDecimal(keyString);
	size_t pos = 0;
	int keyValue = std::stoi(keyString, &pos, constants::DECIMAL);
	AssertKeyValue(keyValue, keyString, pos);
	return static_cast<unsigned char>(keyValue);
}

Arguments ParseArgs(int argc, char* argv[])
{
	Arguments arguments;

	AssertNumberArguments(argc);
	arguments.mode = GetMode(argv[1]);
	arguments.key = GetKey(argv[4]);
	OpenFile(argv[2], arguments.inputFile);
	OpenFile(argv[3], arguments.outputFile);
	return arguments;
}

char GetCryptedChar(char ch, unsigned char key)
{
	char outChar = 0;
	char cryptedByte = ch ^ key;
	outChar |= (cryptedByte & bytes::EIGHTH) >> 2;
	outChar |= (cryptedByte & bytes::SEVENTH) >> 5;
	outChar |= (cryptedByte & bytes::SIXTH) >> 5;
	outChar |= (cryptedByte & bytes::FIFTH) << 3;
	outChar |= (cryptedByte & bytes::FOURTH) << 3;
	outChar |= (cryptedByte & bytes::THIRD) << 2;
	outChar |= (cryptedByte & bytes::SECOND) << 2;
	outChar |= (cryptedByte & bytes::FIRST) << 2;
	return outChar;
}

char GetDecryptedChar(char ch, unsigned char key)
{
	char decryptedChar = 0;
	decryptedChar |= (ch & bytes::EIGHTH) >> 3;
	decryptedChar |= (ch & bytes::SEVENTH) >> 3;
	decryptedChar |= (ch & bytes::SIXTH) << 2;
	decryptedChar |= (ch & bytes::FIFTH) >> 2;
	decryptedChar |= (ch & bytes::FOURTH) >> 2;
	decryptedChar |= (ch & bytes::THIRD) >> 2;
	decryptedChar |= (ch & bytes::SECOND) << 5;
	decryptedChar |= (ch & bytes::FIRST) << 5;
	return decryptedChar ^ key;
}

void Crypt(std::istream& input, std::ostream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		output << GetCryptedChar(byte, key);
	}
}

void Decrypt(std::istream& input, std::ostream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		output << GetDecryptedChar(byte, key);
	}
}

int main(int argc, char* argv[])
{
	Arguments arguments;

	try
	{
		ParseArgs(argc, argv);
		if (arguments.mode == ModeType::Crypt)
		{
			Crypt(arguments.inputFile, arguments.outputFile, arguments.key);
		}
		if (arguments.mode == ModeType::Decript)
		{
			Decrypt(arguments.inputFile, arguments.outputFile, arguments.key);
		}
	}
	catch (const std::exception& errorMesssage)
	{
		std::cerr << errorMesssage.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}