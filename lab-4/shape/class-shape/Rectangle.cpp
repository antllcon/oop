#include "Rectangle.h"
#include <sstream>

Rectangle::Rectangle(
	const Point& topLeft, const Point& bottomRight, Color fill, Color outline)
	: BaseSolidShape(fill, outline)
	, m_topLeft(topLeft)
	, m_bottomRight(bottomRight)
{
}

const Point& Rectangle::GetLeftTop() const
{
	return m_topLeft;
}

const Point& Rectangle::GetRightBottom() const
{
	return m_bottomRight;
}

double Rectangle::GetWidth() const
{
	return std::abs(m_bottomRight.x - m_topLeft.x);
}

double Rectangle::GetHeight() const
{
	return std::abs(m_bottomRight.y - m_topLeft.y);
}

double Rectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double Rectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string Rectangle::ToString() const
{
	std::ostringstream oss;
	oss << "== Rectangle ==" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter();
	return oss.str();
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Points points = {
		m_topLeft,						  // верхний левый угол
		{ m_bottomRight.x, m_topLeft.y }, // верхний правый угол
		m_bottomRight,					  // нижний правый угол
		{ m_topLeft.x, m_bottomRight.y }  // нижний левый угол
	};
	canvas.FillPolygon(points, GetFillColor());
}