#ifndef CAR_H
#define CAR_H

#include <unordered_map>

enum class Gear
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5
};

enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL
};

struct GearSpeedRange
{
	int minSpeed;
	int maxSpeed;
};

class Car
{
public:
	Car();
	~Car();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(Gear gear);
	void SetSpeed(int speed);

	bool IsTurnedOn() const;
	int GetSpeed() const;
	Direction GetDirection() const;
	Gear GetGear() const;

private:
	bool m_isTurnedOn;
	int m_speed;
	Direction m_direction;
	Gear m_gear;

	const std::unordered_map<Gear, GearSpeedRange> m_gearSpeedRanges
		= { { Gear::REVERSE, { 0, 20 } }, { Gear::NEUTRAL, { 0, 150 } },
			  { Gear::FIRST, { 0, 30 } }, { Gear::SECOND, { 20, 50 } },
			  { Gear::THIRD, { 30, 60 } }, { Gear::FOURTH, { 40, 90 } },
			  { Gear::FIFTH, { 50, 150 } } };

	void UpdateDirection(int speed, Gear gear);
	void AssertIsReadyToStop() const;
	void AssertIsValidGear(Gear gear) const;
	void AssertIsGearValidRange(Gear gear) const;
	void AssertIsEngineTurnedOn(Gear gear) const;
	void AssertIsReadyToReverse() const;
	void AssertIsReadyToForward() const;
	void AssertIsPositiveSpeed(int speed) const;
	void AssertIsVariableGear(int speed) const;
	void AssertIsSpeedValidRange(int speed) const;
};

#endif // CAR_H