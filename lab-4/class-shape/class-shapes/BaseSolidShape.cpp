#include "BaseSolidShape.h"

BaseSolidShape::BaseSolidShape(Color solidColor, Color outlineColor)
	: BaseShape(outlineColor)
	, m_fillColor(solidColor)
{
	BaseShape::AssertIsValidColor(solidColor);
}

Color BaseSolidShape::GetFillColor() const
{
	return m_fillColor;
}