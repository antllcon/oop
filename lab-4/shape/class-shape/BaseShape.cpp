#include "BaseShape.h"

BaseShape::BaseShape(Color outline)
	: m_outlineColor(outline)
{
	AssertIsValidColor(outline);
}

Color BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void BaseShape::AssertIsValidColor(Color color)
{
	if (color > 0xFFFFFFFF)
	{
		throw std::invalid_argument("Invalid color value");
	}
}