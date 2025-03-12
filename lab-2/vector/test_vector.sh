#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

program_name="vector"

writeTestSuccess() {
  echo -e "${GREEN}Test passed${NC}"
}

writeTestError() {
  echo -e "${RED}Test failed${NC}"
}

# Компиляция программы
echo "Компиляция программы..."
g++ -o $program_name $program_name.cpp
if [ $? -ne 0 ]; then
  echo -e "${RED}Ошибка компиляции${NC}"
  exit 1
fi

# Функция для запуска программы и проверки вывода
runTest() {
  local input="$1"
  local expected="$2"
  local result=$(echo "$input" | ./$program_name)
  if [ "$result" == "$expected" ]; then
    writeTestSuccess
  else
    writeTestError
  fi
}

# Функция для проверки ошибок
runErrorTest() {
  local input="$1"
  local expected_error="$2"
  local result=$(echo "$input" | ./$program_name 2>&1)
  if [[ "$result" == *"$expected_error"* ]]; then
    writeTestSuccess
  else
    writeTestError
  fi
}

echo "0: Пустой ввод"
expected=""
runTest "" "$expected"

echo "1: Один элемент"
expected="10.000"
runTest "5" "$expected"

echo "2: Два элемента"
expected="9.000 12.000"
runTest "5 2" "$expected"

echo "3: Три элемента"
expected="7.000 8.000 9.000"
runTest "1 2 3" "$expected"

echo "4: Много элементов"
expected="21.000 24.000 27.000 30.000"
runTest "12 9 6 3" "$expected"

echo "5: Есть отрицательные элементы"
expected="-14.100 -13.600 -12.300 0.000 12.100"
runTest "-4.1 -2.3 -3.6 10 22.1" "$expected"

echo "6: Все элементы отрицательные"
expected="-17.170 -16.160 -15.150 -14.140 -13.130"
runTest "-1.01 -2.02 -3.03 -4.04 -5.05" "$expected"

echo "7: Все дробные числа"
expected="1344.444 1345.443 2679.889"
runTest "1.9999999 2.999 1337.445" "$expected"

echo "8: Большие числа"
expected="4000003.000 4000004.000 4000005.000"
runTest "1000000 1000001 1000002" "$expected"

echo "9: Один элемент (ноль)"
expected="0.000"
runTest "0" "$expected"

echo "10: Ввод с разными разделителями"
expected="7.000 8.000 9.000"
runTest $'1\t2\n3' "$expected"

echo "11: Все элементы одинаковые"
expected="20.000 20.000 20.000 20.000"
runTest "5 5 5 5" "$expected"

echo "12: Один элемент — большое отрицательное число"
expected="-2000000.000"
runTest "-1000000" "$expected"

echo "13: Три элемента — нули"
expected="0.000 0.000 0.000"
runTest "0 0 0" "$expected"

echo "14: Ввод только пробелы"
expected=""
runTest "        " "$expected"

echo "15: Очень маленькие числа"
expected="0.007 0.008 0.009"
runTest "0.001 0.002 0.003" "$expected"

echo "15: Очень очень маленькие числа"
expected="0.002 0.003 0.003"
runTest "0.0007 0.0004 0.0009" "$expected"

echo "16: Некорректный ввод (буква)"
runErrorTest "1 a 2" "Error"

echo "Все тесты выполнены."