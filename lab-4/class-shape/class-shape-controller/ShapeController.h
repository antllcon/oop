#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include "../class-shapes/BaseShape.h"
#include "../class-shapes/Circle.h"
#include "../class-shapes/Line.h"
#include "../class-shapes/Rectangle.h"
#include "../class-shapes/Triangle.h"
#include <iostream>
#include <memory>
#include <vector>

class ShapeController
{
public:
	ShapeController(std::istream& input, std::ostream& output);
	~ShapeController() = default;

	void ReadShapes();

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::unique_ptr<BaseShape>> m_shapes;
};

#endif // SHAPECONTROLLER_H