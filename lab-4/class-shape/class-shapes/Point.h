#ifndef POINT_H
#define POINT_H

struct Point
{
	double x = 0;
	double y = 0;

	static double Length(const Point& a, const Point& b);
};

#endif // POINT_H