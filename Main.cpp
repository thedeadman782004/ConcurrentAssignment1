#include <iostream>
#include <thread>\

using namespace std;\

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
	size_t maximum = 40000000000;
	size_t value = 0; 
	size_t * chocolate = &value; 
	time_t startTime = time(NULL);
	time_t endTime;
	
	const int MAX_THREADS = 10;
	thread my_threads[MAX_THREADS];
	for (int index = 0; index < MAX_THREADS; ++index)
		{
			my_threads[index] = std::thread(foo, chocolate, maximum);
		}
	for (int index = 0; index < MAX_THREADS; ++index)
		{
			my_threads[index].join();
		}
		
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