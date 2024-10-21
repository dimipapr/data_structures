clear
tests=tests/bin/test*
if [[ $1 == "tests-only" ]]; then
    for test in $tests  
    do
        echo "####################################################################"
        echo "###############  $test"
        $test
        echo "####################################################################"
        read -p 'Press enter to continue:'
        clear
    done
else
    for test in $tests
    do
        echo "####################################################################"
        echo "###############  $test"
        valgrind --leak-check=full --show-leak-kinds=all -s $test
        echo "####################################################################"
        read -p 'Press enter to continue:'
        clear
    done
fi