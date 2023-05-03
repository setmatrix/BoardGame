#include <cassert>

void test_pass() {
    assert(0 == 0);
}

void test_fail() {
    assert(1 == 0);
}

void test_fail_valgrind() {
    int *x = new int[100];
}