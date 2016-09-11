#!/bin/bash

COUNTER=2
TEMPOEXECUCAO=0

if [ -f ./tempos.csv ]; then
    rm ./tempos.csv
fi
echo 'nthreads;tempo' >> tempos.csv

while [  $COUNTER -lt 17 ]; do
    TEMPOEXECUCAO="$(./knapsack $COUNTER < input | tail -1)"
    echo $COUNTER';'$TEMPOEXECUCAO >> tempos.csv 
    let COUNTER=COUNTER+1 
done