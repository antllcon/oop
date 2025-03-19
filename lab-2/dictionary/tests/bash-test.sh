#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

cd ../../../build/program

program_name="start"

writeTestSuccess() {
  echo -e "${GREEN}Test passed${NC}"
}

writeTestError() {
  echo -e "${RED}Test failed${NC}"
}

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

# echo "0: Очень очень маленькие числа"
# expected="0.002 0.003 0.003"
# runTest "0.0007 0.0004 0.0009" "$expected"
  
# echo "1: Некорректный ввод (буква)"
# runErrorTest "1 a 2" "Error"

echo "Все тесты выполнены."