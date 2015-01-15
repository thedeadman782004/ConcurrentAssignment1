#include <iostream>
#include <thread>
//#include <ctime>
//#include <sys/time.h>

using namespace std;
//typedef unsigned long long timestamp_t;

void foo(size_t * mocha, size_t max)
{
	size_t toAdd = 1;
	while(*mocha < max)
	{
		*mocha += toAdd;
	}
}

size_t bar(size_t  mocha, size_t max)
{
	size_t toAdd = 1;
	while(mocha < max)
	{
		mocha += toAdd;
	}
	return mocha;
}

int main()
{  // The main function
	size_t maximum = 4000000000;
	size_t value = 0; // Declare a value to be 0 to add onto in the functions
	size_t * chocolate = &value; // Assign the pointer chocolate to point to value in memory
	time_t startTime = time(NULL);
	time_t endTime;

	thread first(foo, chocolate, maximum);
	thread second(foo, chocolate, maximum);
	thread third(foo, chocolate, maximum);
	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes
	third.join();
	endTime = time(NULL) - startTime;
	cout << "Thread running time: " << endTime << endl;
	cout << "Chocolate equal to: " << *chocolate << endl;

	size_t cocoa = 0;
	startTime = time(NULL);

	cocoa = bar(cocoa, maximum);

	endTime = time(NULL) - startTime;
	cout << "Sequential time: " << endTime << endl;
	cout << "Chocolate is now equal to: " << cocoa << endl;

	return 0;
}