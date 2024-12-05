#ifndef LP_HASH
#define LP_HASH

#include "hash.h"

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

		//runaway counter (to not loop more than SIZE)
		size_t counter = 0;
	
		//only iterate once through the entire table.
		while (counter <= SIZE) {
			// if this unique data already exists in the correct spot
			if (status.at(addr) == STATUS::FILLED && data.at(addr) == new_data) {
				if (DEBUG) { std::cerr << "(-) not inserted. Dupe?\n";}
				return;
			}

			// this should fail only if the table is full
			//if the bucket is open, add it and mark as filled
			if (status.at(addr) == STATUS::OPEN) {
				data.at(addr) = new_data;
				status.at(addr) = STATUS::FILLED;
				if (DEBUG) std::cerr << "(+) inserted\n";
				return;
			}

			// this is where the linear probing happens
			// otherwise, move to the next bucket
			addr = (addr + 1) % SIZE;
			counter++;
		}

		//if we didn't return as a result of the above while loop, that means the table is full
		if (DEBUG) std::cerr << "(-) not inserted: Table full\n"; std::cerr << "(*) loop counter: " << counter  << "\n";
	}
	
	bool search(T key) {
		size_t addr = hash(key) % SIZE;
		size_t counter = 0;

		// display the search address, and if it's open or filled
		if (DEBUG) {
			std:: cerr << "search address: " << addr << "\n";

			if (status.at(addr) == STATUS::OPEN)   std::cerr << "status: OPEN" << "\n";
			if (status.at(addr) == STATUS::FILLED) std::cerr << "status: FILLED" << "\n";
		}

		//so long as the current bucket isn't open, and we haven't searched the entire table
		while (status.at(addr) == STATUS::OPEN and counter <= SIZE) {
			// display the value and the loop counter for debug
			if (DEBUG) {
				std::cerr << "(*) value : " << data.at(addr) << "\n";
				std::cerr << "(*) loop counter " << counter  << "\n";
			}

			// if data is filled and it matches the key, we found it
			if (status.at(addr) == STATUS::FILLED and data.at(addr) == key) {
				return true;
			}

			// if we haven't found it then move to the next bucket
			addr = (addr + 1) % SIZE;
			counter++;
		}
		return false;
	}

	void print() {
		std::cout << "Printing table:\n";
		int counter = 0;
		std::cout <<"| ";
		for (size_t i = 0; i < SIZE; i++) {
			std::cout << data.at(i) << " ";
			switch (status.at(i)) {
				case STATUS::OPEN:
					std::cout << "_ | ";
					break;
				case STATUS::FILLED:
					std::cout << "X | ";
					break;
			}
			counter++;
			if (counter == 15) {
				std::cout << "\n";
				counter = 0;
			}
		}
		std::cout << "\n";
	}
};

#endif