#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

writeTestSuccess() {
  echo -e "${GREEN}Test passed${NC}"
}

writeTestError() {
  echo -e "${RED}Test failed${NC}"
  exit 1
}

echo "Проверка запуска"
./radix 16 10 1F > output.txt
if [ $? -eq 0 ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Базовый перевод"
expected="31"
result=$(./radix 16 10 1F)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Обратный перевод"
expected="1F"
result=$(./radix 10 16 31)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Границы диапазона (INT_MAX)"
expected=$(printf "%X" $((2**31 - 1)))
result=$(./radix 10 16 $((2**31 - 1)))
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Границы диапазона (INT_MIN)"
expected="-80000000"
result=$(./radix 10 16 -2147483648)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Отрицательные числа"
expected="-1010"
result=$(./radix 10 2 -10)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "36-ричная система"
expected="35"
result=$(./radix 36 10 Z)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Нули в начале"
expected="10"
result=$(./radix 10 10 00010)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Пустая строка числа"
result=$(./radix 10 2 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Некорректное основание системы счисления (слишком маленькое)"
result=$(./radix 1 10 12 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Некорректное основание системы счисления (слишком большое)"
result=$(./radix 37 10 12 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Символ вне диапазона системы счисления"
result=$(./radix 2 10 102 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Переполнение при конверсии"
result=$(./radix 10 10 99999999999999999999999999999999 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Перевод нуля"
expected="0"
result=$(./radix 10 2 0)
if [ "$result" == "$expected" ]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Неверные входные данные"
result=$(./radix 10 2 XYZ 2>&1)
if [[ "$result" == *"Error"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Недостаточно аргументов"
result=$(./radix 10 2 2>&1)
if [[ "$result" == *"Usage"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "Слишком много аргументов"
result=$(./radix 10 2 10 extra 2>&1)
if [[ "$result" == *"Usage"* ]]; then
  writeTestSuccess
else
  writeTestError
fi

echo "MAX_INT + 1 (должна быть ошибка)"
result=$(./radix 10 10 $((2147483647 + 1)) 2>&1)
if [[ "$result" == *"Error"* ]]; then
    writeTestSuccess
else
    writeTestError
fi

echo "MAX_INT (должно пройти)"
expected="2147483647"
result=$(./radix 10 10 2147483647)
if [ "$result" == "$expected" ]; then
    writeTestSuccess
else
    writeTestError
fi

echo "MIN_INT - 1 (должна быть ошибка)"
result=$(./radix 10 10 -2147483649 2>&1)
if [[ "$result" == *"Error"* ]]; then
    writeTestSuccess
else
    writeTestError
fi

echo "MIN_INT (должно пройти)"
expected="-2147483648"
result=$(./radix 10 10 -2147483648)
if [ "$result" == "$expected" ]; then
    writeTestSuccess
else
    writeTestError
fi

echo "MAX_INT + 1 - 1 (должно пройти)"
expected="-2147483647"
result=$(./radix 10 10 $((2147483647 + 1 - 1)) 2>&1)
if [ "$result" == "$expected" ]; then
    writeTestSuccess
else
    writeTestError
fi

echo "MIN_INT - 1 + 1 (должно пройти)"
expected="-2147483648"
result=$(./radix 10 10 $((-2147483648 - 1 + 1)) 2>&1)
if [ "$result" == "$expected" ]; then
    writeTestSuccess
else
    writeTestError
fi

echo "Все тесты выполнены."