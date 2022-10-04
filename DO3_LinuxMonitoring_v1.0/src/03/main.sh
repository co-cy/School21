#!/bin/bash

N="^[1-6]$"
if [[ $# -eq 4 && $1 =~ $N && $2 =~ $N && $3 =~ $N && $4 =~ $N && $1 -ne $2 && $3 -ne $4 ]]
then
  source color.sh

  main() { # back_color, text_color, back_color, text_color
          local ip;

          paint "$@" "HOSTNAME" "$(hostname)"
          paint "$@" "TIMEZONE" "$(timedatectl status | grep "Time zone: " | awk '{print $3 $4 $5}' )"
          paint "$@" "USER" "$(whoami)"
          paint "$@" "OS" "$(lsb_release -d | awk -F"\t" '{print $2}')"
          paint "$@" "DATE" "$(date +"%d %b %Y %T")"
          paint "$@" "UPTIME" "$(uptime -p)"
          paint "$@" "UPTIME_SEC" "$(awk '{print $1}' /proc/uptime)"
          ip=$(hostname -I | awk 'NR==1')
          paint "$@" "IP" "$ip"
          paint "$@" "MASK" "$(ifconfig | awk "/$ip/{print \$4}")"
          paint "$@" "GATEWAY" "$(ip r | awk '/default via /{print $3}')"
          paint "$@" "RAM_TOTAL" "$(free -m | awk '/Mem/{printf("%.3f GB", $2 / 1024)}')"
          paint "$@" "RAM_USED" "$(free -m | awk '/Mem/{printf("%.3f GB", $3 / 1024)}')"
          paint "$@" "RAM_FREE" "$(free -m | awk '/Mem/{printf("%.3f GB", $4 / 1024)}')"
          paint "$@" "SPACE_ROOT" "$(df /root/ | awk '/dev/{printf("%.2f MB", $2 / 1024)}')"
          paint "$@" "SPACE_ROOT_USED" "$(df /root/ | awk '/dev/{printf("%.2f MB", $3 / 1024)}')"
          paint "$@" "SPACE_ROOT_FREE" "$(df /root/ | awk '/dev/{printf("%.2f MB", $4 / 1024)}')"
  }

  main "$1" "$2" "$3" "$4"
else
  echo "Wrong input"
fi