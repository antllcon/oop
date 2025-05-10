#include "../class-bank/bank.h"
#include "../class-person/person.h"
#include <memory>
#include <vector>

class Simulation
{
public:
	// Нужен конструктор эмуляции
	// Иницилазиация денег в банке
	// Инициализация денег акторов
	// Запуск эмуляции
	void RunSimulation();

private:
	void MakeStep();

private:
	Bank bank;
	std::unique_ptr<Person> people;
};