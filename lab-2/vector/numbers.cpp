#include "numbers.h"

namespace constants
{
inline constexpr size_t MIN_COUNT = 3;
inline constexpr int OUTPUT_PRECISION = 3;
inline constexpr double INIT_VALUE = 0.0;
} // namespace constants

void ReadNumbers(std::vector<double>& numbers)
{
	double number;
	while (std::cin >> number)
	{
		numbers.push_back(number);
	}
	if (!std::cin.eof())
	{
		throw std::runtime_error("It's not a double number.");
	}
}

void ProcessNumbers(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	size_t numberMinElements = std::min(constants::MIN_COUNT, numbers.size());
	std::vector<double> minElements(numberMinElements);

	std::partial_sort_copy(numbers.begin(), numbers.end(), minElements.begin(), minElements.end());

	double sumMinElements
		= std::accumulate(minElements.begin(), minElements.end(), constants::INIT_VALUE);

	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		[sumMinElements](double number) { return number + sumMinElements; });
}

void PrintSortedNumbers(const std::vector<double>& numbers)
{
	std::vector<double> sortedNumbers = numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());

	std::cout << std::fixed << std::setprecision(constants::OUTPUT_PRECISION);
	for (size_t i = 0; i < sortedNumbers.size(); ++i)
	{
		std::cout << sortedNumbers[i];
		if (i < sortedNumbers.size() - 1)
		{
			std::cout << ' ';
		}
	}
	std::cout << '\n';
}