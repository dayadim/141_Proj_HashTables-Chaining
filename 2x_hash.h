#pragma once

#include "hash.h"

// refer to the following files to figure out how to implement
// - 2x_hashing: if built in hash fails (i.e. the bucket is full), hash again using a separate hash function

/*
* Implement a two-step hashing approach. First, use a primary hash function to find the initial bucket for a given key. 
* If the bucket is occupied, apply a secondary hash function to determine a new bucket. 
* If both hash attempts fail, use linear probing to find an open slot.

* Insert: Calculate the initial bucket using the primary hash function. If the bucket is empty, place the item there.
* If occupied, use the secondary hash function to attempt to find an open bucket. 
* If both hashing attempts fail, sequentially check subsequent buckets (linear probing) until an open one is found.

* Search: Calculate the initial bucket using the primary hash function and check if the item is present. 
* If not, recalculate using the secondary hash function. 
* If still not found, continue checking subsequent buckets (linear probing) until the item is found or an empty bucket is encountered, indicating the item is not in the table.
*/
template <class T, size_t SIZE>
class Twox_hash : public Hash<T, SIZE> {
	enum class STATUS : char {OPEN, FILLED};

public:
	std::vector<T> data;
	std::vector<STATUS> status;

	Twox_hash() {}

	void insert(T new_data) {}

	bool search(T key) { return false; }

	void print() {}
};
