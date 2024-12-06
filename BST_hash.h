#pragma once

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
