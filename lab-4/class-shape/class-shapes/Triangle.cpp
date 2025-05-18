#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3,
	Color solidColor = 0x000000, Color outlineColor = 0x000000)
	: BaseSolidShape(solidColor, outlineColor)
	, m_vertex1{ vertex1 }
	, m_vertex2{ vertex2 }
	, m_vertex3{ vertex3 }
{
}

const Point& Triangle::GetVertex1() const
{
	return m_vertex1;
}

const Point& Triangle::GetVertex2() const
{
	return m_vertex2;
}

const Point& Triangle::GetVertex3() const
{
	return m_vertex3;
}

double Triangle::GetArea() const
{
	double side1 = Point::Length(m_vertex1, m_vertex2);
	double side2 = Point::Length(m_vertex2, m_vertex3);
	double side3 = Point::Length(m_vertex3, m_vertex1);

	double halfPerimeter = (side1 + side2 + side3) / 2.0;

	double area = std::sqrt(halfPerimeter * (halfPerimeter - side1)
		* (halfPerimeter - side2) * (halfPerimeter - side3));

	return area;
}

double Triangle::GetPerimeter() const
{
	double side1 = Point::Length(m_vertex1, m_vertex2);
	double side2 = Point::Length(m_vertex2, m_vertex3);
	double side3 = Point::Length(m_vertex3, m_vertex1);

	return side1 + side2 + side3;
}

const std::string& Triangle::ToString() const
{
	std::string str;
	str = "== Triangle ==";
	str += "\nArea: " + std::to_string(GetArea());
	str += "\nPerimeter: " + std::to_string(GetPerimeter());
	// str += "\nFill color: " + std::to_string(GetFillColor());
	// str += "\nOutline color: " + std::to_string(GetOutlineColor());
	return str;
}