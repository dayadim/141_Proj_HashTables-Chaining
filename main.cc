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
	table->insert(1);
	table->insert(2);
	table->print();
	table->insert(3);
	table->insert(4);


	return 0;
}