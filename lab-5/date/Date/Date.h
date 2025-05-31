#ifndef DATE_H
#define DATE_H

#include <istream>
#include <ostream>
#include <tuple>

// Месяц
enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

// День недели
enum class DayOfWeek
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class Date
{
public:
	static Date Min();
	static Date Max();
	static Date Now();

public:
	Date() = default;

	explicit Date(unsigned daysSinceEpoch);
	Date(unsigned day, unsigned month, unsigned year);
	Date(unsigned day, Month month, unsigned year);

	unsigned GetDay() const noexcept;
	Month GetMonth() const noexcept;
	unsigned GetYear() const noexcept;
	DayOfWeek GetDayOfWeek() const noexcept;
	std::string ToString() const noexcept;

public:
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	Date operator+(int days) const;
	Date operator-(int days) const;
	int operator-(const Date& other) const;
	Date& operator+=(int days);
	Date& operator-=(int days);
	auto operator<=>(const Date& other) const noexcept = default;
	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);

private:
	unsigned FromDate(unsigned day, unsigned month, unsigned year) const noexcept;
	std::tuple<unsigned, unsigned, unsigned> ToDate() const noexcept;

private:
	unsigned m_epochDays = 0;
};

#endif // DATE_H
