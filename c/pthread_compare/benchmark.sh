#!/bin/bash

NUM_THREADS=$1
NUM_COUNTER=$2
EXECUTABLE="pthread_compare"
OUTPUT_FILE="output.txt"

compile_and_run() {
    OPTION=$1
    make $OPTION
    echo "Running with $OPTION..."
    ./pthread_compare $NUM_THREADS $NUM_COUNTER > temp_output.txt
    TIME=$(awk '{print $2}' temp_output.txt)
    RESULT=$(awk '{print $1}' temp_output.txt)
    echo "$OPTION time: $TIME", result: $RESULT >> $OUTPUT_FILE
}

if [ "$#" -ne 2 ]; then
    echo "Usage: ./compile_and_run.sh 'number of threads' 'number of counter'"
    exit 1
fi

rm -f $OUTPUT_FILE

compile_and_run "atomic"
compile_and_run "mutex"
compile_and_run "while"

rm -f temp_output.txt

echo "Compilation and run completed. Results are in $OUTPUT_FILE."

