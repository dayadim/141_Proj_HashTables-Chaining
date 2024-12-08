#pragma once

#include "hash.h"
#include "linkedList.h"

template <class T, size_t SIZE>
class Hash_LL : public Hash<T, SIZE> {
	//enum class STATUS : char {OPEN, FILLED};

	// hash function. dc what it does
	std::hash<T> hash;

public:
	//"data" is a misnomer. it's really a vector of linked lists
	// each vector element is a linked list/bucket
	std::vector<LinkedList<T>> data;
	//std::vector<STATUS> status;	//we don't need states for chaining

	Hash_LL() {
		//set the vector to be size SIZE that is passed in on initialization
		data.resize(SIZE);
	}

	void insert(T new_data) {
		//get address 
		size_t addr = hash(new_data) % SIZE;
		
		//insert at the front of the linked list at the hashed address
		data.at(addr).insert(new_data);
		
		if (DEBUG) std::cerr << "(+) inserted " << new_data << " at list at " << addr << "\n";
	}

	bool search(T key) {
		size_t addr = hash(key) % SIZE;

		// Access the linked list at the hashed address
		Node<T>* current = data.at(addr).head; // Access the head node of the linked list
		while (current) {
			// If the key matches an item in the list, return true
			if (current->data == key) {
				if (DEBUG) std::cerr << "(+) found " << key << " at list at " << addr << "\n";
				return true;
			}
			current = current->next; // Move to the next node
		}

		// If the key is not found, return false
		if (DEBUG) std::cerr << "(-) not found " << key << " at list at " << addr << "\n";
		return false;
	}


	void print() {
		// for each bucket in vec
		std::cout << "Printing table:\n---\n";

		for (size_t i = 0; i < SIZE; i++) {
			std::cout << i << ": ";
			
			// get head
			Node<T>* current = data.at(i).head;

			// print the linked list there
			int counter = 0;
			while (current) {
				std::cout << current->data << "->";
				current = current->next;

				counter++;
				if (counter == 15) {
					std::cout << "\n";
					counter = 0;
				}
			}

			//end it with null, separate buckets with ---
			std::cout << "null\n";
			std::cout << "---\n";
		}
	}
};
