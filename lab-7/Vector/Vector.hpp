#include <cstddef>
#include <stdexcept>
#include <utility>

namespace constants
{
inline constexpr size_t INIT_CAPACITY = 2;
} // namespace constants

template <typename T>
class Vector
{
public:
	Vector()
		: m_data(nullptr)
		, m_size(0)
		, m_capacity(0)
	{
		ReAlloc(constants::INIT_CAPACITY);
	}

	Vector(const Vector& other)
		: m_data(nullptr)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
		for (size_t i = 0; i < m_size; ++i)
		{
			new (&m_data[i]) T(other.m_data[i]);
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			Clear();
			::operator delete(m_data, m_capacity * sizeof(T));

			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
			for (size_t i = 0; i < m_size; ++i)
			{
				new (&m_data[i]) T(other.m_data[i]);
			}
		}
		return *this;
	}

	Vector(Vector&& other) noexcept
		: m_data(other.m_data)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	Vector& operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			::operator delete(m_data, m_capacity * sizeof(T));

			m_data = other.m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			other.m_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	~Vector()
	{
		Clear();
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	size_t GetSize() const
	{
		return m_size;
	}

	void PushBack(const T& value)
	{
		TryToRelAlloc();
		m_data[m_size] = value;
		++m_size;
	}

	void PushBack(T&& value)
	{
		TryToRelAlloc();
		new (&m_data[m_size]) T(std::move(value));
		++m_size;
	}

	template <typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		TryToRelAlloc();

		new (&m_data[m_size]) T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}

	void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();
		}
	}

	void Resize(size_t newSize)
	{
		if (newSize < m_size)
		{
			for (size_t i = newSize; i < m_size; ++i)
			{
				m_data[i].~T();
			}
			m_size = newSize;
		}
		else if (newSize > m_size)
		{
			if (newSize > m_capacity)
			{
				size_t newCapacity = m_capacity;
				while (newCapacity < newSize)
				{
					newCapacity = newCapacity + newCapacity / 2 + 1;
				}
				ReAlloc(newCapacity);
			}

			for (size_t i = m_size; i < newSize; ++i)
			{
				new (&m_data[i]) T();
			}
			m_size = newSize;
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}

		m_size = 0;
	}

	T* begin() noexcept
	{
		return m_data;
	}

	T* end() noexcept
	{
		return m_data + m_size;
	}

	const T* begin() const noexcept
	{
		return m_data;
	}

	const T* end() const noexcept
	{
		return m_data + m_size;
	}

	const T* cbegin() const noexcept
	{
		return m_data;
	}

	const T* cend() const noexcept
	{
		return m_data + m_size;
	}

	std::reverse_iterator<T*> rbegin() noexcept
	{
		return std::reverse_iterator<T*>(end());
	}

	std::reverse_iterator<T*> rend() noexcept
	{
		return std::reverse_iterator<T*>(begin());
	}

	std::reverse_iterator<const T*> rbegin() const noexcept
	{
		return std::reverse_iterator<const T*>(end());
	}

	std::reverse_iterator<const T*> rend() const noexcept
	{
		return std::reverse_iterator<const T*>(begin());
	}

	std::reverse_iterator<const T*> crbegin() const noexcept
	{
		return std::reverse_iterator<const T*>(cend());
	}

	std::reverse_iterator<const T*> crend() const noexcept
	{
		return std::reverse_iterator<const T*>(cbegin());
	}

	T& operator[](size_t index)
	{
		AssertIsValidIndex(index);
		return m_data[index];
	}

	const T& operator[](size_t index) const
	{
		AssertIsValidIndex(index);
		return m_data[index];
	}

private:
	void AssertIsValidIndex(size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Выход за пределы размера вектора");
		}
	}

	void ReAlloc(size_t newCapacity)
	{
		if (m_size > newCapacity)
		{
			m_size = newCapacity;
		}

		T* newData = (T*)::operator new(newCapacity * sizeof(T));

		for (size_t i = 0; i < m_size; ++i)
		{
			new (&newData[i]) T(std::move(m_data[i]));
		}

		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].~T();
		}

		::operator delete(m_data, m_capacity * sizeof(T));
		m_data = newData;
		m_capacity = newCapacity;
	}

	void TryToRelAlloc()
	{
		if (m_size >= m_capacity)
		{
			ReAlloc(m_capacity * 2);
		}
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};