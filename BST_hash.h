#pragma once 

#include "hash.h"
#include <vector>
#include <memory>
#include <iostream>

// Node structure for the Binary Search Tree
template <class T>
struct BSTNode {
    T data;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

// BST class
template <class T>
class BST {
public:
    std::unique_ptr<BSTNode<T>> root;

    BST() : root(nullptr) {}

    // Insert a new value into the BST
    void insert(T value) {
        root = insertNode(std::move(root), value);
    }

    // Search for a value in the BST
    bool search(T value) {
        return searchNode(root.get(), value);
    }

    // Print the BST in-order
    void print() {
        printInOrder(root.get());
        std::cout << std::endl;
    }

private:
    // Helper to insert a node into the BST
    std::unique_ptr<BSTNode<T>> insertNode(std::unique_ptr<BSTNode<T>> node, T value) {
        if (!node) return std::make_unique<BSTNode<T>>(value);

        if (value < node->data) {
            node->left = insertNode(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insertNode(std::move(node->right), value);
        }
        return node;
    }

    // Helper to search for a node in the BST
    bool searchNode(BSTNode<T>* node, T value) {
        if (!node) return false;
        if (node->data == value) return true;

        if (value < node->data) {
            return searchNode(node->left.get(), value);
        } else {
            return searchNode(node->right.get(), value);
        }
    }

    // Helper to print BST in-order
    void printInOrder(BSTNode<T>* node) {
        if (!node) return;
        printInOrder(node->left.get());
        std::cout << node->data << " ";
        printInOrder(node->right.get());
    }
};

// Hash table with BST chaining
template <class T, size_t SIZE>
class Hash_BST : public Hash<T, SIZE> {
private:
    std::vector<BST<T>> table;

    // Hash function
    size_t hashFunction(T key) const {
        return std::hash<T>{}(key) % SIZE;
    }

public:
    Hash_BST() : table(SIZE) {}

    // Insert into the hash table
    void insert(T new_data) override {
        size_t index = hashFunction(new_data);
        table[index].insert(new_data);
    }

    // Search in the hash table
    bool search(T key) override {
        size_t index = hashFunction(key);
        return table[index].search(key);
    }

    // Print the hash table
    void print() override {
        for (size_t i = 0; i < SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            table[i].print();
        }
    }
};