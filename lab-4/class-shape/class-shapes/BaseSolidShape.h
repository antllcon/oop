#ifndef BASESOLIDSHAPE_H
#define BASESOLIDSHAPE_H

#include "BaseShape.h"

class BaseSolidShape : public BaseShape
{
public:
	explicit BaseSolidShape(Color solidColor, Color outlineColor);
	virtual ~BaseSolidShape() = default;
	Color GetFillColor() const;

private:
	Color m_fillColor = 0x000000;
};

#endif // BASESOLIDSHAPE_H