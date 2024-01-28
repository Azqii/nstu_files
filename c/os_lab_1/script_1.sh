#!/bin/sh

# Вывод наименования скрипта и двух переданных аргументов (строк)
echo $0
echo $1
echo $2

# Вывод информации о том, равны ли строки
if [ $1 = $2 ]; then
	echo "Strings are equal"
else
	echo "String are NOT equal"
fi

