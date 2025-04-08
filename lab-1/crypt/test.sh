#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

program_name="crypt"

writeTestSuccess() {
  echo -e "${GREEN}Test passed${NC}"
}

writeTestError() {  
  echo -e "${RED}Test failed${NC}"
}

echo "Компиляция программы..."
g++ -o $program_name $program_name.cpp
if [ $? -ne 0 ]; then
  echo -e "${RED}Ошибка компиляции${NC}"
  exit 1
fi

runTest() {
  local input="$1"
  local expected="$2"
  local result=$(echo -e "$input" | ./$program_name)
  if [ "$result" == "$expected" ]; then
    writeTestSuccess
  else
    writeTestError
    echo -e "Ожидалось:\n$expected"
    echo -e "Получено:\n$result"
  fi
}

runErrorTest() {
  local input="$1"
  local expected_error="$2"
  local result=$(echo -e "$input" | ./$program_name 2>&1)
  if [[ "$result" == *"$expected_error"* ]]; then
    writeTestSuccess
  else
    writeTestError
    echo -e "Ожидалась ошибка: $expected_error"
    echo -e "Получено: $result"
  fi
}

MAX_VALID_KEY=255
MIN_VALID_KEY=0
VALID_KEY=99
INVALID_HEX_KEY=4A
TOO_LARGE_KEY=256
TOO_SMALL_KEY=-1


echo "1: Название (кратко 1-3 слова)"
expected="..."
runTest "..." "$expected"

echo "2: Название (кратко 1-3 слова)"
expected="0.002 0.003 0.003"
runTest "..." "$expected"

echo "Все тесты выполнены."
exit 0