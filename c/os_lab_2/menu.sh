# Переменные для подсчета успешных и неуспешных попыток
successful_tries=0
unsuccsessful_tries=0

# Бесконечный вывод меню (до выхода)
while true; do
	echo "1. Создать файл"
	echo "2. Удалить файл"
	echo "3. Выход"

	read -p "Введите номер пункта меню: " choice

	case $choice in
		1 | 2)
			read -p "Введите имя файла: " file_name

			if [ $choice -eq 1 ]; then
				./create_file "$file_name"
			elif [ $choice -eq 2 ]; then
				./delete_file "$file_name"
			fi
			
			if [ $? -eq 0 ]; then
				((successful_tries++))
			else
				((unsuccsessful_tries++))
			fi
			;;
		3)
			echo "Удачно: $successful_tries"
			echo "Неудачно: $unsuccsessful_tries"
			exit 0
			;;
		*)
			echo "Такого пункта нет в меню"
			;;
	esac

done
