#include "Circle.h"
#include <math.h>
#include <sstream>

Circle::Circle(const Point& center, double radius, Color fill, Color outline)
	: BaseSolidShape(fill, outline)
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

std::string Circle::ToString() const
{
	std::ostringstream oss;
	oss << "== Circle ==" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter();
	return oss.str();
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, GetFillColor());
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
}

void Circle::AssertIsValidRadius(double radius)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}
}