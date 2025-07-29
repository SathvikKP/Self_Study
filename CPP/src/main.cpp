#include "bst/bst.h"
#include <iostream>

// Forward declaration
void test_bst_simple();
void test_bst_simple_recursive();
void test_bst_inorder_pred_succ();
void test_bst_delete();

int main() {
    try {
        //test_bst_simple();
        //test_bst_simple_recursive();
        //test_bst_inorder_pred_succ();
        test_bst_delete();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // Optionally, cleanup code here
    }
    return 0;
}