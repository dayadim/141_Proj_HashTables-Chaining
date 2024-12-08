#include "hash.h"
#include "LP_hash.h"
#include "LL_hash.h"
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

//WE'RE USING UNSIGNED SHORT DATATYPE
using HashDataType = unsigned short;
const int size_ = 10000; // past 10000 (100000) stack overflow on amaan's machine

/**
* @brief generates a vector of a given size with random numbers.
*
* @note If the same seed is used, the same vector is generated
*
* @param size the size of the vector to generate
* @param seed the seed used for the random number generator
*
* @return a vector of size @p size with random numbers
*/
std::vector<HashDataType> gen_elements(int size, int seed) {
	std::vector<HashDataType> vec;
	std::mt19937 gen(seed); // std mersenne_twister_engine seeded with seed
	std::uniform_int_distribution<HashDataType> dis(0, std::numeric_limits<HashDataType>::max());

	for (int i = 0; i < size; i++) {
		vec.push_back(dis(gen));
	}
	return vec;
}

void timing_LL_probing() {
	cout << "==================== TIMING FOR LL PROBING ====================" << endl;

	vector<HashDataType> elements = gen_elements(size_, 141);

	Hash_LL<HashDataType, size_>* table = new Hash_LL<HashDataType, size_>;

	// to store average timing results for each phase
	vector<double> average_insert_timings;
	vector<double> average_search_timings;

	int capacity = 0;
	int total_capacity = size_ * .4; // 40% capacity to insert after each section of timing
	int time_increment = size_ / 10; // 10% capacity increments to time individually then avg

	// loop until we reach 1000% capacity
	while (capacity < size_ * 10) {
		// insert 40% of elements. so each loop we've added 50% of elements
		// 10% is being timed, but later on in the loop
		int phase_end = capacity + total_capacity;
		for (int i = capacity; i < phase_end; ++i) {
			table->insert(elements[i]);
		}
		capacity = phase_end;

		//cout << "(*) Inserted up to " << (capacity * 100.0 / size) << "% capacity.\n";

		// time how long it takes to search n times where n = # of elements * .1
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, size_ - 1);

		auto search_start_time = high_resolution_clock::now();
		for (int i = 0; i < time_increment; ++i) {
			int random_index = dis(gen); // generate a random index
			table->search(elements[random_index]); // perform search on a random element
		}
		auto search_end_time = high_resolution_clock::now();

		// calculate and store the average time per search for this 10% increment
		double total_search_duration = duration_cast<nanoseconds>(search_end_time - search_start_time).count();
		double average_search_time = total_search_duration / time_increment;
		average_search_timings.push_back(average_search_time);

		cout << "("
			<< ((capacity) * 100.0 / size_) << "%): Average search time = "
			<< average_search_time << " ns/search.\n";

		// time the next 10% capacity worth of inserts
		// we want to add on unadded elements to the table, so we start where we left off
		int timed_insert_start = capacity;
		int timed_insert_end = capacity + time_increment;

		auto insert_start_time = high_resolution_clock::now();
		for (int i = timed_insert_start; i < timed_insert_end; ++i) {
			table->insert(elements[i]);
		}
		auto insert_end_time = high_resolution_clock::now();

		//calculate and store the average time per insert for this 10% increment
		double total_insert_duration = duration_cast<nanoseconds>(insert_end_time - insert_start_time).count();
		double average_insert_time = total_insert_duration / time_increment;
		average_insert_timings.push_back(average_insert_time);

		cout << "(" << (capacity * 100.0 / size_) << "% to "
			<< ((capacity + time_increment) * 100.0 / size_) << "%): Average insert time = "
			<< average_insert_time << " ns/insert.\n";

		// Update capacity after timed inserts
		capacity += time_increment;
	}

	// Clean up
	delete table;

	// Output the average timings for all phases
	cout << "\nFinal Average Timings:\n";
	cout << "Insertion (avg. ns/insert):\n";
	for (int i = 0; i < average_insert_timings.size(); ++i) {
		cout << average_insert_timings[i] << "\n";
	}

	cout << "\nSearch (avg. ns/search):\n";
	for (int i = 0; i < average_search_timings.size(); ++i) {
		cout << average_search_timings[i] << "\n";
	}
}

int main() {
	int choice;
	cout << "Select an option:\n";
	cout << "1. Linear probing timing\n";
	cout << "2. Double hashing timing\n";
	cout << "3. Linked list probing timing\n";
	cout << "4. BST timing\n";
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice) {
		case 1:
			cout << "Linear probing timing not implemented." << endl;
		case 2:
			cout << "Double hashing timing not implemented." << endl;
			break;
		case 3:
			timing_LL_probing();
			break;
		case 4:
			cout << "BST timing not implemented." << endl;
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
	}
	return 0;
}