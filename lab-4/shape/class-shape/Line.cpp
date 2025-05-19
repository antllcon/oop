#include "Line.h"
#include <sstream>

Line::Line(const Point& m_point1, const Point& m_point2, Color outline)
	: BaseShape(outline)
	, m_point1(m_point1)
	, m_point2(m_point2)
{
}

const Point& Line::getA() const
{
	return m_point1;
}

const Point& Line::getB() const
{
	return m_point2;
}

double Line::GetArea() const
{
	return 0;
}

double Line::GetPerimeter() const
{
	return Point::Length(m_point1, m_point2);
}

std::string Line::ToString() const
{
	std::ostringstream oss;
	oss << "== Line ==" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter();
	return oss.str();
}

void Line::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_point1, m_point2, GetOutlineColor());
}