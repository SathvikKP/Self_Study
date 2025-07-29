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

int Tree::height() const {
    int h = -1;
    TreeNode* node = this->root;
    if (!node) return h;
    std::stack<std::pair<TreeNode*, int>> S;
    S.push({node, 0});
    while (!S.empty()) {
        std::pair<TreeNode*, int> stackElement = S.top(); S.pop();
        node = stackElement.first; int curHeight = stackElement.second;
        if (curHeight > h) h = curHeight;
        if (node->left) S.push({node->left, curHeight + 1});
        if (node->right) S.push({node->right, curHeight + 1});
    }
    return h;
}

int Tree::heightRecursive(TreeNode* node) const {
    if (node == nullptr) return -1;
    return 1 + std::max(this->heightRecursive(node->left), this->heightRecursive(node->right));
}

int Tree::heightRecursive() const {
    return this->heightRecursive(this->root);
}


int Tree::inorderPredecessor(int val) const {
    int predecessor = INT_MAX;
    TreeNode* node = this->root;
    while (node) {
        if (node->val >= val) {
            node = node->left;
        } else {
            predecessor = node->val;
            node = node->right;
        }
    }
    if (predecessor == INT_MAX) {
        std::cout<<"No predecessor node found!"<<std::endl;
    }
    return predecessor;
}

int Tree::inorderSuccessor(int val) const {
    int successor = INT_MIN;
    TreeNode* node = this->root;
    while (node) {
        if (node->val <= val) {
            node = node->right;
        } else {
            successor = node->val;
            node = node->left;
        }
    }
    if (successor == INT_MIN) {
        std::cout<<"No successor node found"<<std::endl;
    }
    return successor;
}

int Tree::inorderPredecessorRecursive(TreeNode* node, int val, int& predecessor) const {
    if (!node) return predecessor;
    if (node->val >= val) {
        return this->inorderPredecessorRecursive(node->left, val, predecessor);
    } else {
        predecessor = node->val;
        return this->inorderPredecessorRecursive(node->right, val, predecessor);
    }
}

int Tree::inorderPredecessorRecursive(int val) const {
    int predecessor = INT_MAX;
    this->inorderPredecessorRecursive(this->root, val, predecessor);
    if (predecessor == INT_MAX) {
        std::cout<<"No predecessor node found!"<<std::endl;
    }
    return predecessor;
}

int Tree::inorderSuccessorRecursive(TreeNode* node, int val, int& successor) const {
    if (!node) return successor;
    if (node->val <= val) {
        return this->inorderSuccessorRecursive(node->right, val, successor);
    } else {
        successor = node->val;
        return this->inorderSuccessorRecursive(node->left, val, successor);
    }
}

int Tree::inorderSuccessorRecursive(int val) const {
    int successor = INT_MIN;
    this->inorderSuccessorRecursive(this->root, val, successor);
    if (successor == INT_MIN) {
        std::cout<<"No successor node found"<<std::endl;
    }
    return successor;
}

TreeNode* Tree::findSubtreePredecessor(TreeNode* node) const {
    if (!node || !node->left) return nullptr;
    TreeNode* current = node->left;
    while (current->right) {
        current = current->right;
    }
    return current;
}

TreeNode* Tree::findSubtreeSuccessor(TreeNode* node) const {
    if (!node || !node->right) return nullptr;
    TreeNode* current = node->right;
    while (current->left) {
        current = current->left;
    }
    return current;
}


TreeNode* Tree::findGlobalInorderPredecessor(TreeNode* node) const {
    if (node == nullptr) return nullptr;
    TreeNode* predecessor = nullptr, *current = this->root;
    while (current) {
        if (current->val >= node->val) {
            current = current->left;
        } else {
            predecessor = current;
            current = current->right;
        }
    }
    if (predecessor == nullptr) {
        std::cout<<"No predecessor found!"<<std::endl;
    }
    return predecessor;
}

TreeNode* Tree::findGlobalInorderSuccessor(TreeNode* node) const {
    if (node == nullptr) return nullptr;
    TreeNode* successor = nullptr, *current = this->root;
    while (current) {
        if (current->val <= node->val) {
            current = current->right;
        } else {
            successor = current;
            current = current->left;
        }
    }
    if (successor == nullptr) {
        std::cout<<"No successor found!"<<std::endl;
    }
    return successor;
}

