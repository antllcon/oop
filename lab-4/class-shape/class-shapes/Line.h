#ifndef LINE_H
#define LINE_H

#include "BaseShape.h"
#include "Point.h"

class Line : public BaseShape
{
public:
	Line(const Point& a, const Point& b, Color outlineColor);
	~Line() = default;

	const Point& getA() const;
	const Point& getB() const;

	double GetArea() const override;
	double GetPerimeter() const override;
	const std::string& ToString() const override;

private:
	Point a;
	Point b;
};

#endif // LINE_H