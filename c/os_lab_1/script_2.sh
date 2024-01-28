#!/bin/sh

# Вывод переданных параметров
echo -e "first: $1\nsecond: $2"

# Поиск максимального числа
if [ $1 -gt $2 ]; then
	max=$1
else
	max=$2
fi

echo "max: $max"
