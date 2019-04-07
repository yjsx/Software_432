g++ -fprofile-arcs -ftest-coverage test.cpp -o a.out
chmod +x a.out
./a.out
gcov test.cpp
lcov -d . -t 'test_test' -o 'test_test.info' -b . -c
genhtml -o result test_test.info


