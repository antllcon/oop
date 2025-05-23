#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "BaseSolidShape.h"
#include "Point.h"

class Rectangle : public BaseSolidShape
{
public:
	explicit Rectangle(
		const Point& topLeft, const Point& bottomRight, Color fill, Color outline);
	~Rectangle() = default;

	const Point& GetLeftTop() const;
	const Point& GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_topLeft;
	Point m_bottomRight;
};

#endif // RECTANGLE_H