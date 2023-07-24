#!/bin/bash
contador=0
termina=1000
while [ $termina -ge $contador ]
do
  ./aoeu
  echo "\n"
  let contador=$contador+1
done
