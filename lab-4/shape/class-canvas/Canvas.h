#ifndef CANVAS_H
#define CANVAS_H

#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
	explicit Canvas(sf::RenderWindow& window);
	void DrawLine(
		const Point& m_point1, const Point& m_point2, Color outline) const override;
	void DrawCircle(const Point& center, double radius, Color outline) const override;
	void FillPolygon(const Points& points, Color fill) const override;
	void FillCircle(const Point& center, double radius, Color fill) const override;

private:
	sf::RenderWindow& m_window;
};

#endif // CANVAS_H
