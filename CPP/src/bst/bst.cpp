#include "bst/bst.h"
#include <stack>
#include <iostream>
// Implement BST methods here

BST::BST() {
    this->root = nullptr;
}

void BST::insert(int val) {
    if ((this->root) == nullptr) {
        TreeNode* newNode = new TreeNode(val);
        this->root = newNode; 
        return;
    }
    TreeNode* node = this->root, *trail = nullptr;
    while (node) {
        trail = node;
        if (node->val == val) {
            return; // val already exists
        } else if (node->val > val) {
            node = node->left;
        } else if (node->val < val) {
            node = node->right;
        }
    }
    TreeNode* newNode = new TreeNode(val);
    if (trail->val > val) {
        trail->left = newNode;
    } else {
        trail->right = newNode;
    }
}


void BST::insertRecursive(TreeNode*& node, int val) {
    if (node == nullptr) {
        TreeNode* newNode = new TreeNode(val);
        node = newNode; return;
    } else if (node->val == val) {
        return;
    } else if (node->val < val) {
        this->insertRecursive(node->right, val);
    } else if (node->val > val) {
        this->insertRecursive(node->left, val);
    }
}

void BST::insertRecursive(int val) {
    this->insertRecursive(this->root, val);
}


bool BST::search(int val) const {
    TreeNode* node = this->root;
    while (node) {
        if (node->val == val) return true;
        else if (node->val < val) node = node->right;
        else if (node->val > val) node = node->left;
    }
    return false;
}

bool BST::searchRecursive(TreeNode* node, int val) const {
    if (node == nullptr) return false;
    if (node->val == val) return true;
    if (node->val < val) return this->searchRecursive(node->right, val);
    else return this->searchRecursive(node->left, val);
}

bool BST::searchRecursive(int val) const {
    return this->searchRecursive(this->root, val);
}

