#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

program_name="invert"

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
  local result=$(echo -e "$input" | ./$program_name)
  if [ "$result" == "$expected" ]; then
    writeTestSuccess
  else
    writeTestError
    echo -e "Ожидалось:\n$expected"
    echo -e "Получено:\n$result"
  fi
}

# Функция для проверки ошибок
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

# Тест 1: Корректное чтение матрицы из файла
echo "Тест 1: Корректное чтение матрицы из файла"
expected='-24.000\t18.000\t5.000\n20.000\t-15.000\t-4.000\n-5.000\t4.000\t1.000'
echo -e '1\t2\t3\n0\t1\t4\n5\t6\t0' > test_matrix.txt
runTest "" "$expected" < test_matrix.txt
rm test_matrix.txt

# Тест 2: Корректное чтение матрицы из stdin
echo "Тест 2: Корректное чтение матрицы из stdin"
expected='-24.000\t18.000\t5.000\n20.000\t-15.000\t-4.000\n-5.000\t4.000\t1.000'
input='1\t2\t3\n0\t1\t4\n5\t6\t0'
runTest "$input" "$expected"

# Тест 3: Вырожденная матрица (определитель = 0)
echo "Тест 3: Вырожденная матрица (определитель = 0)"
input='1\t2\t3\n4\t5\t6\n7\t8\t9'
expected_error="Non-invertible"
runErrorTest "$input" "$expected_error"

# Тест 4: Некорректный формат матрицы (недостаточно чисел)
echo "Тест 4: Некорректный формат матрицы (недостаточно чисел)"
input='1\t2\t3\n4\t5\n6\t7\t8'
expected_error="Invalid matrix format"
runErrorTest "$input" "$expected_error"

# Тест 5: Некорректный формат матрицы (лишние символы)
echo "Тест 5: Некорректный формат матрицы (лишние символы)"
input='1\t2\t3\n4\t5\t6\n7\t8\t9\t10'
expected_error="Invalid matrix format"
runErrorTest "$input" "$expected_error"

# Тест 6: Некорректный файл (файл не существует)
echo "Тест 6: Некорректный файл (файл не существует)"
expected_error="Cannot open file"
runErrorTest "" "$expected_error" <<< "./$program_name non_existent_file.txt"

# Тест 7: Вывод справки
echo "Тест 7: Вывод справки"
expected='Usage: invert [input_file]\n       invert 	// read matrix from STDIN\n       invert -h 	// display this help message'
result=$(./$program_name -h)
if [[ "$result" == *"$expected"* ]]; then
  writeTestSuccess
else
  writeTestError
  echo -e "Ожидалось:\n$expected"
  echo -e "Получено:\n$result"
fi

# Тест 8: Некорректный режим (слишком много аргументов)
echo "Тест 8: Некорректный режим (слишком много аргументов)"
expected_error="invalid usage"
runErrorTest "" "$expected_error" <<< "./$program_name arg1 arg2"

# Тест 9: Матрица с нулевыми элементами
echo "Тест 9: Матрица с нулевыми элементами"
expected='0.000\t0.000\t0.000\n0.000\t0.000\t0.000\n0.000\t0.000\t0.000'
input='0\t0\t0\n0\t0\t0\n0\t0\t0'
runTest "$input" "$expected"

# Тест 10: Матрица с отрицательными числами
echo "Тест 10: Матрица с отрицательными числами"
expected='-0.500\t0.500\t0.000\n0.500\t-0.500\t0.000\n0.000\t0.000\t0.500'
input='1\t1\t0\n1\t1\t0\n0\t0\t2'
runTest "$input" "$expected"

