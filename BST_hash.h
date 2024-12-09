#pragma once 

#include "hash.h"
#include <vector>
#include <memory>
#include <iostream>

// Binary Search Tree Node
template <class T>
struct BSTNode {
    T data;
    std::shared_ptr<BSTNode> left;
    std::shared_ptr<BSTNode> right;

    BSTNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
template <class T>
class BST {
    std::shared_ptr<BSTNode<T>> root;

    void insertNode(std::shared_ptr<BSTNode<T>>& node, T val) {
        if (!node) {
            node = std::make_shared<BSTNode<T>>(val);
        } else if (val < node->data) {
            insertNode(node->left, val);
        } else if (val > node->data) {
            insertNode(node->right, val);
        }
    }

    bool searchNode(std::shared_ptr<BSTNode<T>> node, T val) const {
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return searchNode(node->left, val);
        return searchNode(node->right, val);
    }

    void printNode(std::shared_ptr<BSTNode<T>> node, int level = 0) const {
        if (!node) return;
        printNode(node->right, level + 1);
        std::cout << std::string(level * 4, ' ') << node->data << "\n";
        printNode(node->left, level + 1);
    }

public:
    BST() : root(nullptr) {}

    void insert(T val) { insertNode(root, val); }

    bool search(T val) const { return searchNode(root, val); }

    void print() const { printNode(root); }
};

// Hash Table with BST chaining
template <class T, size_t SIZE>
class Hash_BST : public Hash<T, SIZE> {
    std::vector<BST<T>> table;

    size_t hashFunction(T key) const {
        return std::hash<T>{}(key) % SIZE;
    }

public:
    Hash_BST() : table(SIZE) {}

    void insert(T new_data) override {
        size_t index = hashFunction(new_data);
        table.at(index).insert(new_data);
        if (DEBUG) std::cerr << "(+) Inserted " << new_data << " into bucket " << index << "\n";
    }

    bool search(T key) override {
        size_t index = hashFunction(key);
        bool found = table.at(index).search(key);
        if (DEBUG) std::cerr << "(?) Searching for " << key << " in bucket " << index << ": " << (found ? "Found" : "Not Found") << "\n";
        return found;
    }

    void print() override {
        std::cout << "Hash Table with BST Chaining:\n";
        for (size_t i = 0; i < SIZE; i++) {
            std::cout << "Bucket " << i << ":\n";
            table.at(i).print();
            std::cout << "\n";
        }
    }
};
/*#pragma once

#include "hash.h"

// refer to the following files to figure out how to implement a hash table with BST chaining
// - old_hash.h, near the lower part of the file. uses standard BST <set>, but we need to make our own
// - hash.h.
// - LP_hash.h, for how to understand this syntax and this STATUS stuff
//		- but basically assume all datatypes are T, and use size_t for size etc.
//		- in a BST, we probably don't need status. in collisions, first addr checked has the data,
//			so you just add it to the bst and move on
template <class T, size_t SIZE>
class Hash_BST : public Hash<T, SIZE> {
	enum class STATUS : char {OPEN, FILLED};

public:
	std::vector<T> data;
	std::vector<STATUS> status;

	Hash_BST() {}

	void insert(T new_data) {}

	bool search(T key) { return false; }

	void print() {}
};
*/