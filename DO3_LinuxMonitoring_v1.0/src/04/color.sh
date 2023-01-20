#!/bin/bash

export WHITE_T="\033[97m"
export WHITE_B="\033[107m"
export RED_T="\033[91m"
export RED_B="\033[101m"
export GREEN_T="\033[92m"
export GREEN_B="\033[102m"
export BLUE_T="\033[96m"
export BLUE_B="\033[106m"
export PURPLE_T="\033[95m"
export PURPLE_B="\033[105m"
export BLACK_T="\033[30m"
export BLACK_B="\033[40m"
export COLOR_END="\033[0m"

color_b() { # color_id
  case $1 in
  1)echo "$WHITE_B";;
  2)echo "$RED_B";;
  3)echo "$GREEN_B";;
  4)echo "$BLUE_B";;
  5)echo "$PURPLE_B";;
  6)echo "$BLACK_B";;
  esac
}

color_t() { # color_id
  case $1 in
  1)echo "$WHITE_T";;
  2)echo "$RED_T";;
  3)echo "$GREEN_T";;
  4)echo "$BLUE_T";;
  5)echo "$PURPLE_T";;
  6)echo "$BLACK_T";;
  esac
}

color_n() { # color_id
  case $1 in
  1)echo "white";;
  2)echo "red";;
  3)echo "green";;
  4)echo "blue";;
  5)echo "purple";;
  6)echo "black";;
  esac
}

paint () {
  # input color_back, color_text, color_back, color_text, A, B
  echo -e "$(color_b "$1")$(color_t "$2")$5$COLOR_END = $(color_b "$3")$(color_t "$4")$6$COLOR_END"
}

export -f color_b
export -f color_t
export -f color_n
export -f paint