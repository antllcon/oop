#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include "../class-car/car.h"
#include <iostream>
#include <sstream>
#include <string>

class Controller
{
public:
	Controller(Car& car, std::istream& input, std::ostream& output)
		: m_car(car)
		, m_input(input)
		, m_output(output)
	{
	}

	void HandleCommand();

private:
	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	void Info() const;
	void EngineOn();
	void EngineOff();
	void SetGear(const std::string& argument);
	void SetSpeed(const std::string& argument);
	void PrintDirection() const;
};

#endif // CAR_CONTROLLER_H