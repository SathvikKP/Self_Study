#include "utils/utils.h"
#include "bst/bst.h"
#include <iostream>
#include <vector>
#include <limits>

void test_bst_simple() {
    BST bst;
    std::vector<int> values = readIntegersFromFile("inputs/bst_input_1.txt");
    for (int v : values) {
        bst.insert(v);
    }
    
    bst.display();

    std::cout << "Enter values to search (press Enter without input to stop):" << std::endl;
    while (true) {
        std::cout << "Value to search: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) break;
        try {
            int query = std::stoi(input);
            std::cout << "Searching for " << query << ": ";
            if (bst.search(query))
                std::cout << "Found!" << std::endl;
            else
                std::cout << "Not found!" << std::endl;
        } catch (...) {
            std::cout << "Invalid input. Stopping search." << std::endl;
            break;
        }
    }
}

void test_bst_simple_recursive() {
    BST bst;
    std::vector<int> values = readIntegersFromFile("inputs/bst_input_1.txt");
    for (int v : values) {
        bst.insertRecursive(v);
    }

    bst.displayRecursive();

    std::cout << "Enter values to search recursively (press Enter without input to stop):" << std::endl;
    while (true) {
        std::cout << "Value to search: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) break;
        try {
            int query = std::stoi(input);
            std::cout << "Searching for " << query << ": ";
            if (bst.searchRecursive(query))
                std::cout << "Found!" << std::endl;
            else
                std::cout << "Not found!" << std::endl;
        } catch (...) {
            std::cout << "Invalid input. Stopping search." << std::endl;
            break;
        }
    }
}

void test_bst_inorder_pred_succ() {
    BST bst;
    /*
    // Construct a tree:
    //         20
    //       /    \
    //     10      30
    //    /  \    /  \
    //   5   15  25  35
    //  / \    \
    // 2   7   17
    */
    std::vector<int> values = {20, 10, 30, 5, 15, 25, 35, 2, 7, 17};
    for (int v : values) bst.insert(v);

    bst.display();

    std::vector<int> test_vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 17, 100, 1, 16};

    std::cout << "\nTesting inorder predecessor and successor (iterative and recursive):\n";
    for (int v : test_vals) {
        std::cout<<"Inorder display : "; bst.inorder(); std::cout<<std::endl;
        std::cout << "Value: " << v << "\n";
        int pred_iter = bst.inorderPredecessor(v);
        int pred_rec  = bst.inorderPredecessorRecursive(v);
        int succ_iter = bst.inorderSuccessor(v);
        int succ_rec  = bst.inorderSuccessorRecursive(v);

        std::cout << "  Iterative predecessor: ";
        if (pred_iter == INT_MAX) std::cout << "None";
        else std::cout << pred_iter;
        std::cout << "\n";

        std::cout << "  Recursive predecessor: ";
        if (pred_rec == INT_MAX) std::cout << "None";
        else std::cout << pred_rec;
        std::cout << "\n";

        std::cout << "  Iterative successor: ";
        if (succ_iter == INT_MIN) std::cout << "None";
        else std::cout << succ_iter;
        std::cout << "\n";

        std::cout << "  Recursive successor: ";
        if (succ_rec == INT_MIN) std::cout << "None";
        else std::cout << succ_rec;
        std::cout << "\n";
    }
}

void test_bst_delete() {
    BST bst;
    /*
    // Build a comprehensive tree:
    //         20
    //       /    \
    //     10      30
    //    /  \    /  \
    //   5   15  25  35
    //  / \    \
    // 2   7   17
    */
    std::vector<int> values = {20, 10, 30, 5, 15, 25, 35, 2, 7, 17};
    for (int v : values) bst.insert(v);

    std::cout << "Initial tree (inorder): ";
    bst.inorder();
    std::cout << "\n";

    // Nodes to delete: leaf, one child, two children, root, min, max, not present
    std::vector<int> to_delete = {
        2,    // leaf
        5,    // one child (after 2 is deleted, 5 has only right child 7)
        10,   // two children
        20,   // root (two children)
        35,   // max (leaf)
        25,   // one child (after 35 is deleted, 25 has no right child)
        100,  // not present
        7,    // leaf
        15,   // one child (after 17 is deleted, 15 has no right child)
        17    // leaf
    };

    for (int v : to_delete) {
        std::cout << "\nDeleting " << v << "...\n";
        bst.removeRecursive(v);
        std::cout << "Tree (inorder): ";
        bst.inorder();
        std::cout << "\n";
        std::cout << "Searching for " << v << ": ";
        if (bst.search(v)) std::cout << "Still present (error!)\n";
        else std::cout << "Not found (correct)\n";
    }
}