#!/bin/bash

if [ $# -lt 1 ];then
    echo "USAGE: ./scripts/runtests.sh [biraries folder] [memcheck(OPTIONAL)]"
fi

VALGRIND=""
TESTS_DIR=$1
TESTS=$(ls $TESTS_DIR/test_*)

if [ "$2" == "memcheck" ];then
    VALGRIND="valgrind -s"
fi

for test in $TESTS
do
    $VALGRIND $test
done