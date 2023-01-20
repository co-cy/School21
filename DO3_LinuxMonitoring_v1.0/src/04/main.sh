#!/bin/bash

source parse_conf.sh
source color.sh

main() { # back_color, text_color, back_color, text_color
  if [[ $1 == "default" ]];
  then back_color=6; else back_color=$1; fi
  if [[ $2 == "default" ]];
  then text_color=1; else text_color=$2; fi
  if [[ $3 == "default" ]];
  then back2_color=1; else back2_color=$3; fi
  if [[ $4 == "default" ]];
  then text2_color=1; else text2_color=$4; fi

  local color;
  color=("$back_color" "$text_color" "$back2_color" "$text2_color")

  local ip;
  paint "${color[@]}" "HOSTNAME" "$(hostname)"
  paint "${color[@]}" "TIMEZONE" "$(timedatectl status | grep "Time zone: " | awk '{print $3 $4 $5}' )"
  paint "${color[@]}" "USER" "$(whoami)"
  paint "${color[@]}" "OS" "$(lsb_release -d | awk -F"\t" '{print $2}')"
  paint "${color[@]}" "DATE" "$(date +"%d %b %Y %T")"
  paint "${color[@]}" "UPTIME" "$(uptime -p)"
  paint "${color[@]}" "UPTIME_SEC" "$(awk '{print $1}' /proc/uptime)"
  ip=$(hostname -I | awk 'NR==1')
  paint "${color[@]}" "IP" "$ip"
  paint "${color[@]}" "MASK" "$(ifconfig | awk "/$ip/{print \$4}")"
  paint "${color[@]}" "GATEWAY" "$(ip r | awk '/default via /{print $3}')"
  paint "${color[@]}" "RAM_TOTAL" "$(free -m | awk '/Mem/{printf("%.3f GB", $2 / 1024)}')"
  paint "${color[@]}" "RAM_USED" "$(free -m | awk '/Mem/{printf("%.3f GB", $3 / 1024)}')"
  paint "${color[@]}" "RAM_FREE" "$(free -m | awk '/Mem/{printf("%.3f GB", $4 / 1024)}')"
  paint "${color[@]}" "SPACE_ROOT" "$(df /root/ | awk '/dev/{printf("%.2f MB", $2 / 1024)}')"
  paint "${color[@]}" "SPACE_ROOT_USED" "$(df /root/ | awk '/dev/{printf("%.2f MB", $3 / 1024)}')"
  paint "${color[@]}" "SPACE_ROOT_FREE" "$(df /root/ | awk '/dev/{printf("%.2f MB", $4 / 1024)}')"

  echo
  echo "Column 1 background = $1 ($(color_n "$back_color"))"
  echo "Column 1 font color = $2 ($(color_n "$text_color"))"
  echo "Column 2 background = $3 ($(color_n "$back2_color"))"
  echo "Column 2 font color = $4 ($(color_n "$text2_color"))"
}

read -ra input < <(parse_conf "color.conf")
main "${input[@]}"
