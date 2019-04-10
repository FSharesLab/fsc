#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./clfsc.sh
# Run single cmd:  sudo ./clfsc.sh <clfsc paramers>

PREFIX="docker-compose exec nodfscd clfsc"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "clfsc " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX "$@"
fi
