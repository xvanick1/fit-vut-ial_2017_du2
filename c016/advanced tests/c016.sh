#!/bin/sh

make clean

make

./c016-advanced-test >user.output

diff user.output c016-advanced-test.output >difffile

EMPTY=`cat difffile`

if [ -z "$EMPTY" ]; then
  echo "Prosel jsi testem"
  exit
fi

echo "Neprosel jsi testem, Vysledky v souboru difffile"


