#include <cstddef>
#include <utility>

namespace constants
{
inline constexpr int INIT_CAPACITY = 2;
} // namespace constants

template <typename T>
class Vector
{
public:
	Vector();
	~Vector();

	size_t GetSize() const;
	void PushBack(const T& value);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

private:
	void ReAlloc(size_t newCapacity);

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};

template <typename T>
Vector<T>::Vector()
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
{
	ReAlloc(constants::INIT_CAPACITY);
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] m_data;
}

template <typename T>
void Vector<T>::ReAlloc(size_t newCapacity)
{
	// Метод поддерживает уменьшение памяти
	if (m_size > newCapacity)
	{
		m_size = newCapacity;
	}

	T* newData = new T[newCapacity];

	for (size_t i = 0; i < m_size; ++i)
	{
		newData[i] = std::move(m_data[i]);
	}

	delete[] m_data;
	m_data = newData;
	m_capacity = newCapacity;
}

template <typename T>
void Vector<T>::PushBack(const T& value)
{
	if (m_size >= m_capacity)
	{
		ReAlloc(m_capacity + m_capacity);
	}
	m_data[m_size++] = value;
}

template <typename T>
size_t Vector<T>::GetSize() const
{
	return m_size;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	return m_data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return m_data[index];
}