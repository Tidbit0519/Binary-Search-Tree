#include <iostream>
#include <fstream>
#include <sstream>
#include "Node.h"

using namespace std;
Node* root = nullptr;

// Performs a inorder traversal of the BST, printing the nodes' values as they are visited.
void inorderTreeWalk(Node* n) {
    if (n != nullptr) {
        cout << n->key << " ";
        inorderTreeWalk(n->left);
        inorderTreeWalk(n->right);
    }
}

// Performs a preorder traversal of the BST, printing the nodes' values as they are visited.
void preorderTreeWalk(Node* n) {
    if (n != nullptr) {
        preorderTreeWalk(n->left);
        cout << n->key << " ";
        preorderTreeWalk(n->right);
    }
}

// // Performs a postorder traversal of the BST, printing the nodes' values as they are visited.
void postorderTreeWalk(Node* n) {
    if (n != nullptr) {
        postorderTreeWalk(n->left);
        postorderTreeWalk(n->right);
        cout << n->key << " ";
    }
}

// TREE-INSERT. Inserting new nodes into the tree.
void treeInsert(Node* n) {
    Node* r = root;
    Node* p = nullptr;
    while (r != nullptr) {
        p = r;
        if (n->key < r->key) {
            r = r->left;
        }
        else {
            r = r->right;
        }
    }
    n->parent = p;
    // when root node is null
    if (p == nullptr) {
        root = n;
    }
    else if (n->key < p->key) {
        p->left = n;
    }
    else {
        p->right = n;
    }
}

// ITERATIVE-TREE-SEARCH
// Searches the BST for n, starting at the root.
// Prints out each node's value as it searches.
Node* iterativeTreeSearch(Node* x, int k) {
    if (root != nullptr) {
        cout << root->key << " ";
    }
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left;
            if (x != nullptr) {
                cout << x->key << " ";
            }
        }
        else if (k > x->key) {
            x = x->right;
            if (x != nullptr) {
                cout << x->key << " ";
            }
        }
    }
    return x;
}

// Delete all the nodes from the BST.
void clearTree(Node* n) {
    if (n != nullptr) {
        clearTree(n->left);
        clearTree(n->right);
        delete n;
    }
}

int main(int argc, char** argv) {
    // handles missing command - line parameters and "file-not-found" errors.
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // checks the first line of the file to determine how many lines will follow.
    // getline gets the first line from the ifstream and stores it into a string variable
    string firstLine;
    getline(ifs, firstLine);
    // Convert firstLine into an int
    int numLines = stoi(firstLine);

    string instruction;
    string number;
    int key;

    for (int i = 0; i < numLines; i++)
    {
        // Read instructions
        string nextLine;
        getline(ifs, nextLine);
        stringstream ss(nextLine);
        ss >> instruction >> number;

        // prints out the name of each node as it is ADDed
        if (instruction == "ADD") {
            cout << "Adding " << number << endl;
            key = stoi(number);
            Node* n = new Node(key);
            treeInsert(n);
        }
        else if (instruction == "FIND") {
            cout << "Looking for " << number << "... ";
            key = stoi(number);
            Node* result = iterativeTreeSearch(root, key);
            // If found, print "found". Otherwise print not found.
            if (result == nullptr) {
                cout << " : not found" << endl;
            }
            else {
                cout << " : found" << endl;
            }
        }
        else if (instruction == "INORDER") {
            cout << "INORDER: ";
            preorderTreeWalk(root);
            cout << endl;
        }
        else if (instruction == "PREORDER") {
            cout << "PREORDER: ";
            inorderTreeWalk(root);
            cout << endl;
        }
        else if (instruction == "POSTORDER") {
            cout << "POSTORDER: ";
           postorderTreeWalk(root);
           cout << endl;
        }
        else if (instruction == "CLEAR") {
            clearTree(root);
            root = nullptr;
            cout << "(tree deleted!)" << endl;
        }
        
        // Resets the variable for the next instruction
        instruction = "";
        number = "";
        key = 0;
    }
}