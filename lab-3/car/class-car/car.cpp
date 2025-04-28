#include "car.h"
#include <iostream>
#include <limits>
#include <stdexcept>

Car::Car()
	: m_isTurnedOn(false)
	, m_speed(0)
	, m_direction(Direction::STANDING_STILL)
	, m_gear(Gear::NEUTRAL){};

Car::~Car() = default;

bool Car::IsTurnedOn() const { return m_isTurnedOn; }

int Car::GetSpeed() const { return m_speed; }

Direction Car::GetDirection() const { return m_direction; }

Gear Car::GetGear() const { return m_gear; }

void Car::TurnOnEngine() { m_isTurnedOn = true; }

void Car::TurnOffEngine()
{
	AssertIsReadyToStop();
	m_isTurnedOn = false;
}

void Car::UpdateDirection(int speed, Gear gear)
{
	if (speed == 0)
	{
		m_direction = Direction::STANDING_STILL;
		return;
	}

	if (gear == Gear::REVERSE)
	{
		m_direction = Direction::BACKWARD;
		return;
	}

	m_direction = Direction::FORWARD;
}

void Car::SetGear(Gear gear)
{
	AssertIsValidGear(gear);
	AssertIsGearValidRange(gear);
	AssertIsEngineTurnedOn(gear);
	AssertIsReadyToReverse();

	if (gear == Gear::REVERSE && m_speed != 0)
	{
		throw std::runtime_error("Нельзя делать полецейский разворот");
	}

	UpdateDirection(m_speed, gear);
	m_gear = gear;
}

void Car::SetSpeed(int speed)
{
	AssertIsEngineTurnedOn(m_gear);
	AssertIsPositiveSpeed(speed);
	AssertIsVariableGear(speed);
	AssertIsSpeedValidRange(speed);

	UpdateDirection(speed, m_gear);
	m_speed = speed;
}

void Car::AssertIsReadyToStop() const
{
	if (m_gear != Gear::NEUTRAL || m_speed != 0)
	{
		throw std::runtime_error("Нельзя выключить двигатель в движущейся машине");
	}
}

void Car::AssertIsVariableGear(int speed) const
{
	if (m_gear == Gear::NEUTRAL && speed > m_speed)
	{
		throw std::runtime_error(
			"Нельзя увеличивать скорость на нейтральной передаче");
	}
}

void Car::AssertIsPositiveSpeed(int speed) const
{
	if (speed < 0)
	{
		throw std::invalid_argument("Нельзя ездить на отрицательной скорости");
	}
}

void Car::AssertIsReadyToReverse() const
{
	if (m_isTurnedOn && m_speed != 0 && m_gear == Gear::REVERSE)
	{
		throw std::runtime_error(
			"Нельзя переключать передачу при движении задним ходом");
	}
}

void Car::AssertIsReadyToForward() const
{
	if (m_gear == Gear::REVERSE)
	{
		throw std::runtime_error("Нельзя сменить направление если ты едешь назад");
	}
}

void Car::AssertIsValidGear(Gear gear) const
{
	if (gear < Gear::REVERSE || Gear::FIFTH < gear)
	{
		throw std::invalid_argument("Нельзя ездить на несуществующей передаче");
	}
}

void Car::AssertIsGearValidRange(Gear gear) const
{
	if (m_speed < m_gearSpeedRanges.at(gear).minSpeed
		|| m_speed > m_gearSpeedRanges.at(gear).maxSpeed)
	{
		throw std::runtime_error("Нельзя установить передачу вне диапазона скорости");
	}
}

void Car::AssertIsSpeedValidRange(int speed) const
{
	if (speed < m_gearSpeedRanges.at(m_gear).minSpeed
		|| m_gearSpeedRanges.at(m_gear).maxSpeed < speed)
		throw std::runtime_error("Нельзя гнать на скорости вне диапазона передачи");
}

void Car::AssertIsEngineTurnedOn(Gear gear) const
{
	if (!m_isTurnedOn && gear != Gear::NEUTRAL)
	{
		throw std::runtime_error("Нельзя менять передачи при выключенном двигателе");
	}
}