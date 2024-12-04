//#include "read.h"
#include "old_hash.h"
using namespace std;

int main(int argc, char **argv) {
	//This makes two constants, LINEAR which is 0 and CHAINING which is 1.
	//Note the slight difference from the enum class in hash.h
	enum MODE { LINEAR, CHAINING };
	int mode = LINEAR;
	if (argc > 1) mode = atoi(argv[1]); //Read mode from command line parameters
	//If no command line parameter (a.out 0 or a.out 1) is provided, then read from keyboard
	else mode = read("Choose mode:\n0) Linear\n1) Chaining\n");
	if (mode < LINEAR or mode > CHAINING) mode = LINEAR;
	cerr << "Mode == " << mode << endl;
	//ME: THIS 11 GETS CHANGED TO A MILLION WHEN BENCHMARKING, 11 FOR AUTO GRADING/chaining
	Hash<int, 11> *table; //Hash is an abstract class, but by C++ magic we can make it implement one of our two options
	if (mode == LINEAR) table = new LinearProbingHash<int, 11>;
	else table = new ChainingHash<int, 11>;

	while (cin) {
		string s;
		cin >> s;
		if (!cin) break;
		if (s == "CHANGE") {
			int x = 0, y = 0;
			cin >> x >> y;
			if (!cin) break;
			table->change(x, y);
		} else {
			int x = 0;
			cin >> x;
			if (!cin) break;
			if (s == "INSERT") table->insert(x);
			else if (s == "SEARCH") {
				if (table->search(x))
					cout << x << " IN TABLE\n";
				else
					cout << x << " NOT IN TABLE\n";
			} else if (s == "REMOVE") table->remove(x);
			else break;
		}
	}

	delete table;
}

