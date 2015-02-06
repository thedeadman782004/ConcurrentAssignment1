/* HEADER
 * Author: Stephen Burgos
 * Class: CIS 363, Concurrent Programming
 * Professor: Dr. Joe Hoffert
 * Assignment 1: Chapter 1, Exercise 3, page 28
 * Last Edited: February 6, 2015
 * Version: 1.0
 * Description: This program counts the number of 3s in a given array
		and prints the final count.
 * Statement: I wrote all of this code myself and did not copy any
		code from the internet or another student.
*/
#include <iostream> ;
#include <thread>;
#include <random>;

int _addThrees(int i, int * arrayOne, int * arrayTwo)
{
	// Pre-condition: arrayOne contains integers that will be added together, 
	// two at a time, and placed into arrayTwo
	// Post-condition: The indicis in arrayTwo each contain two of the indices 
	// from arrayOne added together. i.e., arrayTwo[0] contains arrayOne[0] + 
	// arrayOne[1]
	return 0; // Should return the size of arrayTwo
}

void _checkThree(int * arrayCheck_arr, const int size_cint, const int find_value_cint)
{
	// Pre-condition: An array of integers, the size of the array and the value
	// to find are passed in
	// Post-condition: All threes in the array have been changed to 1 and all 
	// other numbers have been changed to 0
	for (int i = 0; i < size_cint; ++i)
	{
		if (arrayCheck_arr[i] == find_value_cint)
		{
			arrayCheck_arr[i] = 1;
		}
		else
		{
			arrayCheck_arr[i] = 0;
		}
	}
	return;
}

int main()
{
	// Variable declaration
	const int generator_max_cint = 4;
	const int generator_min_cint = 2;
	const int array_size_cint = 20;
	const int find_this_cint = 3;
	const int max_threads_cint = 10;
	int arrayOfThrees_arr[array_size_cint];
	// Create an array of random numbers
	std::random_device randomDevice;
	std::mt19937_64 numberGenerated_int(randomDevice());
	std::uniform_int_distribution<> distr(generator_min_cint, generator_max_cint);
	for (int index = 0; index < array_size_cint; ++index)
	{
		// Generate an array of array_size random numbers in the range generator_min to generator_max
		arrayOfThrees_arr[index] = distr(numberGenerated_int);
	}
	// Convert the array for counting
	_checkThree(arrayOfThrees_arr, array_size_cint, find_this_cint);
	std::thread addition_threads[max_threads_cint];
	// Add up the number of threes
	int arrayTwo_arr[array_size_cint / 2]; // Right here the might be a problem if the array has an odd number of indices
	for (int i = 0; i < max_threads_cint; ++i)
	{ // addition_threads creates i threads, which is the maximum number of threads allowed
		// _addThrees needs to be passed index locations from arrayOfThrees_arr from 0 to arrayOfThrees_arr.length / 2
		addition_threads[i] = std::thread(_addThrees, (2 * i) + 1, arrayOfThrees_arr, arrayTwo_arr);
	}
	for (int i = 0; i < max_threads_cint; ++i)
	{
		addition_threads[i].join();
	}
	return 0;
}