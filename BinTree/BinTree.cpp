// This program implements a binary search tree (BST) to process and analyze words from a text file.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // For isspace and ispunct
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;

class BinTree {
private:
    struct Node {
        string word; // Stores the word
        int count;   // Frequency of the word
        int level;   // Level of the node in the tree
        Node* left;  // Pointer to left child
        Node* right; // Pointer to right child

        // Node constructor initializes the word, count, and child pointers
        Node(const string& w, int lvl) : word(w), count(1), level(lvl), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr; // Root node of the tree
    
public:
    void insert(const string& word);    // Inserts a word into the tree
    void printTree() const;             // Prints all words and frequencies
    void calculateStats() const;        // Calculates and prints tree statistics
    void printBT() const;               // Prints a visual representation of the tree

private:
    void insert(Node*& node, const string& word, int level); // Recursive insert helper
    void printTree(Node* node) const;                        // Recursive print helper
    void calculateStats(Node* node, int& nodes, int& leaves, int level, int& maxLevel) const;
    void cleanWord(string& word);                            // Cleans a word
    void printBT(const string& prefix, const Node* node, bool isLeft) const; // Print for tree visualization
};

// Removes punctuation and converts a word to lowercase
void BinTree::cleanWord(string& word) {
    word.erase(remove_if(word.begin(), word.end(), [](char c) {
        return ispunct(c) || isspace(c);
    }), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

// Inserts a word into the binary tree, or increments count if it exists
void BinTree::insert(Node*& node, const string& word, int level) {
    if (!node) {
        node = new Node(word, level); // Create a new node if it doesn't exist
    } else if (word < node->word) {
        insert(node->left, word, level + 1); // Insert into the left subtree if word is smaller
    } else if (word > node->word) {
        insert(node->right, word, level + 1); // Insert into the right subtree if word is larger
    } else {
        node->count++; // Increment count if the word already exists
    }
}

// Inserts a cleaned word into the tree
void BinTree::insert(const string& word) {
    string cleanWordStr = word;
    cleanWord(cleanWordStr);
    if (!cleanWordStr.empty()) {
        insert(root, cleanWordStr, 1);  // Start at level 1 for the root
    }
}

// Prints the tree
void BinTree::printTree(Node* node) const {
    if (node) {
        printTree(node->left); // Left subtree
        cout << node->word << "(" << node->count << ") "; // Current node
        printTree(node->right); // Right subtree
    }
}

// Prints all words in the tree and their frequencies
void BinTree::printTree() const {
    if (!root) {
        cout << "Tree is empty" << endl;
    } else {
        printTree(root);
        cout << endl;
    }
}

// Method to calculate nodes, leaves, and maximum level
void BinTree::calculateStats(Node* node, int& nodes, int& leaves, int level, int& maxLevel) const {
    if (!node) return;
    nodes++; // Increment node count
    if (!node->left && !node->right) 
        leaves++; // Count leaves
    maxLevel = max(maxLevel, level); // Track the deepest level

    calculateStats(node->left, nodes, leaves, level + 1, maxLevel); // Left subtree
    calculateStats(node->right, nodes, leaves, level + 1, maxLevel); // Right subtree
}

// Calculates and displays the statistics for the tree
void BinTree::calculateStats() const {
    int nodes = 0, leaves = 0, maxLevel = 0;
    calculateStats(root, nodes, leaves, 1, maxLevel);

    cout << "\nTree statistics:\n";
    cout << "Number of leaves in the tree: " << leaves << endl;
    cout << "Number of nodes in the tree: " << nodes << endl;
    cout << "Tree height: " << maxLevel << endl;

    // Calculate and display tree fullness as a percentage
    double fullness = (static_cast<double>(nodes) / (pow(2, maxLevel) - 1)) * 100;
    cout << "Tree fullness (percentage): " << fixed << setprecision(2) << fullness << " %" << endl;
}

// Prints the tree structure in a visual format
void BinTree::printBT(const string& prefix, const Node* node, bool isLeft) const {
    if (node != nullptr) {
        cout << prefix << (isLeft ? "├── " : "└── ") << node->word << ": " << node->level << "-" << node->count << endl;
        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

// Prints the visual representation of the tree from the root
void BinTree::printBT() const {
    if (root) {
        printBT("", root, false);
    } else {
        cout << "Tree is empty\n";
    }
}

int main() {
    BinTree tree;
    ifstream file("text.txt");
    string word;

    cout << "\nPrinting tree keys before adding them:\n";
    tree.printTree();

    while (file >> word) {
        tree.insert(word);
    }

    cout << "\nPrinting tree keys after insertion:\n";
    tree.printTree();

    tree.calculateStats();

    cout << "\nTree visualization:\n" << endl;
    cout << "*Word: level-repetitions*\n" << endl;
    tree.printBT();

    cout << endl;
    return 0;
}