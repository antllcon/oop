#include "BaseSolidShape.h"

BaseSolidShape::BaseSolidShape(Color fill, Color outline)
	: BaseShape(outline)
	, m_fillColor(fill)
{
	BaseShape::AssertIsValidColor(fill);
}

Color BaseSolidShape::GetFillColor() const
{
	return m_fillColor;
}