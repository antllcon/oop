#include "BaseShape.h"

BaseShape::BaseShape(Color outlineColor)
	: m_outlineColor(outlineColor)
{
	AssertIsValidColor(outlineColor);
}

Color BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void BaseShape::AssertIsValidColor(Color color)
{
	if (color > 0xFFFFFF)
	{
		throw std::invalid_argument("Invalid color value");
	}
}