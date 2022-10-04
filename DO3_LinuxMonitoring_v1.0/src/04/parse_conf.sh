#!/bin/bash


parse_conf() { # filename
  col1_back="default"
  col1_text="default"
  col2_back="default"
  col2_text="default"

  IFS=$'\n'
  while read -r line; do
    if [[ $line =~ ^column1_background=[1-6]$ ]]; then
      col1_back=$(echo "$line" | awk -F"=" '{print $2}')
    elif [[ $line =~ ^column1_font_color=[1-6]$ ]]; then
      col1_text=$(echo "$line" | awk -F"=" '{print $2}')
    elif [[ $line =~ ^column2_background=[1-6]$ ]]; then
      col2_back=$(echo "$line" | awk -F"=" '{print $2}')
    elif [[ $line =~ ^column2_font_color=[1-6]$ ]]; then
      col2_text=$(echo "$line" | awk -F"=" '{print $2}')
    fi
  done < "$1"

  echo "$col1_back" "$col1_text" "$col2_back" "$col2_text"
}

export -f parse_conf