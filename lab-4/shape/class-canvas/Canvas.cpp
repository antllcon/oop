#include "Canvas.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void Canvas::DrawLine(
	const Point& m_point1, const Point& m_point2, Color outline) const
{
	sf::Vertex line[]
		= { sf::Vertex(sf::Vector2f(m_point1.x, m_point1.y), sf::Color(outline)),
			  sf::Vertex(sf::Vector2f(m_point2.x, m_point2.y), sf::Color(outline)) };
	m_window.draw(line, 2, sf::Lines);
}

void Canvas::DrawCircle(const Point& center, double radius, Color outline) const
{
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color(outline));
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius, radius);
	m_window.draw(circle);
}

void Canvas::FillPolygon(const Points& points, Color fill) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setFillColor(sf::Color(fill));
	m_window.draw(polygon);
}

void Canvas::FillCircle(const Point& center, double radius, Color fill) const
{
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color(fill));
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius, radius);
	m_window.draw(circle);
}
