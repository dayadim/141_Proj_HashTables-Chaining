#pragma once

#include "hash.h"

template <class T, size_t SIZE>
class Hash_LL : public Hash<T, SIZE> {
public:
	std::vector<T> data;
	std::vector<STATUS> status;
	Hash_LL() {}
	void insert(T new_data) {}
	bool search(T key) { return false; }
	void print() {}
};