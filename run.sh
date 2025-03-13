#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Ошибка: Не корректно указаны аргументы."
  echo "Используй: ./run.sh <номер лабы> <имя_задания>"
  exit 1
fi

NUM_LAB=$1
TASK_NAME=$2

TASK_DIR="lab-$NUM_LAB/$TASK_NAME"

if [ ! -d "$TASK_DIR" ]; then
  echo "Ошибка: Папка задания '$TASK_DIR' не найдена."
  exit 1
fi

echo "Очистка папки build..."
rm -rf build/*
mkdir -p build

echo "Сборка основной программы для задания '$TASK_NAME'..."
cd "$TASK_DIR" || exit 1
mkdir -p ../../build/program
cd ../../build/program || exit 1
cmake ../../"$TASK_DIR"
make
 
echo "Возвращаемся в корень проекта"
cd ../../

echo "Сборка unit-тестов для задания '$TASK_NAME'..."
cd "$TASK_DIR/tests" || exit 1
mkdir -p ../../../build/tests
cd ../../../build/tests || exit 1
cmake ../../"$TASK_DIR"/tests
make

cd ../../

echo "Запуск unit-тестов..."
./build/tests/unit-test

echo "Запуск интеграционных тестов..."
cd "$TASK_DIR/tests" || exit 1
./bash-test.sh

echo "Сборка и тестирование задания '$TASK_NAME' завершено."