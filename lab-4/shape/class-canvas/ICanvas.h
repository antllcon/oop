#ifndef ICANVAS_H
#define ICANVAS_H

#include "../Types.h"
#include "../class-shape/BaseShape.h"
#include "../class-shape/Point.h"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(
		const Point& m_point1, const Point& m_point2, Color outline) const
		= 0;
	virtual void DrawCircle(const Point& center, double radius, Color outline) const
		= 0;
	virtual void FillPolygon(const Points& points, Color fill) const = 0;
	virtual void FillCircle(const Point& center, double radius, Color fill) const = 0;
};

#endif // ICANVAS_H