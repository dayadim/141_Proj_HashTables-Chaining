#include "hash.h"
#include "LP_hash.h"
using namespace std;

int main() {
	cout << "Testing linear probing." << endl;

	//declare a table like this.
	//1. make the hash table base as a pointer
	//2. assign the table to the abstraction of the base class
	//idfk
	Hash<int, 11> *table;
	table = new Hash_LinearProbing<int, 11>;
	//fill table to max capacity
	for (int i = 0; i < 11; i++) {
		table->insert(i);
	}
	table->print();

	//search for 1st, middle, last element
	table->search(0);
	table->search(5);
	table->search(10);

	//try to insert another element
	table->insert(11);
	return 0;
}