#pragma once

#include <iostream>

// node structure for the linked list
template <class T>
struct Node {
	T data;
	Node* next;

	Node(T val) : data(val), next(nullptr) {}
};

// linked list class
template <class T>
class LinkedList {
public:
	Node<T>* head;
	
	// constructor
	LinkedList() : head(nullptr) {}

	// insert a new element if it doesn't already exist
	void insert(T new_data) {
		//if (search(new_data)) return; // if it exists, do nothing

		Node<T>* newNode = new Node<T>(new_data);
		newNode->next = head;
		head = newNode;
	}

	// search for an element
	bool search(T test_data) const {
		Node<T>* current = head;
		while (current) {
			if (current->data == test_data)
				return true;
			current = current->next;
		}
		return false;
	}

	// for debugging: print the contents of the list
	void print() const {
		Node<T>* current = head;
		while (current) {
			std::cout << current->data << " -> ";
			current = current->next;
		}
		std::cout << "nullptr\n";
	}
};


