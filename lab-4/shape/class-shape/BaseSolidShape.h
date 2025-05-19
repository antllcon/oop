#ifndef BASESOLIDSHAPE_H
#define BASESOLIDSHAPE_H

#include "BaseShape.h"

class BaseSolidShape : public BaseShape
{
public:
	explicit BaseSolidShape(Color fill, Color outline);
	virtual ~BaseSolidShape() = default;
	Color GetFillColor() const;

private:
	Color m_fillColor;
};

#endif // BASESOLIDSHAPE_H