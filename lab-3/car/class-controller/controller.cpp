#include "controller.h"

void Controller::HandleCommand()
{
	std::string command;
	while (std::getline(m_input, command))
	{
		std::istringstream commandStream(command);
		std::string action;
		commandStream >> action;

		if (action == "Info")
		{
			Info();
		}
		else if (action == "EngineOn")
		{
			EngineOn();
		}
		else if (action == "EngineOff")
		{
			EngineOff();
		}
		else if (action == "SetGear")
		{
			std::string argument;
			commandStream >> argument;
			SetGear(argument);
		}
		else if (action == "SetSpeed")
		{
			std::string argument;
			commandStream >> argument;
			SetSpeed(argument);
		}
		else
		{
			throw std::invalid_argument("Invalid command");
		}
	}
}

void Controller::Info() const
{
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl;
	m_output << "Direction: ";
	PrintDirection();
	m_output << "Speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Gear: " << static_cast<int>(m_car.GetGear()) << std::endl;
}

void Controller::EngineOn() { m_car.TurnOnEngine(); }

void Controller::EngineOff() { m_car.TurnOffEngine(); }

void Controller::SetGear(const std::string& argument)
{
	int gear = std::stoi(argument);
	m_car.SetGear(static_cast<Gear>(gear));
}

void Controller::SetSpeed(const std::string& argument)
{
	int speed = std::stoi(argument);
	m_car.SetSpeed(speed);
}

void Controller::PrintDirection() const
{
	switch (m_car.GetDirection())
	{
	case Direction::FORWARD:
		m_output << "forward\n";
		break;
	case Direction::BACKWARD:
		m_output << "backward\n";
		break;
	case Direction::STANDING_STILL:
		m_output << "standing still\n";
		break;
	}
}