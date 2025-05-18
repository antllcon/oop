#ifndef BASESHAPE_H
#define BASESHAPE_H

#include <cstdint>
#include <iostream>

using Color = uint32_t;

class BaseShape
{
public:
	explicit BaseShape(Color outlineColor);
	virtual ~BaseShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual const std::string& ToString() const = 0;
	Color GetOutlineColor() const;

protected:
	static void AssertIsValidColor(Color color);

private:
	Color m_outlineColor = 0x000000;
};

#endif // BASESHAPE_H
