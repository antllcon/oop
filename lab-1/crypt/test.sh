#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

PROGRAM="./start"

writeTestSuccess() {
  echo -e "${GREEN}Test passed${NC}"
}

writeTestError() {  
  echo -e "${RED}Test failed${NC}"
}

writeAssert() {
  echo -e "${GREEN}File eq${NC}"
}

writeAssertError() {  
  echo -e "${RED}File no eq${NC}"
}


MAX_VALID_KEY=255
MIN_VALID_KEY=0
VALID_KEY=24
INVALID_HEX_KEY=4A
TOO_LARGE_KEY=256
TOO_SMALL_KEY=-1

assert_files_equal() {
  if cmp -s "$1" "$2"; then
    writeAssert 
  else
    writeAssertError
    exit 1
  fi
}

echo "1. Несуществующий файл"
"$PROGRAM" crypt tests/non-exist output/closed $MAX_VALID_KEY &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError 

echo "2. Неверное число аргументов"
"$PROGRAM" crypt tests/non-exist output/closed &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError 

echo "3. Некорректный ключ (hex)"
"$PROGRAM" crypt tests/line output/one-line-cripted $INVALID_HEX_KEY &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError 

echo "4. Ключ > 255"
"$PROGRAM" crypt tests/line output/one-line-cripted $TOO_LARGE_KEY &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError 

echo "5. Ключ < 0"
"$PROGRAM" crypt tests/line output/one-line-cripted $TOO_SMALL_KEY &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError 
echo "6. Неверная команда"
"$PROGRAM" ivalid-action tests/line output/one-line-cripted $VALID_KEY &>/dev/null
[ $? -eq 1 ] && writeTestSuccess || writeTestError

echo "7. Корректный ключ (24)"
"$PROGRAM" crypt tests/line output/one-line-cripted $VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess
  "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $VALID_KEY &>/dev/null
  assert_files_equal tests/line output/one-line-decripted
else
  writeTestError
fi

echo "8. Максимальный ключ (255)"
"$PROGRAM" crypt tests/line output/one-line-cripted $MAX_VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess
  "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $MAX_VALID_KEY &>/dev/null
  assert_files_equal tests/line output/one-line-decripted
else
  writeTestError
fi

echo "9. Минимальный ключ (0)"
"$PROGRAM" crypt tests/line output/one-line-cripted $MIN_VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess 
  "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $MIN_VALID_KEY &>/dev/null
  assert_files_equal tests/line output/one-line-decripted
else
  writeTestError
fi

echo "10. Пустой файл"
"$PROGRAM" crypt tests/empty output/empty-file-cripted $VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess
  "$PROGRAM" decrypt output/empty-file-cripted output/empty-file-decripted $VALID_KEY &>/dev/null
  assert_files_equal tests/empty output/empty-file-decripted
else
  writeTestError 
fi

echo "11. Многострочный файл"
"$PROGRAM" crypt tests/poem output/lots-of-lines-cripted $VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess
  "$PROGRAM" decrypt output/lots-of-lines-cripted output/lots-of-lines-decripted $VALID_KEY &>/dev/null
  assert_files_equal tests/poem output/lots-of-lines-decripted
else
  writeTestError
fi

echo "11. Тест самой программы"
"$PROGRAM" crypt tests/program output/lots-of-lines-cripted $VALID_KEY &>/dev/null
if [ $? -eq 0 ]; then
  writeTestSuccess
  "$PROGRAM" decrypt output/lots-of-lines-cripted output/lots-of-lines-decripted $VALID_KEY &>/dev/null
  assert_files_equal tests/program output/lots-of-lines-decripted
else
  writeTestError
fi


echo -e "${GREEN}Все тесты завершены!${NC}"