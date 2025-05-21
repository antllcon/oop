#include "BaseShape.h"

BaseShape::BaseShape(Color outline)
	: m_outlineColor(outline)
{
}

Color BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}