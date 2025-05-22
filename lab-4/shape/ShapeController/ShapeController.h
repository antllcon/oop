#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include "../Shape/BaseShape.h"
#include "../Shape/Circle.h"
#include "../Shape/Line.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"
#include <iostream>
#include <memory>
#include <vector>

class ShapeController
{
public:
	explicit ShapeController(std::istream& input);
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
	std::vector<std::unique_ptr<BaseShape>> m_shapes;
};

#endif // SHAPECONTROLLER_H