#include "ShapeController.h"
#include <algorithm>
#include <sstream>

namespace
{
void AssertIsValidIstream(std::istream& input)
{
	// 1. Проверка общего состояния потока
	if (!input.good())
	{
		throw std::runtime_error("Input stream is in m_point1 bad state");
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
		throw std::runtime_error("Output stream is in m_point1 bad state");
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

void ThrowInvalidTriangleParams()
{
	throw std::runtime_error("Некорректные параметры для triangle");
}

void ThrowInvalidRectangleParams()
{
	throw std::runtime_error("Некорректные параметры для rectangle");
}

void ThrowInvalidCircleParams()
{
	throw std::runtime_error("Некорректные параметры для circle");
}

void ThrowInvalidLineParams()
{
	throw std::runtime_error("Некорректные параметры для line");
}

void ThrowInvalidShapeType()
{
	throw std::runtime_error("Некорректный тип фигуры");
}
} // namespace

ShapeController::ShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	AssertIsValidIstream(m_input);
	AssertIsValidOstream(m_output);
}

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
		CollectShape(keyword, stringStream);
	}
}

void ShapeController::DrawShapes(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

BaseShape* ShapeController::GetMaxAreaShape() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto maxIt = std::max_element(m_shapes.begin(), m_shapes.end(),
		[](const std::unique_ptr<BaseShape>& m_point1,
			const std::unique_ptr<BaseShape>& m_point2) {
			return m_point1->GetArea() < m_point2->GetArea();
		});

	return maxIt->get();
}

BaseShape* ShapeController::GetMinPerimeterShape() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto minIt = std::min_element(m_shapes.begin(), m_shapes.end(),
		[](const std::unique_ptr<BaseShape>& m_point1,
			const std::unique_ptr<BaseShape>& m_point2) {
			return m_point1->GetPerimeter() < m_point2->GetPerimeter();
		});

	return minIt->get();
}

void ShapeController::CollectShape(
	const std::string& keyword, std::istringstream& stringStream)
{
	if (keyword == "triangle")
	{
		CollectTriangle(stringStream);
	}
	else if (keyword == "rectangle")
	{
		CollectRectangle(stringStream);
	}
	else if (keyword == "circle")
	{
		CollectCircle(stringStream);
	}
	else if (keyword == "line")
	{
		CollectLine(stringStream);
	}
	else
	{
		ThrowInvalidShapeType();
	}
}

void ShapeController::CollectTriangle(std::istringstream& stringStream)
{
	double x1, y1, x2, y2, x3, y3;
	std::string solid, outline;
	if (!(stringStream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> solid
			>> outline))
	{
		ThrowInvalidTriangleParams();
		return;
	}

	Point p1{ x1, y1 };
	Point p2{ x2, y2 };
	Point p3{ x3, y3 };

	Color solidColor = std::stoul(solid, nullptr, COLOR_RADIX);
	Color outlineColor = std::stoul(outline, nullptr, COLOR_RADIX);

	auto trian = std::make_unique<Triangle>(p1, p2, p3, solidColor, outlineColor);
	m_shapes.push_back(std::move(trian));
}

void ShapeController::CollectRectangle(std::istringstream& stringStream)
{
	double x1, y1, x2, y2;
	std::string solid, outline;
	if (!(stringStream >> x1 >> y1 >> x2 >> y2 >> std::hex >> solid >> outline))
	{
		ThrowInvalidRectangleParams();
		return;
	}

	Point point1{ x1, y1 };
	Point point2{ x2, y2 };
	Color solidColor = std::stoul(solid, nullptr, COLOR_RADIX);
	Color outlineColor = std::stoul(outline, nullptr, COLOR_RADIX);

	auto rect = std::make_unique<Rectangle>(point1, point2, solidColor, outlineColor);
	m_shapes.push_back(std::move(rect));
}

void ShapeController::CollectCircle(std::istringstream& stringStream)
{
	double x, y, radius;
	std::string solid, outline;
	if (!(stringStream >> x >> y >> radius >> std::hex >> solid >> outline))
	{
		ThrowInvalidCircleParams();
		return;
	}

	Point point{ x, y };
	Color solidColor = std::stoul(solid, nullptr, COLOR_RADIX);
	Color outlineColor = std::stoul(outline, nullptr, COLOR_RADIX);

	auto circle = std::make_unique<Circle>(point, radius, solidColor, outlineColor);
	m_shapes.push_back(std::move(circle));
}

void ShapeController::CollectLine(std::istringstream& stringStream)
{
	double x1, y1, x2, y2;
	std::string outline;
	if (!(stringStream >> x1 >> y1 >> x2 >> y2 >> std::hex >> outline))
	{
		ThrowInvalidLineParams();
		return;
	}

	Point point1{ x1, y1 };
	Point point2{ x2, y2 };
	Color outlineColor = std::stoul(outline, nullptr, COLOR_RADIX);

	auto line = std::make_unique<Line>(point1, point2, outlineColor);
	m_shapes.push_back(std::move(line));
}