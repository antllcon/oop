#include "Rectangle.h"

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight, Color solidColor,
	Color outlineColor)
	: BaseSolidShape(solidColor, outlineColor)
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

const std::string& Rectangle::ToString() const
{
	std::string str;
	str = "== Rectangle ==";
	str += "\nArea: " + std::to_string(GetArea());
	str += "\nPerimeter: " + std::to_string(GetPerimeter());
	// str += "\nFill color: " + std::to_string(GetFillColor());
	// str += "\nOutline color: " + std::to_string(GetOutlineColor());
	return str;
}
