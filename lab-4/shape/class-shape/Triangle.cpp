#include "Triangle.h"
#include <cmath>
#include <sstream>

Triangle::Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3,
	Color solid, Color outline)
	: BaseSolidShape(solid, outline)
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

std::string Triangle::ToString() const
{
	std::ostringstream oss;
	oss << "== Triangle ==" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter();
	return oss.str();
}

void Triangle::Draw(ICanvas& canvas) const
{
	Points points = { m_vertex1, m_vertex2, m_vertex3 };
	canvas.FillPolygon(points, GetFillColor());
	canvas.DrawLine(m_vertex1, m_vertex2, GetOutlineColor());
	canvas.DrawLine(m_vertex2, m_vertex3, GetOutlineColor());
	canvas.DrawLine(m_vertex3, m_vertex1, GetOutlineColor());
}