#include "Circle.h"
#include <math.h>

Circle::Circle(
	const Point& center, double radius, Color solidColor, Color outlineColor)
	: BaseSolidShape(solidColor, outlineColor)
	, m_center(center)
	, m_radius(radius)
{
	AssertIsValidRadius(radius);
}

const Point& Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

const std::string& Circle::ToString() const
{
	std::string str;
	str = "== Circle ==";
	str += "\nArea: " + std::to_string(GetArea());
	str += "\nPerimeter: " + std::to_string(GetPerimeter());
	// str += "\nFill color: " + std::to_string(GetFillColor());
	// str += "\nOutline color: " + std::to_string(GetOutlineColor());
	return str;
}

void Circle::AssertIsValidRadius(double radius)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}
}
