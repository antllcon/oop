#include "Point.h"
#include <cmath>

double Point::Length(const Point& a, const Point& b)
{
	return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}