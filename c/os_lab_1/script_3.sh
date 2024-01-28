#!/bin/sh

# Вывод переданных параметров
echo -e "first: $1\nsecond: $2\nthird: $3\nfoutrh: $4"

# Поиск максимального числа
if [ $1 -gt $2 ]; then
	max=$1
else
	max=$2
fi

if [ $3 -gt $max ]; then
	max=$3
fi

if [ $4 -gt $max ]; then
	max=$4
fi

echo "max: $max"
