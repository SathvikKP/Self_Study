#include "bst/bst.h"
#include <iostream>

// Forward declaration
void test_bst_simple();
void test_bst_simple_recursive();

int main() {
    try {
        test_bst_simple();
        test_bst_simple_recursive();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // Optionally, cleanup code here
    }
    return 0;
}