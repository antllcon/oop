#include "Vector.hpp"
#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

struct Point
{
	int x = 0;
	int y = 0;
	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

// Структура с управлением памятью (Coords)
struct Coords
{
	double x = 0;
	double y = 0;
	double z = 0;
	int* m_memoryBlock;

	Coords() { m_memoryBlock = new int[5]; }
	Coords(double transformation)
		: x(transformation)
		, y(transformation)
		, z(transformation)
	{
		m_memoryBlock = new int[5];
	}
	Coords(double x, double y, double z)
		: x(x)
		, y(y)
		, z(z)
	{
		m_memoryBlock = new int[5];
	}
	Coords(const Coords& other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
		m_memoryBlock = new int[5];
		std::cout << "copy" << std::endl;
	}
	Coords(Coords&& other) noexcept
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		std::cout << "move" << std::endl;
	}
	~Coords()
	{
		delete[] m_memoryBlock;
		std::cout << "destroy" << std::endl;
	}
	Coords& operator=(const Coords& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			std::cout << "copy assign" << std::endl;
		}
		return *this;
	}
	Coords& operator=(Coords&& other) noexcept
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			std::cout << "move assign" << std::endl;
		}
		return *this;
	}
	bool operator==(const Coords& other) const { return x == other.x && y == other.y && z == other.z; }
};

// 1. int, float
TEST(VectorTest, IntBasic)
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	EXPECT_EQ(v.GetSize(), 2);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, FloatBasic)
{
	Vector<float> v;
	v.PushBack(1.5f);
	v.PushBack(2.5f);
	EXPECT_FLOAT_EQ(v[0], 1.5f);
	EXPECT_FLOAT_EQ(v[1], 2.5f);
}

// 2. string, char
TEST(VectorTest, StringBasic)
{
	Vector<std::string> v;
	v.PushBack("abc");
	v.PushBack("def");
	EXPECT_EQ(v[0], "abc");
	EXPECT_EQ(v[1], "def");
}

TEST(VectorTest, CharBasic)
{
	Vector<char> v;
	v.PushBack('a');
	v.PushBack('b');
	EXPECT_EQ(v[0], 'a');
	EXPECT_EQ(v[1], 'b');
}

// 3. Структуры
TEST(VectorTest, StructBasic)
{
	Vector<Point> v;
	v.PushBack({ 1, 2 });
	v.PushBack({ 3, 4 });
	EXPECT_EQ(v[0], (Point{ 1, 2 }));
	EXPECT_EQ(v[1], (Point{ 3, 4 }));
}

// 4. Структуры с памятью
TEST(VectorTest, CoordsStructBasic)
{
	Vector<Coords> v;
	v.PushBack(Coords(1.0, 2.0, 3.0));
	v.PushBack(Coords(4.0, 5.0, 6.0));
	EXPECT_EQ(v[0], (Coords{ 1.0, 2.0, 3.0 }));
	EXPECT_EQ(v[1], (Coords{ 4.0, 5.0, 6.0 }));
}

TEST(VectorTest, NestedVectorOfCoords)
{
	Vector<Vector<Coords>> vv;
	vv.EmplaceBack();
	vv[0].PushBack(Coords(1, 2, 3));
	vv[0].PushBack(Coords(4, 5, 6));
	EXPECT_EQ(vv[0][0], (Coords{ 1, 2, 3 }));
	EXPECT_EQ(vv[0][1], (Coords{ 4, 5, 6 }));
}

// 5. STL совместимость
TEST(VectorTest, RangeBasedFor)
{
	Vector<int> v;
	for (int i = 0; i < 5; ++i)
		v.PushBack(i);
	int sum = 0;
	for (int x : v)
		sum += x;
	EXPECT_EQ(sum, 10);
}

TEST(VectorTest, StdFind)
{
	Vector<int> v;
	for (int i = 0; i < 5; ++i)
		v.PushBack(i);
	auto it = std::find(v.begin(), v.end(), 3);
	EXPECT_NE(it, v.end());
	EXPECT_EQ(*it, 3);
}

TEST(VectorTest, StdSort)
{
	Vector<int> v;
	v.PushBack(3);
	v.PushBack(1);
	v.PushBack(2);
	std::sort(v.begin(), v.end());
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

// 6. Операторы и исключения
TEST(VectorTest, CopyMoveAssign)
{
	Vector<std::string> v1;
	v1.PushBack("a");
	Vector<std::string> v2 = v1; // copy
	EXPECT_EQ(v2[0], "a");
	Vector<std::string> v3;
	v3 = v1; // copy assign
	EXPECT_EQ(v3[0], "a");
	Vector<std::string> v4 = std::move(v1); // move
	EXPECT_EQ(v4[0], "a");
	Vector<std::string> v5;
	v5 = std::move(v2); // move assign
	EXPECT_EQ(v5[0], "a");
}

TEST(VectorTest, IndexOperatorOutOfRange)
{
	Vector<int> v;
	v.PushBack(1);
	EXPECT_THROW(v[1], std::out_of_range);
}

TEST(VectorTest, ResizeAndClear)
{
	Vector<int> v;
	v.Resize(3);
	EXPECT_EQ(v.GetSize(), 3);
	v.Clear();
	EXPECT_EQ(v.GetSize(), 0);
}

// 7. Граничные случаи
TEST(VectorTest, EmptyVector)
{
	Vector<int> v;
	EXPECT_EQ(v.GetSize(), 0);
	EXPECT_EQ(v.begin(), v.end());
}

TEST(VectorTest, PopBack)
{
	Vector<int> v;
	v.PushBack(1);
	v.PopBack();
	EXPECT_EQ(v.GetSize(), 0);
}

TEST(VectorTest, PopBackManyTimes)
{
	Vector<int> v;
	for (int i = 0; i < 3; ++i)
		v.PushBack(i);
	for (int i = 0; i < 10; ++i)
	{
		v.PopBack();
		EXPECT_GE(v.GetSize(), 0u);
	}
	EXPECT_EQ(v.GetSize(), 0u);
}

TEST(VectorTest, EmplaceBack)
{
	Vector<std::pair<int, std::string>> v;
	v.EmplaceBack(1, "abc");
	EXPECT_EQ(v[0].first, 1);
	EXPECT_EQ(v[0].second, "abc");
}

// 8. Копирование и перемещение больших векторов
TEST(VectorTest, CopyLargeVector)
{
	Vector<int> v1;
	for (int i = 0; i < 10000; ++i)
		v1.PushBack(i);
	Vector<int> v2 = v1;
	EXPECT_EQ(v2.GetSize(), v1.GetSize());
	for (int i = 0; i < 10000; ++i)
		EXPECT_EQ(v2[i], i);
}

TEST(VectorTest, MoveLargeVector)
{
	Vector<int> v1;
	for (int i = 0; i < 10000; ++i)
		v1.PushBack(i);
	Vector<int> v2 = std::move(v1);
	EXPECT_EQ(v2.GetSize(), 10000);
	for (int i = 0; i < 10000; ++i)
		EXPECT_EQ(v2[i], i);
}

// 9. Вектор вектора
TEST(VectorTest, VectorOfVectors)
{
	Vector<Vector<int>> vv;
	vv.EmplaceBack();
	vv[0].PushBack(42);
	EXPECT_EQ(vv[0][0], 42);
}

// 10. Тип без конструктора по умолчанию
struct NoDefault
{
	int x;
	explicit NoDefault(int x)
		: x(x)
	{
	}
	bool operator==(const NoDefault& o) const { return x == o.x; }
};
TEST(VectorTest, NoDefaultType)
{
	Vector<NoDefault> v;
	v.EmplaceBack(5);
	v.EmplaceBack(7);
	EXPECT_EQ(v[0], NoDefault(5));
	EXPECT_EQ(v[1], NoDefault(7));
}

// 11. Тип только для перемещения
TEST(VectorTest, MoveOnlyType)
{
	Vector<std::unique_ptr<int>> v;
	v.PushBack(std::make_unique<int>(42));
	EXPECT_EQ(*v[0], 42);
	v.EmplaceBack(new int(99));
	EXPECT_EQ(*v[1], 99);
}

// 12. Итераторы и обратные итераторы
TEST(VectorTest, ReverseIterators)
{
	Vector<int> v;
	for (int i = 0; i < 3; ++i)
		v.PushBack(i + 1); // 1,2,3
	auto it = v.rbegin();
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 1);
}

TEST(VectorTest, ManyOperations)
{
	Vector<int> v;
	for (int i = 0; i < 100; ++i)
		v.PushBack(i);
	for (int i = 0; i < 50; ++i)
		v.PopBack();
	EXPECT_EQ(v.GetSize(), 50);
	v.Clear();
	EXPECT_EQ(v.GetSize(), 0);
	v.Resize(10);
	EXPECT_EQ(v.GetSize(), 10);
}

struct Counter
{
	static int count;
	Counter() { ++count; }
	Counter(const Counter&) { ++count; }
	Counter(Counter&&) noexcept { ++count; }
	~Counter() { --count; }
};
int Counter::count = 0;
TEST(VectorTest, NoLeaksOrDoubleDelete)
{
	{
		Vector<Counter> v;
		v.Resize(10);
		v.Clear();
		v.Resize(5);
	}
	EXPECT_EQ(Counter::count, 0);
}

// 15. Самоприсваивание
TEST(VectorTest, SelfAssignment)
{
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.PushBack(i);
	v = v;
	EXPECT_EQ(v.GetSize(), 10);
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], i);
	v = std::move(v);
	EXPECT_EQ(v.GetSize(), 10);
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], i);
}

// 16. Копирование и перемещение пустого вектора
TEST(VectorTest, CopyMoveEmptyVector)
{
	Vector<int> v1;
	Vector<int> v2 = v1;
	EXPECT_EQ(v2.GetSize(), 0);
	Vector<int> v3 = std::move(v1);
	EXPECT_EQ(v3.GetSize(), 0);
}

// 17. Работа с const Vector
TEST(VectorTest, ConstVector)
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	const Vector<int>& cv = v;
	EXPECT_EQ(cv.GetSize(), 2);
	EXPECT_EQ(cv[0], 1);
	EXPECT_EQ(cv[1], 2);
	auto it = cv.begin();
	EXPECT_EQ(*it, 1);
}

// 18. Тип с удалённым копированием, только move
struct MoveOnly
{
	int x;
	MoveOnly(int x)
		: x(x)
	{
	}
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly& operator=(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&& other) noexcept
		: x(other.x)
	{
		other.x = 0;
	}
	MoveOnly& operator=(MoveOnly&& other) noexcept
	{
		x = other.x;
		other.x = 0;
		return *this;
	}
};
TEST(VectorTest, MoveOnlyCustomType)
{
	Vector<MoveOnly> v;
	v.PushBack(MoveOnly(5));
	v.EmplaceBack(7);
	EXPECT_EQ(v[0].x, 5);
	EXPECT_EQ(v[1].x, 7);
}

// 19. Большой объект
TEST(VectorTest, LargeObject)
{
	Vector<std::array<int, 1000>> v;
	std::array<int, 1000> arr{};
	arr[999] = 42;
	v.PushBack(arr);
	EXPECT_EQ(v[0][999], 42);
}

// 20. Выход за границы (operator[])
TEST(VectorTest, OutOfRangeThrows)
{
	Vector<int> v;
	v.PushBack(1);
	EXPECT_THROW(v[1], std::out_of_range);
	EXPECT_NO_THROW(v[0]);
}

// 22. Тип с выбрасывающим operator=
struct ThrowOnAssign
{
	int x = 0;
	ThrowOnAssign() = default;
	ThrowOnAssign(const ThrowOnAssign&) = default;
	ThrowOnAssign& operator=(const ThrowOnAssign&) { throw std::runtime_error("assign"); }
};
TEST(VectorTest, ThrowingAssign)
{
	Vector<ThrowOnAssign> v;
	v.PushBack(ThrowOnAssign{});
	EXPECT_THROW(v[0] = ThrowOnAssign{}, std::runtime_error);
}

// 23. Тип с несколькими указателями
struct DoublePtr
{
	int* a;
	int* b;
	DoublePtr(int x, int y)
		: a(new int(x))
		, b(new int(y))
	{
	}
	DoublePtr(const DoublePtr& o)
		: a(new int(*o.a))
		, b(new int(*o.b))
	{
	}
	DoublePtr(DoublePtr&& o) noexcept
		: a(o.a)
		, b(o.b)
	{
		o.a = nullptr;
		o.b = nullptr;
	}
	DoublePtr& operator=(const DoublePtr& o)
	{
		if (this != &o)
		{
			delete a;
			delete b;
			a = new int(*o.a);
			b = new int(*o.b);
		}
		return *this;
	}
	DoublePtr& operator=(DoublePtr&& o) noexcept
	{
		if (this != &o)
		{
			delete a;
			delete b;
			a = o.a;
			b = o.b;
			o.a = nullptr;
			o.b = nullptr;
		}
		return *this;
	}
	~DoublePtr()
	{
		delete a;
		delete b;
	}
	bool operator==(const DoublePtr& o) const { return *a == *o.a && *b == *o.b; }
};
TEST(VectorTest, DoublePtrType)
{
	Vector<DoublePtr> v;
	v.EmplaceBack(1, 2);
	v.EmplaceBack(3, 4);
	EXPECT_EQ(v[0], DoublePtr(1, 2));
	EXPECT_EQ(v[1], DoublePtr(3, 4));
}

// 24. Тип без operator== (только push/pop)
struct NoEqual
{
	int x;
	NoEqual(int x)
		: x(x)
	{
	}
};
TEST(VectorTest, NoEqualType)
{
	Vector<NoEqual> v;
	v.EmplaceBack(1);
	v.EmplaceBack(2);
	EXPECT_EQ(v.GetSize(), 2);
	// Нельзя сравнивать элементы, но можно проверять размер
}

TEST(VectorTest, CoordsFullFunctionality)
{
	// PushBack, EmplaceBack, Resize, PopBack, Clear
	Vector<Coords> v;
	v.PushBack(Coords(1, 2, 3));
	v.EmplaceBack(4, 5, 6);
	v.EmplaceBack();
	EXPECT_EQ(v.GetSize(), 3);
	EXPECT_EQ(v[0], (Coords{ 1, 2, 3 }));
	EXPECT_EQ(v[1], (Coords{ 4, 5, 6 }));
	v[2].x = 7;
	v[2].y = 8;
	v[2].z = 9;
	EXPECT_EQ(v[2], (Coords{ 7, 8, 9 }));

	// PopBack
	v.PopBack();
	EXPECT_EQ(v.GetSize(), 2);
	v.PopBack();
	v.PopBack();
	EXPECT_EQ(v.GetSize(), 0);

	// Resize (увеличение и уменьшение)
	v.Resize(5);
	EXPECT_EQ(v.GetSize(), 5);
	v[0] = Coords(10, 11, 12);
	v.Resize(2);
	EXPECT_EQ(v.GetSize(), 2);
	EXPECT_EQ(v[0], (Coords{ 10, 11, 12 }));

	// Copy constructor
	v[1] = Coords(13, 14, 15);
	Vector<Coords> v2 = v;
	EXPECT_EQ(v2.GetSize(), 2);
	EXPECT_EQ(v2[1], (Coords{ 13, 14, 15 }));

	// Copy assignment
	Vector<Coords> v3;
	v3 = v2;
	EXPECT_EQ(v3[0], (Coords{ 10, 11, 12 }));

	// Move constructor
	Vector<Coords> v4 = std::move(v3);
	EXPECT_EQ(v4[0], (Coords{ 10, 11, 12 }));

	// Move assignment
	Vector<Coords> v5;
	v5 = std::move(v4);
	EXPECT_EQ(v5[1], (Coords{ 13, 14, 15 }));

	// Самоприсваивание
	v5 = v5;
	EXPECT_EQ(v5.GetSize(), 2);

	// Вложенный вектор
	Vector<Vector<Coords>> vv;
	vv.EmplaceBack();
	vv[0].PushBack(Coords(21, 22, 23));
	EXPECT_EQ(vv[0][0], (Coords{ 21, 22, 23 }));

	// Проверка выброса исключения
	EXPECT_THROW(v5[10], std::out_of_range);
}