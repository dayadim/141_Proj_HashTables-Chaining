#include <vector>
#include <list>
#include <functional>
#include "../read.h"
#include <set>

const bool DEBUG = true;

// review:
// https://www.youtube.com/watch?v=o7qZj-zX8As&list=PLSVD_4SKyaWHcnFNoV2Dp6vG_Ban2pz8N&index=35

//Base class that provides an interface the two subclasses will inherit
//This is an abstract class that does nothing
//But it allows us to avoid copy/pasting code in main because the interface is the same for both hash tables
template <class T, size_t SIZE>
class Hash {
	public:
		virtual ~Hash() {}
		virtual void insert(T new_data) = 0;
		virtual void remove(T old_data) = 0;
		virtual bool search(T test_data) = 0;
		virtual void change(T old_data, T new_data) = 0;
};

//YOU: Write two hash tables, one for linear probing, one for chaining
template <class T, size_t SIZE>
class LinearProbingHash : public Hash<T,SIZE> {
	/*This bit of magic makes three constants: STATUS::OPEN, STATUS::FILLED, and STATUS::DELETED
	OPEN means the bucket has never held a value in it
	FILLED means it currently holds a valid value in it
	DELETED means the value in it has been deleted and not replaced yet*/
	enum class STATUS : char {OPEN, FILLED, DELETED};
	std::vector<T> data;
	std::vector<STATUS> status; //Each element can be STATUS::OPEN, STATUS::FILLED or STATUS::DELETED
	public:
	LinearProbingHash() {
		data.resize(SIZE); //Set the vector to be SIZE big - SIZE is a template parameter
		status.resize(SIZE,STATUS::OPEN); //Set the state of every bucket to STATUS::OPEN
	}
	void insert(T new_data) {
		//Step 1 - Compute the initial bucket to try
		size_t address = std::hash<T>{}(new_data) % SIZE;
		//Step 2 - We will start at the bucket at "address" and then move to the right,
		//  looping around to the start if necessary, to find first available bucket
		//  Either an OPEN bucket or a DELETED bucket will do.
		//TODO: Make this not infinite loop on a full hash table
		
		//!!!NEW - 17:37 in vid. counter and size should both be size_t otherwise signed vs unsigned possible.
		size_t counter = 0;
		while (status.at(address) == STATUS::FILLED and counter <= SIZE) {
			if (data.at(address) == new_data) {
				if (DEBUG)
					std::cerr << "not inserted\n";
				return;
			}
			
			address = (address+1)%SIZE; //Move one bucket to the right, looping around
			counter++;
			// !!!NEW - like 5 min into vid
			if (counter >= SIZE) {
				std::cerr << "not inserted\n";
				return;
			}
		}
		if (status.at(address) == STATUS::OPEN or status.at(address) == STATUS::DELETED) {
			//Ok, we've found an open spot, write the data in and mark it as filled
			data.at(address) = new_data;
			status.at(address) = STATUS::FILLED;
			if (DEBUG)
				std::cerr << "inserted\n";
		} else
			if (DEBUG)
				std::cerr << "not inserted\n";
	}
	//YOU:
	void remove(T old_data) {
		size_t counter = 0;
		//size_t address = old_data % SIZE;
		// !!!NEW - replace above line with this. 6:08 at vid:
		size_t address = std::hash<T>{}(old_data) % SIZE;

		//error. insert 5. insert 16. delete 16. problem: since both mod 11 to 5, 16 isn't deleted
		// see: 8:08, 10:10, then 18:20 in vid
		while ((status. at (address) == STATUS::FILLED or status. at (address) == STATUS::DELETED) and counter <= SIZE) {
			if (data.at(address) == old_data) {
				status.at(address) = STATUS::DELETED;
				if (DEBUG)
					std::cerr << "deleted\n";
				return;
			}
			address = (address+1)%SIZE;
			counter++;
		}
	}
	//YOU:
	bool search(T test_data) {
		//bool return_val = false;
		size_t counter = 0;
		// !!!NEW - 6:08 and 10:54 in vid
		size_t address = std::hash<T>{}(test_data) % SIZE;
		if (DEBUG) {
			std::cerr << "search address: " << address << "\n";
			
			if (status.at(address) == STATUS::OPEN)
				std::cerr << "status: OPEN" << "\n";
			if (status.at(address) == STATUS::FILLED)
				std::cerr << "status: FILLED" << "\n";
			if (status.at(address) == STATUS::DELETED)
				std::cerr << "status: DELETED" << "\n";
		}
		/*while (status.at(address) == STATUS::FILLED or status.at(address) == STATUS::DELETED) {
			if (data.at(address) == test_data and status.at(address) != STATUS::DELETED)
				return_val = true;
			if (counter > SIZE)
				break;
			address = (address+1)%SIZE;
			counter++;
		}
		return return_val;*/
		
		while (status.at(address) != STATUS::OPEN and counter <= SIZE) {
			if (DEBUG) {
				std::cerr << "value : " << data.at(address) << "\n";
				std::cerr << "loop counter " << counter  << "\n";
			}
			
			if (status.at(address) != STATUS::DELETED and data.at(address) == test_data)
				return true;
			//!!!NEW -11:30 in vid
			address = (address+1)%SIZE;
			counter++;
		}
		//return return_val;
		return false;
	}
	//YOU:
	void change(T old_data, T new_data) {
		//Remember, only change it if it actually is in the hash table
		if (!search(old_data)) {
			if (DEBUG)
				std::cerr << "not in table\n";
			return;
		}
		
		size_t counter = 0;
		// might need to change this to match the other hash functions but idk
		size_t address = std::hash<T>{}(old_data) % SIZE;
		while (status.at(address) == STATUS::FILLED and counter <= SIZE) {
			//std::cerr << "looking for change\n";
			if (data.at(address) == old_data) {
				//!!!NEW - idk why but the nexxt line was uncommented.
				data.at(address) = new_data;
				//status.at(address) = STATUS::FILLED;
				
				if (DEBUG) {
					std::cerr << "changed. new data: " << data.at(address) << "\n";
				if (status.at(address) == STATUS::OPEN)
					std::cerr << "after change status: OPEN" << "\n";
				if (status.at(address) == STATUS::FILLED)
					std::cerr << "after change status: FILLED" << "\n";
				if (status.at(address) == STATUS::DELETED)
					std::cerr << "after change status: DELETED" << "\n";
				}
				return;
			}
			address = (address+1)%SIZE;
			counter++;
		}
	}
};

// !!!NEW - Updated to correct for errors shown in my review.

//YOU: Do the same as the above, with with hashing with chaining instead of linear probing
//You can do chaining either with LLs or with BSTs
template <class T, size_t SIZE>
class ChainingHash : public Hash<T, SIZE> {
    // YOU:
    enum class STATUS : char {OPEN, FILLED};
    std::vector<std::set<T>> data;
	// !!!NEW - status vector is only for linear probing. 14:00 in vid
    //std::vector<STATUS> status;

public:
    // YOU:
    ChainingHash() {
        data.resize(SIZE); // Set the vector to be SIZE big - SIZE is a template parameter
        //status.resize(SIZE, STATUS::OPEN); // Set the state of every bucket to STATUS::OPEN
    }

    // YOU:
    void insert(T new_data) {
		//!!!NEW - 14:40 in vid. don't need allat
        size_t address = std::hash<T>{}(new_data) % SIZE;
        data.at(address).insert(new_data);
    }

    // YOU:
    void remove(T old_data) {
        size_t address = std::hash<T>{}(old_data) % SIZE;
        data.at(address).erase(old_data);
    }

    // YOU:
    bool search(T test_data) {
        size_t address = std::hash<T>{}(test_data) % SIZE;
        return (bool)data.at(address).count(test_data);
    }

    // YOU:
    void change(T old_data, T new_data) {
        if (!search(old_data)) {
            if (DEBUG) std::cerr << "not in table\n";
            return;
        }


		// !!!NEW - address wasn't used here. deleted line. 16:00
        remove(old_data);
        insert(new_data);
    }
};
