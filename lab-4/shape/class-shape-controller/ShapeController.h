#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include "../class-shape/BaseShape.h"
#include "../class-shape/Circle.h"
#include "../class-shape/Line.h"
#include "../class-shape/Rectangle.h"
#include "../class-shape/Triangle.h"
#include <iostream>
#include <memory>
#include <vector>

class ShapeController
{
public:
	ShapeController(std::istream& input, std::ostream& output);
	~ShapeController() = default;

	void ReadShapes();
	void DrawShapes(ICanvas& canvas) const;
	BaseShape* GetMaxAreaShape() const;
	BaseShape* GetMinPerimeterShape() const;

private:
	void CollectShape(const std::string& keyword, std::istringstream& stringStream);
	void CollectTriangle(std::istringstream& stringStream);
	void CollectRectangle(std::istringstream& stringStream);
	void CollectCircle(std::istringstream& stringStream);
	void CollectLine(std::istringstream& stringStream);

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::unique_ptr<BaseShape>> m_shapes;
};

#endif // SHAPECONTROLLER_H