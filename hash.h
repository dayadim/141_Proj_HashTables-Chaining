#ifndef HASH_H
#define HASH_H

#include "read.h"
#include <vector>

const bool DEBUG = false;

//template. makes something of unspecified type T.
//- e.g. usage: Hash<int, 100> for integers and size 100
//- any class that inherits from hash must have the funcs, but they can be overwritten
//  - that's why they're virtual and = 0. idk don't ask more questions
//- using size_t for size because that is the biggest possible primitive datatype, unsigned
template <class T, size_t SIZE> class Hash {
	public:
		virtual ~Hash() {}
		virtual void insert(T new_data) = 0;
		virtual bool search(T test_data) = 0;
		
		//new
		virtual void print() = 0;
		//virtual void stats() = 0;
};



#endif // HASH_H