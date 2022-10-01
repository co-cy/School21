#!/bin/bash

if [[ $1 =~ ^[+-]?[0-9]+(\.([0-9]+)?)? ]]
then
  echo "error: string is a number!"
else
  echo "$1"
fi
