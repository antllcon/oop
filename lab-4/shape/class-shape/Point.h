#ifndef POINT_H
#define POINT_H

#include <vector>

struct Point
{
	double x = 0;
	double y = 0;

	static double Length(const Point& a, const Point& b);
};

using Points = std::vector<Point>;

#endif // POINT_H