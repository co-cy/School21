#!/bin/bash

main() {
        local ip;

        echo "HOSTNAME = $(hostname)"
        echo "TIMEZONE = $(timedatectl status | grep "Time zone: " | awk '{print $3 $4 $5}' )"
        echo "USER = $(whoami)"
        echo "OS = $(lsb_release -d | awk -F"\t" '{print $2}')"
        echo "DATE = $(date +"%d %b %Y %T")"
        echo "UPTIME = $(uptime -p)"
        echo "UPTIME_SEC = $(awk '{print $1}' /proc/uptime)"
        ip=$(hostname -I | awk 'NR==1')
        echo "IP = $ip"
        echo "MASK = $(ifconfig | awk "/$ip/{print \$4}")"
        echo "GATEWAY = $(ip r | awk '/default via /{print $3}')"
        echo "RAM_TOTAL = $(free -m | awk '/Mem/{printf("%.3f GB", $2 / 1024)}')"
        echo "RAM_USED = $(free -m | awk '/Mem/{printf("%.3f GB", $3 / 1024)}')"
        echo "RAM_FREE = $(free -m | awk '/Mem/{printf("%.3f GB", $4 / 1024)}')"
        echo "SPACE_ROOT = $(df /root/ | awk '/dev/{printf("%.2f MB", $2 / 1024)}')"
        echo "SPACE_ROOT_USED = $(df /root/ | awk '/dev/{printf("%.2f MB", $3 / 1024)}')"
        echo "SPACE_ROOT_FREE = $(df /root/ | awk '/dev/{printf("%.2f MB", $4 / 1024)}')"
}

IFS=""
result=$(main)

echo "$result"
echo

read -rp "Записать в файл (Y/N):" input
if [[ $input =~ ^[Yy]$ ]]
then
        filename=$(date +"%d_%m_%y_%H_%M_%S.status")
        echo "$result" > "$filename"
        echo "Сохранено в файл: $filename"
else
        echo "No"
fi