#include "../class-car/car.h"
#include <gtest/gtest.h>

// Инициалзация
TEST(Car, CarInitialization)
{
	Car car;
	EXPECT_FALSE(car.IsTurnedOn());
	EXPECT_EQ(car.GetSpeed(), 0);
	EXPECT_EQ(car.GetDirection(), Direction::STANDING_STILL);
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
}

// Двигатель успешно включается, если был выключен
TEST(Car, EngineStartsWhenOff)
{
	Car car;
	EXPECT_FALSE(car.IsTurnedOn());
	car.TurnOnEngine();
	EXPECT_TRUE(car.IsTurnedOn());
}

// Попытка включить уже работающий двигатель
TEST(Car, EngineAlreadyOn)
{
	Car car;
	car.TurnOnEngine();
	car.TurnOnEngine();
	EXPECT_TRUE(car.IsTurnedOn());
}

// Двигатель выключается на нейтрали при нулевой скорости
TEST(Car, EngineTurnsOffWhenNeutralAndStopped)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_EQ(car.GetSpeed(), 0);
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
	car.TurnOffEngine();
	EXPECT_FALSE(car.IsTurnedOn());
}

// Нельзя выключить двигатель на передаче отличной от нейтральной
TEST(Car, EngineFailsToTurnOffWhenNotInNeutral)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	EXPECT_THROW(car.TurnOffEngine(), std::runtime_error);
}

// Нельзя выключить двигатель при ненулевой скорости
TEST(Car, EngineFailsToTurnOffWhenMoving)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	car.SetSpeed(10);
	EXPECT_THROW(car.TurnOffEngine(), std::runtime_error);
}

// Выключение уже выключенного двигателя
TEST(Car, EngineAlreadyOff)
{
	Car car;
	car.TurnOffEngine();
	EXPECT_FALSE(car.IsTurnedOn());
}

// Нельзя переключить передачу при выключенном двигателе
TEST(Car, CannotSetGearWhenEngineOff)
{
	Car car;
	EXPECT_THROW(car.SetGear(Gear::REVERSE), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::FIRST), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::SECOND), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::THIRD), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::FOURTH), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::FIFTH), std::runtime_error);
}

// Можно установить нейтраль при выключенном двигателе
TEST(Car, CanSetNeutralWhenEngineOff)
{
	Car car;
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
}

// Задняя передача включается только при нулевой скорости
TEST(Car, CanSetReverseOnlyAtZeroSpeed)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_NO_THROW(car.SetGear(Gear::REVERSE));
	EXPECT_EQ(car.GetGear(), Gear::REVERSE);
}

// Нельзя включить заднюю при скорости больше нуля
TEST(Car, CannotSetReverseWhenMovingForward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	car.SetSpeed(10);
	EXPECT_THROW(car.SetGear(Gear::REVERSE), std::runtime_error);
}

// ? - Нельзя включить заднюю при движении назад
// TODO: исправь exception
TEST(Car, CannotSetReverseWhenMovingBackward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::REVERSE);
	car.SetSpeed(20);
	EXPECT_THROW(car.SetGear(Gear::REVERSE), std::runtime_error);
}

// Нейтраль можно включить c любой передачи
TEST(Car, CanSetNeutralAtAnySpeed)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	car.SetSpeed(10);
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
	car.SetGear(Gear::FIRST);
	car.SetSpeed(20);
	car.SetGear(Gear::SECOND);
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
	car.SetGear(Gear::SECOND);
	car.SetSpeed(30);
	car.SetGear(Gear::THIRD);
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
	car.SetGear(Gear::THIRD);
	car.SetSpeed(40);
	car.SetGear(Gear::FOURTH);
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
	car.SetGear(Gear::FOURTH);
	car.SetSpeed(50);
	car.SetGear(Gear::FIFTH);
	EXPECT_NO_THROW(car.SetGear(Gear::NEUTRAL));
	EXPECT_EQ(car.GetGear(), Gear::NEUTRAL);
}

// Передача включается, если скорость в допустимом диапазоне
// Передача не включается, если скорость вне диапазона
TEST(Car, CanSetGearIfSpeedInRange)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_NO_THROW(car.SetGear(Gear::REVERSE));
	EXPECT_THROW(car.SetSpeed(-1), std::invalid_argument);
	car.SetSpeed(10);
	car.SetSpeed(20);
	EXPECT_THROW(car.SetSpeed(21), std::runtime_error);
	car.SetSpeed(0);
	EXPECT_NO_THROW(car.SetGear(Gear::FIRST));
	car.SetSpeed(10);
	car.SetSpeed(20);
	car.SetSpeed(30);
	EXPECT_THROW(car.SetSpeed(31), std::runtime_error);
	EXPECT_NO_THROW(car.SetGear(Gear::SECOND));
	EXPECT_THROW(car.SetSpeed(19), std::runtime_error);
	car.SetSpeed(20);
	car.SetSpeed(30);
	car.SetSpeed(50);
	EXPECT_THROW(car.SetSpeed(51), std::runtime_error);
	EXPECT_NO_THROW(car.SetGear(Gear::THIRD));
	EXPECT_THROW(car.SetSpeed(29), std::runtime_error);
	car.SetSpeed(30);
	car.SetSpeed(40);
	car.SetSpeed(60);
	EXPECT_THROW(car.SetSpeed(61), std::runtime_error);
	EXPECT_NO_THROW(car.SetGear(Gear::FOURTH));
	EXPECT_THROW(car.SetSpeed(39), std::runtime_error);
	car.SetSpeed(40);
	car.SetSpeed(50);
	car.SetSpeed(90);
	EXPECT_THROW(car.SetSpeed(91), std::runtime_error);
	EXPECT_NO_THROW(car.SetGear(Gear::FIFTH));
	EXPECT_THROW(car.SetSpeed(49), std::runtime_error);
	car.SetSpeed(50);
	car.SetSpeed(60);
	car.SetSpeed(150);
	EXPECT_THROW(car.SetSpeed(151), std::runtime_error);
}

// Нельзя включить передние передачи при движении назад
TEST(Car, CannotSetForwardGearWhenMovingBackward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::REVERSE);
	car.SetSpeed(10);
	EXPECT_THROW(car.SetGear(Gear::SECOND), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::THIRD), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::FOURTH), std::runtime_error);
	EXPECT_THROW(car.SetGear(Gear::FIFTH), std::runtime_error);
}

// Можно включить переднюю передачу после остановки с заднего хода
TEST(Car, CanSetForwardGearAfterStoppingFromReverse)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::REVERSE);
	car.SetSpeed(10);
	car.SetSpeed(0);
	EXPECT_NO_THROW(car.SetGear(Gear::FIRST));
	EXPECT_EQ(car.GetGear(), Gear::FIRST);
}

// Нельзя изменить скорость при выключенном двигателе
TEST(Car, CannotSetSpeedWhenEngineOff)
{
	Car car;
	EXPECT_THROW(car.SetSpeed(10), std::runtime_error);
}

// На нейтрали можно только снижать скорость (по модулю)
// TEST(Car, CanOnlyDecreaseSpeedOnNeutral)
// {
// 	Car car;
// 	car.TurnOnEngine();
// 	car.SetGear(Gear::FIRST);
// 	car.SetSpeed(10);
// 	car.SetGear(Gear::NEUTRAL);
// 	EXPECT_THROW(car.SetSpeed(20), std::runtime_error);
// 	EXPECT_NO_THROW(car.SetSpeed(0));
// }

// CannotIncreaseSpeedOnNeutral – на нейтрали нельзя увеличить скорость
TEST(Car, CannotIncreaseSpeedOnNeutral)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_THROW(car.SetSpeed(10), std::runtime_error);
}

// Направление при движении на передних передачах
TEST(Car, DirectionIsForwardWhenMovingForward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	car.SetSpeed(20);
	EXPECT_EQ(car.GetDirection(), Direction::FORWARD);
	car.SetGear(Gear::SECOND);
	car.SetSpeed(30);
	EXPECT_EQ(car.GetDirection(), Direction::FORWARD);
	car.SetGear(Gear::THIRD);
	car.SetSpeed(40);
	EXPECT_EQ(car.GetDirection(), Direction::FORWARD);
	car.SetGear(Gear::FOURTH);
	car.SetSpeed(50);
	EXPECT_EQ(car.GetDirection(), Direction::FORWARD);
	car.SetGear(Gear::FIFTH);
	car.SetSpeed(60);
	EXPECT_EQ(car.GetDirection(), Direction::FORWARD);
	car.SetGear(Gear::NEUTRAL);
}

// Направление при движении на задней передаче
TEST(Car, DirectionIsBackwardWhenMovingBackward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::REVERSE);
	car.SetSpeed(20);
	EXPECT_EQ(car.GetDirection(), Direction::BACKWARD);
	car.SetGear(Gear::NEUTRAL);
}
