# Word Frequency Analysis with a Binary Search Tree

This program processes a text file to analyze and visualize the frequency of words using a **binary search tree (BST)** structure.

## 📌 Features
- **Word Frequency Counting**: Cleans and inserts words into a BST, tracking their frequency.
- **Tree Statistics**:
  - Calculates the total number of nodes and leaves.
  - Determines the tree height (maximum depth).
  - Computes the tree fullness as a percentage.
- **Tree Visualization**: Prints the hierarchical structure of the tree, including word frequencies and levels.
- **Case Insensitivity**: Automatically converts words to lowercase and removes punctuation.

## 🚀 How It Works
1. The program reads words from a text file (`text.txt`).
2. Each word is:
   - Cleaned of punctuation and converted to lowercase.
   - Inserted into the binary search tree or incremented in count if it already exists.
3. The tree is then:
   - Printed in sorted order (in-order traversal).
   - Visualized as a hierarchical tree structure.
   - Analyzed to compute statistics like node count, tree height, and fullness percentage.
