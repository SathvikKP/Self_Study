#pragma once
#include <stack>
#include <iostream>
#include <utility>
#include <climits> // For INT_MAX and INT_MIN

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

    int height() const; 
    int heightRecursive() const;

    // Returns INT_MAX if predecessor not found, INT_MIN if successor not found
    int inorderPredecessor(int val) const;           // Iterative
    int inorderPredecessorRecursive(int val) const;  // Recursive

    int inorderSuccessor(int val) const;             // Iterative
    int inorderSuccessorRecursive(int val) const;    // Recursive

protected:
    // Recursive helpers
    void inorderRecursive(TreeNode* node) const;
    void preorderRecursive(TreeNode* node) const;
    void postorderRecursive(TreeNode* node) const;

    int heightRecursive(TreeNode* node) const;
    int inorderPredecessorRecursive(TreeNode* node, int val, int& predecessor) const;
    int inorderSuccessorRecursive(TreeNode* node, int val, int& successor) const;

    TreeNode* findSubtreePredecessor(TreeNode* node) const;
    TreeNode* findSubtreeSuccessor(TreeNode* node) const;
    TreeNode* findGlobalInorderPredecessor(TreeNode* node) const;
    TreeNode* findGlobalInorderSuccessor(TreeNode* node) const;
};