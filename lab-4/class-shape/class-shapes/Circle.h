#ifndef CIRCLE_H
#define CIRCLE_H

#include "BaseSolidShape.h"
#include "Point.h"

class Circle : public BaseSolidShape
{
public:
	explicit Circle(
		const Point& center, double radius, Color solidColor, Color outlineColor);
	~Circle() = default;

	const Point& GetCenter() const;
	double GetRadius() const;

	double GetArea() const override;
	double GetPerimeter() const override;
	const std::string& ToString() const override;

protected:
	static void AssertIsValidRadius(double radius);

private:
	Point m_center;
	double m_radius = 0;
};

#endif // CIRCLE_H