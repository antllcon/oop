#ifndef BASESHAPE_H
#define BASESHAPE_H

#include "../Types.h"
#include "ICanvasDrawable.h"
#include <cstdint>
#include <iostream>

class BaseShape : public ICanvasDrawable
{
public:
	explicit BaseShape(Color outline);
	virtual ~BaseShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	Color GetOutlineColor() const;

protected:
	static void AssertIsValidColor(Color color);

private:
	Color m_outlineColor;
};

#endif // BASESHAPE_H