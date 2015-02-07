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
#include <iostream>
#include <thread>
#include <random>
#include <array>

#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0]))) // Gives the size of the array

typedef const int CINT;

void _addThrees(int i, int * arrayOne_arr, int * arrayTwo_arr)
{
	// Pre-condition: arrayOne contains integers that will be added together, 
	// two at a time, and placed into arrayTwo
	// Post-condition: The indicis in arrayTwo each contain two of the indices 
	// from arrayOne added together. i.e., arrayTwo[0] contains arrayOne[0] + 
	// arrayOne[1]
	arrayTwo_arr[i / 2] = arrayOne_arr[i - 1] + arrayOne_arr[i];
	return; 
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
	return;
}

int _switchArray(int * arrayOne_arr, int * arrayTwo_arr)
{
	// Pre-condition: Two arrays are passed in.  The first array will become the second 
	// and the second will be set to half the size of the first and become all 0s
	// Post-condition: Two arrays are "returned" for use in the next iteration of counting
	CINT size_of_one_cint = ARRAY_SIZE(arrayOne_arr);
	CINT size_of_two_cint = ARRAY_SIZE(arrayTwo_arr);
	for (int i = 0; i < size_of_two_cint; ++i)
	{
		arrayOne_arr[i] = arrayTwo_arr[i]; // Copy the elements back to one to be summed again
	}
	for (int i = size_of_two_cint; i < size_of_one_cint; ++i)
	{
		arrayOne_arr[i] = 0; // Set all other values in arrayOne_arr to 0
	}
	for (int i = 0; i < size_of_two_cint; ++i)
	{
		arrayTwo_arr[i] = 0; // Reset arrayTwo_arr
	}
	int used_space_int = size_of_two_cint;
	return used_space_int; // Return the value to loop with in main, full value to loop through arrayOne_arr and half for arrayTwo_arr
}

int main()
{
	// Variable declaration
	CINT generator_max_cint = 4;
	CINT generator_min_cint = 2;
	CINT half_of_array_cint = 10; // Twice this number will be the size of the array
	CINT array_size_cint = 2 * half_of_array_cint;
	CINT find_this_cint = 3; // Count how many of this number there is in the array
	CINT max_threads_cint = array_size_cint / 2; // TODO Maybe delete the /2
	int space_used_int = half_of_array_cint; // Tracks the space of each array being used
	int arrayOfThrees_arr[array_size_cint];
	// Create an array of random numbers
	std::random_device randomDevice;
	std::mt19937_64 numberGenerated_int(randomDevice());
	std::uniform_int_distribution<> distr(generator_min_cint, generator_max_cint);
	for (int index = 0; index < array_size_cint; ++index)
	{
		// Generate an array of array_size_cint random numbers in the range generator_min_cint to generator_max_cint
		arrayOfThrees_arr[index] = distr(numberGenerated_int);
	}
	// Convert the array for counting
	_checkThree(arrayOfThrees_arr, array_size_cint, find_this_cint);
	std::thread addition_threads[max_threads_cint];
	//DEBUGGING
	std::cout << "Array One: " << std::endl;
	for (int i = 0; i < array_size_cint; ++i)
	{
		std::cout << arrayOfThrees_arr[i];
	}
	//DEBUGGING END
	// Add up the number of threes
	int arrayTwo_arr[half_of_array_cint] = { 0 };
	while (space_used_int > 0) // If less than 2, there is only one item left in the array, and it is the number of 3s
	{
		for (int i = 0; i < space_used_int; ++i)
		{
			addition_threads[i] = std::thread(_addThrees, (2 * i) + 1, arrayOfThrees_arr, arrayTwo_arr);
		}
		for (int i = 0; i < space_used_int; ++i)
		{
			addition_threads[i].join();
		}
		if (space_used_int != 1 && space_used_int % 2 != 0)
		{
			arrayTwo_arr[space_used_int - 2] += arrayTwo_arr[space_used_int - 1]; // Don't lose the last number of an odd length array
			arrayTwo_arr[space_used_int - 1] = 0;
		}
		// Add condition here to check for odd number in arrayOfThrees, if odd, add arrayTwo[last] to arrayOfThrees[last-1]

		for (int i = 0; i < space_used_int; ++i)
		{
			arrayOfThrees_arr[i] = arrayTwo_arr[i]; // Copy the elements back to one to be summed again
		}
		for (int i = space_used_int; i < space_used_int * 2; ++i)
		{
			arrayOfThrees_arr[i] = 0; // Set all other values in arrayOne_arr to 0
		}
		for (int i = 0; i < space_used_int; ++i)
		{
			arrayTwo_arr[i] = 0; // Reset arrayTwo_arr
		}
		space_used_int = space_used_int / 2;
	}
	//DEBUGGING:
	//std::cout << "Array One: " << std::endl;
	//for (int i = 0; i < array_size_cint; ++i)
	//{
	//	std::cout << arrayOfThrees_arr[i];
	//}
	std::cout << std::endl;
	std::cout << "Array Two: " << std::endl;
	for (int i = 0; i < half_of_array_cint; ++i)
	{
		std::cout << arrayTwo_arr[i];
	}
	std::cout << std::endl;
	std::cout << "Final value: " << arrayOfThrees_arr[0] << std::endl;
	return 0;
}