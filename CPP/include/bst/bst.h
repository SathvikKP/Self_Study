#pragma once
#include "tree/tree.h"

class BST : public Tree {
private:
    // BST-specific recursive helpers
    void insertRecursive(TreeNode*& node, int val);
    bool searchRecursive(TreeNode* node, int val) const;
    TreeNode* removeRecursive(TreeNode* node, int val);

public:
    BST();
    //~BST();

    // Iterative versions (default)
    void insert(int val);
    bool search(int val) const;
    void remove(int val);

    // Recursive versions
    void insertRecursive(int val);
    bool searchRecursive(int val) const;
    void removeRecursive(int val);
};