#!/bin/bash

path=${1/%"/"}

if [[ -d $path ]]
then
  path=$1
else
  echo "Not find Directory"
  exit
fi

IFS=$'\n'

get_time() {
  awk '{print $1}' /proc/uptime
}

start_time=$(get_time)
all_dir=$(du -h "$path")
all_files=$(find "$path" -type f -exec du -ha {} +)

echo "Общее число папок, включая вложенные: $(echo "${all_dir[@]}" | wc -l)"
echo "Топ 5 больших папок:"
echo "${all_dir[@]}" | sort -rh | head -n 5

echo "Всего файлов: $(echo "${all_files[@]}" | wc -l)"
echo "Конфигурационных файлов: $(echo "${all_files[@]}" | grep -ce "\.conf$")"
echo "Текстовых файлов: $(echo "${all_files[@]}" | grep -ce "\.txt$")"
exec_files=$(find "$path" -type f -executable -exec du -ha {} +)
echo "Исполняемых файлов: $(echo "${exec_files[@]}" | wc -l)"
echo "Логов: $(echo "${all_files[@]}" | grep -ce "\.log$")"
echo "Архивов: $(echo "${all_files[@]}" | grep -ce "\.zip$")"
echo "Символических ссылок: $(find "$path" -type l | wc -l)"

echo "Топ 10 больших файлов:"
tmp=$(echo "${all_files[@]}" | sort -rh | awk '{print(NR" - "$2"\t"$1)}' | head -n 10)
for i in $tmp
do
  echo "$i$(echo "$i" | awk '{print $3}' |awk -F"/" '{n=split($NF, a, "."); if (n > 1) print(", "a[n])}')"
done


echo "Топ 10 больших исполняемых файлов:"
tmp=$(echo "${exec_files[@]}" | sort -rh | awk '{print(NR" - "$2"\t"$1)}' | head -n 10)
for i in $tmp
do
  echo "$i, $(echo "$i" | awk '{print $3}' | md5sum |  awk '{print $1}')"
done
echo "Время выполнения скрипта: $(echo "$(get_time) - $start_time" | bc)"
