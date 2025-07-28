#pragma once
#include <stack>
#include <iostream>
#include <utility>

// Standalone TreeNode class
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val);
};

class Tree {
protected:
    TreeNode* root;
public:
    Tree();
    virtual ~Tree(); // needed for base class pointer - polymorphism etc

    // Traversals
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void display() const;

    void inorderRecursive() const;
    void preorderRecursive() const;
    void postorderRecursive() const;
    void displayRecursive() const;

protected:
    // Recursive helpers
    void inorderRecursive(TreeNode* node) const;
    void preorderRecursive(TreeNode* node) const;
    void postorderRecursive(TreeNode* node) const;
};