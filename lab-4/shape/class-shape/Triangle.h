#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "BaseSolidShape.h"
#include "Point.h"

class Triangle : public BaseSolidShape
{
public:
	explicit Triangle(const Point& vertex1, const Point& vertex2,
		const Point& vertex3, Color fill, Color outline);
	~Triangle() = default;

	const Point& GetVertex1() const;
	const Point& GetVertex2() const;
	const Point& GetVertex3() const;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

#endif // TRIANGLE_H
