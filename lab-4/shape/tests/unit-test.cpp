#include "../Shape/Circle.h"
#include "../Shape/Line.h"
#include "../Shape/Point.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"
#include <cmath>
#include <gtest/gtest.h>
#include <limits>

namespace
{
const Color TEST_FILL_COLOR = 0xFF00FF00;
const Color TEST_OUTLINE_COLOR = 0xFFFF0000;
const Point TEST_CENTER{ 10.0, 20.0 };
const double TEST_RADIUS = 5.0;
} // namespace

TEST(CircleTest, ConstructorAndGetters)
{
	Circle circle(TEST_CENTER, TEST_RADIUS, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_EQ(circle.GetCenter().x, TEST_CENTER.x);
	EXPECT_EQ(circle.GetCenter().y, TEST_CENTER.y);
	EXPECT_EQ(circle.GetRadius(), TEST_RADIUS);
	EXPECT_EQ(circle.GetFillColor(), TEST_FILL_COLOR);
	EXPECT_EQ(circle.GetOutlineColor(), TEST_OUTLINE_COLOR);
}

TEST(CircleTest, GetArea)
{
	Circle circle(TEST_CENTER, TEST_RADIUS, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	const double expectedArea = M_PI * TEST_RADIUS * TEST_RADIUS;

	EXPECT_DOUBLE_EQ(circle.GetArea(), expectedArea);
}

TEST(CircleTest, GetPerimeter)
{
	Circle circle(TEST_CENTER, TEST_RADIUS, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	const double expectedPerimeter = 2 * M_PI * TEST_RADIUS;

	EXPECT_DOUBLE_EQ(circle.GetPerimeter(), expectedPerimeter);
}

TEST(CircleTest, InvalidRadiusThrowsException)
{
	EXPECT_THROW(
		{ Circle circle(TEST_CENTER, -1.0, TEST_FILL_COLOR, TEST_OUTLINE_COLOR); },
		std::invalid_argument);

	EXPECT_THROW(
		{ Circle circle(TEST_CENTER, 0.0, TEST_FILL_COLOR, TEST_OUTLINE_COLOR); },
		std::invalid_argument);
}

namespace
{
const Point LINE_POINT_A{ 1.0, 2.0 };
const Point LINR_POINT_B{ 4.0, 6.0 };
} // namespace

TEST(LineTest, ConstructorAndGetters)
{
	Line line(LINE_POINT_A, LINR_POINT_B, TEST_OUTLINE_COLOR);

	EXPECT_EQ(line.getA().x, LINE_POINT_A.x);
	EXPECT_EQ(line.getA().y, LINE_POINT_A.y);
	EXPECT_EQ(line.getB().x, LINR_POINT_B.x);
	EXPECT_EQ(line.getB().y, LINR_POINT_B.y);
	EXPECT_EQ(line.GetOutlineColor(), TEST_OUTLINE_COLOR);
}

TEST(LineTest, GetArea)
{
	Line line(LINE_POINT_A, LINR_POINT_B, TEST_OUTLINE_COLOR);
	EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);
}

TEST(LineTest, GetPerimeter)
{
	Line line(LINE_POINT_A, LINR_POINT_B, TEST_OUTLINE_COLOR);
	const double expectedLength = sqrt(pow(LINR_POINT_B.x - LINE_POINT_A.x, 2)
		+ pow(LINR_POINT_B.y - LINE_POINT_A.y, 2));

	EXPECT_DOUBLE_EQ(line.GetPerimeter(), expectedLength);
}

TEST(LineTest, VerticalLine)
{
	Point a{ 1.0, 1.0 };
	Point b{ 1.0, 5.0 };
	Line line(a, b, TEST_OUTLINE_COLOR);

	EXPECT_DOUBLE_EQ(line.GetPerimeter(), 4.0);
}

TEST(LineTest, ZeroLengthLine)
{
	Line line(LINE_POINT_A, LINE_POINT_A, TEST_OUTLINE_COLOR);
	EXPECT_DOUBLE_EQ(line.GetPerimeter(), 0.0);
}

namespace
{
const Point RECTANGLE_TOP_LEFT{ 1.0, 4.0 };
const Point RECTANGLE_BOTTOM_RIGHT{ 5.0, 1.0 };
} // namespace

TEST(RectangleTest, ConstructorAndGetters)
{
	Rectangle rect(RECTANGLE_TOP_LEFT, RECTANGLE_BOTTOM_RIGHT, TEST_FILL_COLOR,
		TEST_OUTLINE_COLOR);

	EXPECT_EQ(rect.GetLeftTop().x, RECTANGLE_TOP_LEFT.x);
	EXPECT_EQ(rect.GetLeftTop().y, RECTANGLE_TOP_LEFT.y);
	EXPECT_EQ(rect.GetRightBottom().x, RECTANGLE_BOTTOM_RIGHT.x);
	EXPECT_EQ(rect.GetRightBottom().y, RECTANGLE_BOTTOM_RIGHT.y);
	EXPECT_EQ(rect.GetFillColor(), TEST_FILL_COLOR);
	EXPECT_EQ(rect.GetOutlineColor(), TEST_OUTLINE_COLOR);
}

TEST(RectangleTest, GetWidth)
{
	Rectangle rect(RECTANGLE_TOP_LEFT, RECTANGLE_BOTTOM_RIGHT, TEST_FILL_COLOR,
		TEST_OUTLINE_COLOR);
	const double expectedWidth
		= std::abs(RECTANGLE_BOTTOM_RIGHT.x - RECTANGLE_TOP_LEFT.x);

	EXPECT_DOUBLE_EQ(rect.GetWidth(), expectedWidth);
}

TEST(RectangleTest, GetHeight)
{
	Rectangle rect(RECTANGLE_TOP_LEFT, RECTANGLE_BOTTOM_RIGHT, TEST_FILL_COLOR,
		TEST_OUTLINE_COLOR);
	const double expectedHeight
		= std::abs(RECTANGLE_BOTTOM_RIGHT.y - RECTANGLE_TOP_LEFT.y);

	EXPECT_DOUBLE_EQ(rect.GetHeight(), expectedHeight);
}

TEST(RectangleTest, GetArea)
{
	Rectangle rect(RECTANGLE_TOP_LEFT, RECTANGLE_BOTTOM_RIGHT, TEST_FILL_COLOR,
		TEST_OUTLINE_COLOR);
	const double expectedArea
		= std::abs((RECTANGLE_BOTTOM_RIGHT.x - RECTANGLE_TOP_LEFT.x)
			* (RECTANGLE_BOTTOM_RIGHT.y - RECTANGLE_TOP_LEFT.y));

	EXPECT_DOUBLE_EQ(rect.GetArea(), expectedArea);
}

TEST(RectangleTest, GetPerimeter)
{
	Rectangle rect(RECTANGLE_TOP_LEFT, RECTANGLE_BOTTOM_RIGHT, TEST_FILL_COLOR,
		TEST_OUTLINE_COLOR);
	const double expectedPerimeter = 2
		* (std::abs(RECTANGLE_BOTTOM_RIGHT.x - RECTANGLE_TOP_LEFT.x)
			+ std::abs(RECTANGLE_BOTTOM_RIGHT.y - RECTANGLE_TOP_LEFT.y));

	EXPECT_DOUBLE_EQ(rect.GetPerimeter(), expectedPerimeter);
}

TEST(RectangleTest, NegativeCoordinates)
{
	const Point topLeft{ -5.0, -3.0 };
	const Point bottomRight{ -1.0, -1.0 };
	Rectangle rect(topLeft, bottomRight, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_DOUBLE_EQ(rect.GetWidth(), 4.0);
	EXPECT_DOUBLE_EQ(rect.GetHeight(), 2.0);
}

TEST(RectangleTest, ZeroWidth)
{
	const Point topLeft{ 2.0, 4.0 };
	const Point bottomRight{ 2.0, 1.0 };
	Rectangle rect(topLeft, bottomRight, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_DOUBLE_EQ(rect.GetWidth(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetHeight(), 3.0);
	EXPECT_DOUBLE_EQ(rect.GetArea(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 6.0);
}

TEST(RectangleTest, ZeroHeight)
{
	const Point topLeft{ 1.0, 3.0 };
	const Point bottomRight{ 5.0, 3.0 };
	Rectangle rect(topLeft, bottomRight, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_DOUBLE_EQ(rect.GetWidth(), 4.0);
	EXPECT_DOUBLE_EQ(rect.GetHeight(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetArea(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 8.0);
}

TEST(RectangleTest, PointRectangle)
{
	const Point point{ 2.0, 3.0 };
	Rectangle rect(point, point, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_DOUBLE_EQ(rect.GetWidth(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetHeight(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetArea(), 0.0);
	EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 0.0);
}

namespace
{
// Правильный треугольник со стороной 2
const Point V1{ 0.0, 0.0 };
const Point V2{ 2.0, 0.0 };
const Point V3{ 1.0, std::sqrt(3.0) };

// Прямоугольный треугольник 3-4-5
const Point RV1{ 0.0, 0.0 };
const Point RV2{ 3.0, 0.0 };
const Point RV3{ 0.0, 4.0 };
} // namespace

TEST(TriangleTest, ConstructorAndGetters)
{
	Triangle triangle(V1, V2, V3, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_EQ(triangle.GetVertex1().x, V1.x);
	EXPECT_EQ(triangle.GetVertex1().y, V1.y);
	EXPECT_EQ(triangle.GetVertex2().x, V2.x);
	EXPECT_EQ(triangle.GetVertex2().y, V2.y);
	EXPECT_EQ(triangle.GetVertex3().x, V3.x);
	EXPECT_EQ(triangle.GetVertex3().y, V3.y);
	EXPECT_EQ(triangle.GetFillColor(), TEST_FILL_COLOR);
	EXPECT_EQ(triangle.GetOutlineColor(), TEST_OUTLINE_COLOR);
}

TEST(TriangleTest, GetPerimeter_Equilateral)
{
	Triangle triangle(V1, V2, V3, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	const double expectedPerimeter = 6.0;

	EXPECT_NEAR(triangle.GetPerimeter(), expectedPerimeter,
		std::numeric_limits<double>::epsilon());
}

TEST(TriangleTest, GetPerimeter_Right)
{
	Triangle triangle(RV1, RV2, RV3, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	const double expectedPerimeter = 12.0;

	EXPECT_NEAR(triangle.GetPerimeter(), expectedPerimeter,
		std::numeric_limits<double>::epsilon());
}

TEST(TriangleTest, GetArea_Right)
{
	Triangle triangle(RV1, RV2, RV3, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	const double expectedArea = 6.0;

	EXPECT_NEAR(
		triangle.GetArea(), expectedArea, std::numeric_limits<double>::epsilon());
}

TEST(CircleTest, MaxRadius)
{
	const double maxRadius = std::numeric_limits<double>::max();
	Circle circle(TEST_CENTER, maxRadius, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_EQ(circle.GetRadius(), maxRadius);
	EXPECT_NO_THROW(circle.GetArea());
	EXPECT_NO_THROW(circle.GetPerimeter());
}

TEST(CircleTest, TooLargeRadiusThrows)
{
	const double tooLarge = std::numeric_limits<double>::max();
	EXPECT_NO_THROW({
		Circle circle(TEST_CENTER, tooLarge, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);
	});
}

TEST(RectangleTest, MaxSize)
{
	const double maxCoord = std::numeric_limits<double>::max() / 4;
	Point topLeft{ -maxCoord, maxCoord };
	Point bottomRight{ maxCoord, -maxCoord };
	Rectangle rect(topLeft, bottomRight, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_NO_THROW(rect.GetArea());
	EXPECT_NO_THROW(rect.GetPerimeter());
}

TEST(TriangleTest, MaxSize)
{
	const double maxCoord = std::numeric_limits<double>::max() / 4;
	Point v1{ 0.0, 0.0 };
	Point v2{ maxCoord, 0.0 };
	Point v3{ 0.0, maxCoord };
	Triangle triangle(v1, v2, v3, TEST_FILL_COLOR, TEST_OUTLINE_COLOR);

	EXPECT_NO_THROW(triangle.GetArea());
	EXPECT_NO_THROW(triangle.GetPerimeter());
}