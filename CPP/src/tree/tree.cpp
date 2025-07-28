#include "tree/tree.h"


// TreeNode implementation
TreeNode::TreeNode(int val) {
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}

// Faster constructor --> TreeNode::TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
// Example of faster constructor below 
Tree::Tree() : root(nullptr) {}


// Destructor explicit for base class - derived class shenenigans --> polymorphism
Tree::~Tree() {}

void Tree::inorder() const {
    TreeNode* node = this->root;
    std::stack<TreeNode*> S;
    while (!S.empty() || node) {
        while (node) {
            S.push(node);
            node = node->left;
        }
        node = S.top(); S.pop();
        std::cout << node->val << " ";
        node = node->right;
    }
}

void Tree::inorderRecursive(TreeNode* node) const {
    if (!node) return;
    this->inorderRecursive(node->left);
    std::cout << node->val << " ";
    this->inorderRecursive(node->right);
}

void Tree::inorderRecursive() const {
    this->inorderRecursive(root);
}

void Tree::preorder() const {
    TreeNode* node = this->root;
    std::stack<TreeNode*> S;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); S.pop();
        std::cout<<node->val<<" ";
        if (node->right) S.push(node->right);
        if (node->left) S.push(node->left);
    }
}

void Tree::preorderRecursive(TreeNode* node) const {
    if (!node) return;
    std::cout<<node->val<<" ";
    this->preorderRecursive(node->left);
    this->preorderRecursive(node->right);
}

void Tree::preorderRecursive() const {
    this->preorderRecursive(this->root);
}


void Tree::postorder() const {
    TreeNode* node = root;
    //if (!node) return;
    std::stack<std::pair<TreeNode*, bool>> S;

    while (!S.empty() || node) {
        while (node) {
            S.push({node, false});
            node = node->left;
        }
        std::pair<TreeNode*, bool> stackElement = S.top(); S.pop();
        node = stackElement.first; bool processed = stackElement.second;
        if (processed == false) {
            S.push({node, true});
            node = node->right;
        } else {
            std::cout<<node->val<<" ";
            node = nullptr; // VERY IMPORTANT
        }
    }

    /* Alternate Approach */

    /*
    std::stack<TreeNode*> s;
    TreeNode* node = root;
    TreeNode* lastVisited = nullptr;

    while (!s.empty() || node) {
        // Traverse left subtree
        while (node) {
            s.push(node);
            node = node->left;
        }

        // Peek at top node
        node = s.top();

        // If right child exists and hasn't been visited, go to right
        if (node->right && node->right != lastVisited) {
            node = node->right;
        } else {
            // Print node value and mark as visited
            std::cout << node->val << " ";
            lastVisited = node;
            s.pop();
            node = nullptr;
        }
    }
    
    */
}


void Tree::postorderRecursive(TreeNode* node) const {
    if (!node) return;
    this->postorderRecursive(node->left);
    this->postorderRecursive(node->right);
    std::cout<<node->val<<" ";
}

void Tree::postorderRecursive() const {
    this->postorderRecursive(this->root);
}


void Tree::display() const {
    std::cout << "Inorder traversal: ";
    this->inorder();
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    this->preorder();
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    this->postorder();
    std::cout << std::endl; 
}

void Tree::displayRecursive() const {
    std::cout << "Inorder traversal (recursive): ";
    this->inorderRecursive();
    std::cout << std::endl;

    std::cout << "Preorder traversal (recursive): ";
    this->preorderRecursive();
    std::cout << std::endl;

    std::cout << "Postorder traversal (recursive): ";
    this->postorderRecursive();
    std::cout << std::endl;
}