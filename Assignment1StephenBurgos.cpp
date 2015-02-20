/* 
 * Author: Stephen Burgos
 * Class: CIS 363, Concurrent Programming
 * Professor: Dr. Joe Hoffert
 * Assignment 1: Chapter 1, Exercise 3, page 28
 * Last Edited: February 7, 2015
 * Version: 1.0
 * Description: This program generates an array of random numbers, 
		prints the array, counts the number of 3s (or other value if specified)
		in a given array and prints the final count.
 * Statement: I wrote all of this code myself and did not copy any
		code from the internet or another student.
 * Comment: It is hard to determine what a "Huge function" is, but I don't think any
		of mine are.  
 * Formatting Note: Comments that tell what a code block does are placed above the block,
		comments that tell what a single line means are placed on that line
*/
#include <iostream>
#include <thread>
#include <random>
typedef const int CINT;

void _addThrees(int i, int * arrayOne_arr, int * arrayTwo_arr)
{
	// Pre-condition: arrayOne contains integers that will be added together, 
	// two at a time, and placed into arrayTwo_arr
	// Post-condition: The indices in arrayTwo_arr each contain two of the indices 
	// from arrayOne added together. i.e., arrayTwo_arr[0] contains arrayOne_arr[0] + 
	// arrayOne_arr[1]
	arrayTwo_arr[i / 2] = arrayOne_arr[i - 1] + arrayOne_arr[i];
}

void _checkThree(int * arrayCheck_arr, CINT size_cint, CINT find_value_cint)
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
}

int main()
{
	// Variable declaration
	// The first 4 may be changed, based on preference, before executing the code
	CINT generator_max_cint = 4;
	CINT generator_min_cint = 2;
	CINT half_of_array_cint = 11; // Twice this number will be the size of the array
	CINT find_this_cint = 3; // Count how many of this number there is in the array
	CINT array_size_cint = 2 * half_of_array_cint;
	CINT max_threads_cint = array_size_cint / 2;
	int space_used_int = half_of_array_cint; // Tracks the space of each array being used
	int arrayOfThrees_arr[array_size_cint];
	
	// Generate an array of array_size_cint random numbers in the range generator_min_cint to generator_max_cint
	std::random_device randomDevice;
	std::mt19937_64 numberGenerated_int(randomDevice());
	std::uniform_int_distribution<> distr(generator_min_cint, generator_max_cint);
	for (int index = 0; index < array_size_cint; ++index)
	{
		arrayOfThrees_arr[index] = distr(numberGenerated_int);
	}	
	
	// Print the array for to check visually
	std::cout << "Initial array: " << std::endl;
	for (int i = 0; i < array_size_cint; ++i)
	{
		std::cout << arrayOfThrees_arr[i]; 
	}
	std::cout << std::endl;
	
	// Convert the array for counting
	_checkThree(arrayOfThrees_arr, array_size_cint, find_this_cint);
	std::thread addition_threads[max_threads_cint];
	
	// Add up the number of threes (or other value of find_this_cint)
	int arrayTwo_arr[half_of_array_cint] = { 0 };
	while (space_used_int > 0) // If space_used_int is 0, then the final answer has been found
	{
		for (int i = 0; i < space_used_int; ++i)
		{
			addition_threads[i] = std::thread(_addThrees, (2 * i) + 1, arrayOfThrees_arr, arrayTwo_arr);
		}
		for (int i = 0; i < space_used_int; ++i)
		{
			addition_threads[i].join();
		}
		
		// Don't lose the last number of an odd length array
		if (space_used_int != 1 && space_used_int % 2 != 0)
		{
			arrayTwo_arr[space_used_int - 2] += arrayTwo_arr[space_used_int - 1]; 
			arrayTwo_arr[space_used_int - 1] = 0;
		}
		
		// Copy the elements back to arrayOfThrees_arr to be summed again
		for (int i = 0; i < space_used_int; ++i)
		{
			arrayOfThrees_arr[i] = arrayTwo_arr[i]; 
		}
		
		// Set all other values in arrayOne_arr to 0
		for (int i = space_used_int; i < space_used_int * 2; ++i)
		{
			arrayOfThrees_arr[i] = 0; 
		}
		
		// Reset arrayTwo_arr
		for (int i = 0; i < space_used_int; ++i)
		{
			arrayTwo_arr[i] = 0; 
		}
		space_used_int = space_used_int / 2;
	}
	std::cout << "The final count for the number of " << find_this_cint << "s is " << arrayOfThrees_arr[0] << std::endl;
	return 0;
}