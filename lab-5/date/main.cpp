#include "Date/Date.h"
#include <iostream>

std::string DayOfWeekToString(DayOfWeek weekDay)
{
	switch (weekDay)
	{
	case DayOfWeek::SUNDAY:
		return "Воскресенье";
	case DayOfWeek::MONDAY:
		return "Понедельник";
	case DayOfWeek::TUESDAY:
		return "Вторник";
	case DayOfWeek::WEDNESDAY:
		return "Среда";
	case DayOfWeek::THURSDAY:
		return "Четверг";
	case DayOfWeek::FRIDAY:
		return "Пятница";
	case DayOfWeek::SATURDAY:
		return "Суббота";
	default:
		return "Неизвестный день недели, друг...";
	}
}

int main()
{
	try
	{
		Date date(11, 9, 2001);
		std::cout << date << "  ===✈ ∏∏" << std::endl;
		std::cout << "=========" << std::endl;
		Date fate1(2345);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
}
