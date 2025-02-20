#!/bin/bash

# Функция для сравнения файлов
compare_files() {
    if diff "$1" "$2" > /dev/null; then
        echo "Passed: $3"
    else
        echo "Failed: $3"
    fi
}

# Режим командной строки

# Тест 1: Базовая замена
echo -e "mama delala pelmeni\nya pokushal plotno" > in.txt
./replace in.txt out.txt "ma" "mama"
echo -e "mamamama delala pelmeni\nya pokushal plotno" > expected.txt
compare_files out.txt expected.txt "Test 1 (command line mode: basic replacement)"

# Тест 2: Пустая строка поиска
echo -e "mama delala pelmeni\nya pokushal plotno" > in.txt
./replace in.txt out.txt "" "mama"
echo -e "mama delala pelmeni\nya pokushal plotno" > expected.txt
compare_files out.txt expected.txt "Test 2 (command line mode: empty search string)"

# Тест 3: Замена на саму себя
echo -e "mama delala pelmeni\nya pokushal plotno" > in.txt
./replace in.txt out.txt "mama" "mama"
echo -e "mama delala pelmeni\nya pokushal plotno" > expected.txt
compare_files out.txt expected.txt "Test 3 (command line mode: replace with itself)"

# Тест 4: Пересекающиеся вхождения
echo -e "12312312345" > in.txt
./replace in.txt out.txt "1231234" "XYZ"
echo -e "123XYZ5" > expected.txt
compare_files out.txt expected.txt "Test 4 (command line mode: overlapping occurrences)"

# Тест 5: Ошибка открытия файла
if ./replace non_existent.txt out.txt "ma" "mama" > /dev/null 2>&1; then
    echo "Failed: Test 5 (command line mode: file open error)"
else
    echo "Passed: Test 5 (command line mode: file open error)"
fi

# Тест 6: Пустой файл
> in.txt
./replace in.txt out.txt "ma" "mama"
> expected.txt
compare_files out.txt expected.txt "Test 6 (command line mode: empty file)"

# Тест 7: Пустая строка-заменитель
echo -e "mama delala pelmeni\nya pokushal plotno" > in.txt
./replace in.txt out.txt "ma" ""
echo -e " delala pelmeni\nya pokushal plotno" > expected.txt
compare_files out.txt expected.txt "Test 7 (command line mode: empty replacement string)"

# Тест 8: Многократная замена в одной строке
echo -e "mama ma ma\nmama ma\nma mama" > in.txt
./replace in.txt out.txt "ma" "mama"
echo -e "mamamama mama mama\nmamamama mama\nmama mamamama" > expected.txt
compare_files out.txt expected.txt "Test 8 (command line mode: multiple replacements in one line)"

# Тест 9: Спецсимволы
echo -e "mama\tma\nma" > in.txt
./replace in.txt out.txt $'\t' "TAB"
echo -e "mamaTABma\nma" > expected.txt
compare_files out.txt expected.txt "Test 9 (command line mode: special characters)"

# Тест 10: Ошибка открытия файла с выводом ERROR
./replace non_existent.txt out.txt "ma" "mama" > /dev/null 2>&1
if [ $? -eq 1 ]; then
    echo "Passed: Test 10 (command line mode: file open error with ERROR output)"
else
    echo "Failed: Test 10 (command line mode: file open error with ERROR output)"
fi

# Тест 11: Большой файл
dd   if=/dev/zero of=in.txt bs=1M count=10 2>/dev/null
echo "ma" > search.txt
echo "mama" > replace.txt
./replace in.txt out.txt "$(cat search.txt)" "$(cat replace.txt)"
if [ $? -eq 0 ]; then
    echo "Passed: Test 11 (command line mode: large file handling)"
else
    echo "Failed: Test 11 (command line mode: large file handling)"
fi

# Режим stdin

# Тест 12: Базовая замена
echo -e "ma\nmama\nmama delala pelmeni\nya pokushal plotno" | ./replace > out.txt
echo -e "mamamama delala pelmeni\nya pokushal plotno" > expected.txt
compare_files out.txt expected.txt "Test 12 (stdin mode: basic replacement)"

# Тест 13: Прерывание ввода
echo -e "ma" | ./replace > out.txt
if grep -q "ERROR" out.txt; then
    echo "Passed: Test 13 (stdin mode: input interruption)"
else
    echo "Failed: Test 13 (stdin mode: input interruption)"
fi

# Тест 14: Пустой ввод
echo -n "" | ./replace > out.txt
if [ $? -eq 0 ] && grep -q "ERROR" out.txt; then
    echo "Passed: Test 14 (stdin mode: empty input)"
else
    echo "Failed: Test 14 (stdin mode: empty input)"
fi

# Режим справки

# Тест 15: Вывод справки
./replace -h > out.txt
if grep -q "Usage:" out.txt; then
    echo "Passed: Test 15 (help mode: display usage)"
else
    echo "Failed: Test 15 (help mode: display usage)"
fi