#include "ShapeController.h"
#include <sstream>

namespace
{
void AssertIsValidIstream(std::istream& input)
{
	// 1. Проверка общего состояния потока
	if (!input.good())
	{
		throw std::runtime_error("Input stream is in a bad state");
	}

	// 2. Проверка на достижение конца файла (если это критично)
	if (input.eof())
	{
		throw std::runtime_error("Unexpected end of input stream");
	}

	// 3. Проверка флагов ошибок (необязательно, но полезно для отладки)
	if (input.fail())
	{
		throw std::runtime_error("Input operation failed (invalid data?)");
	}

	// 4. Проверка, что поток не "пустой" (например, для строковых потоков)
	if (input.peek() == std::char_traits<char>::eof())
	{
		throw std::runtime_error("Input stream is empty");
	}
}

void AssertIsValidOstream(std::ostream& output)
{
	// 1. Проверка общего состояния потока
	if (!output.good())
	{
		throw std::runtime_error("Output stream is in a bad state");
	}

	// 2. Проверка флагов ошибок (например, диск переполнен)
	if (output.fail())
	{
		throw std::runtime_error("Output operation failed");
	}

	// 3. Для файловых потоков: явная проверка на запись
	if (output.bad())
	{
		throw std::runtime_error("Critical output error (disk full?)");
	}
}
} // namespace

ShapeController::ShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	AssertIsValidIstream(m_input);
	AssertIsValidOstream(m_output);
}

// строка = [ключевое слово] [параметры]
// [параметры] - зависят от ключевого слова
// [параметры] = [число] [число] [число]
// [параметры] = [число] [число]

void ShapeController::ReadShapes()
{
	AssertIsValidIstream(m_input);

	std::string line;
	while (std::getline(m_input, line))
	{
		if (line.empty())
		{
			continue;
		}
		std::istringstream stringStream(line);
		std::string keyword;
		stringStream >> keyword;

		if (!shape)
		{
			m_output << "Unknown shape: " << keyword << std::endl;
			continue;
		}
		shape->ReadParams(ss);
		m_shapes.push_back(std::move(shape));
	}
}