#ifndef LINE_H
#define LINE_H

#include "BaseShape.h"
#include "Point.h"

class Line : public BaseShape
{
public:
	Line(const Point& a, const Point& m_point2, Color outline);
	~Line() = default;

	const Point& getA() const;
	const Point& getB() const;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_point1;
	Point m_point2;
};

#endif // LINE_H