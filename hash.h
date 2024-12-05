#ifndef HASH_H
#define HASH_H

#include "read.h"
#include <vector>

const bool DEBUG = true;

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
};

//using inheritance
//- inherits all properties from hash
//- but is also a template, so it can be used with any type
template <class T, size_t SIZE>
class Hash_LinearProbing : public Hash<T, SIZE> {
	//this enumerates chars to be "strongly typed" to types called "STATUS"
	//- usage e.g: STATUS::OPEN will just be some char value
	// - we will just use it as STATUS::OPEN or STATUS::FILLED
	// - don't care what it actually is
	enum class STATUS : char {OPEN, FILLED};

	//use this as the hash function
	// inline usage: std::hash<T>{}(data_to_hash)... % smt
	std::hash<T> hash;

public:
	std::vector<T> data;
	std::vector<STATUS> status;

	Hash_LinearProbing() {
		//set the vector to be size SIZE and set all states to open
		data.resize(SIZE); 
		status.resize(SIZE, STATUS::OPEN);
	}

	//inserts data of type T. check above comments why it's T
	void insert(T new_data) {
		//get address 
		size_t addr = hash(new_data) % SIZE;

		//runaway loop counter
		size_t counter = 0;
	
		//while the bucket is filled
		//i think the counter check in the while loop might be redundant
		while (status.at(addr) == STATUS::FILLED and counter <= SIZE) {
			// if this unique data already exists in the correct spot
			if (data.at(addr) == new_data) {
				if (DEBUG) { std::cerr << "(-) not inserted. Dupe?\n";}
				return;
			}

			// this is where the linear probing happens
			// otherwise, move to the next bucket
			addr = (addr + 1) % SIZE;

			if (counter >= SIZE) {
				std::cerr << "(-) not inserted\n";
				return;
			}
		}

		// this should fail only if the table is full
		try {
			//if the bucket is open, add it and mark as filled
			if (status.at(addr) == STATUS::OPEN) {
				data.at(addr) = new_data;
				status.at(addr) = STATUS::FILLED;
				if (DEBUG) std::cerr << "(+) inserted\n";
			} else {
				throw std::runtime_error("Table full? Did not insert.");
			}
		} catch (const std::exception &e) {
			if (DEBUG) std::cerr << "(-) not inserted: " << e.what() << "\n";
		}
	}

	void search(T key) {
		size_t addr = hash(key) % SIZE;
		size_t counter = 0;

		// display the search address, and if it's open or filled
		if (DEBUG) {
			std:: cerr << "search address: " << addr << "\n";

			if (status.at(addr) == STATUS::OPEN)   std::cerr << "status: OPEN" << "\n";
			if (status.at(addr) == STATUS::FILLED) std::cerr << "status: FILLED" << "\n";
		}

		while (status.at(addr) != STATUS::OPEN and counter <= SIZE) {
			
		}
	}
};

#endif // HASH_H