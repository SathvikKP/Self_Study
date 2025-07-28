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