#include <iostream>
#include <thread>

using namespace std;

void foo(int * mocha, int max)
{
	int toAdd = 2;
	while(*mocha < max)// These two while loops are not executing in parallel.  Why Not?
	//					Perhaps the debugger is serializing the execution.  To test this, execute the loops with a large maximum with and without debugging and compare the running time.
	{
		*mocha += toAdd;
	}
	//*mocha += 5; // This adds 5 to the value mocha points to
}

void bar(int * mocha, int max)
{
	int toAdd = 2;
	while(*mocha < max)
	{
		*mocha += toAdd;
	}
	//*mocha += 2; // This adds 2 to the value mocha points to
	//*mocha += 3;
}

int main()
{  // The main function
	int maximum = 20;
	int value = 0; // Declare a value to be 0 to add onto in the functions
	int * chocolate = &value; // Assign the pointer chocolate to point to value in memory

	thread first(foo, chocolate, maximum);
	thread second(bar, chocolate, maximum);

	cout << "main, foo and bar now execute concurrently..." << endl;

	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	cout << "foo and bar completed." << endl;
	cout << "Chocolate is now equal to: " << *chocolate << endl;
	//chocolate is equal to 17, 10 + 5 + 2, because each function used a pointer

	return 0;
}