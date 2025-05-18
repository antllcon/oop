#include "Line.h"

Line::Line(const Point& a, const Point& b, Color outlineColor)
	: BaseShape(outlineColor)
	, a(a)
	, b(b)
{
}

const Point& Line::getA() const
{
	return a;
}

const Point& Line::getB() const
{
	return b;
}

double Line::GetArea() const
{
	return 0;
}

double Line::GetPerimeter() const
{
	return Point::Length(a, b);
}

const std::string& Line::ToString() const
{
	std::string str;
	str = "== Line ==";
	str += "\nArea: " + std::to_string(GetArea());
	str += "\nPerimeter: " + std::to_string(GetPerimeter());
	// str += "\nFill color: " + std::to_string(GetFillColor());
	// str += "\nOutline color: " + std::to_string(GetOutlineColor());
	return str;
}
