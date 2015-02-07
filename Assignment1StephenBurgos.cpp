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

void _addThrees(int i, int * arrayOne, int * arrayTwo, int size_array_two_cint)
{
	// Pre-condition: arrayOne contains integers that will be added together, 
	// two at a time, and placed into arrayTwo
	// Post-condition: The indicis in arrayTwo each contain two of the indices 
	// from arrayOne added together. i.e., arrayTwo[0] contains arrayOne[0] + 
	// arrayOne[1]
	std::cout << "Thread " << i << std::endl;
	/*if (arrayOne[i - 1] == 0 && arrayOne[i] == 0)
	{
		return;
	}
	else if (size_array_two_cint == 1)
	{
		std::cout << "There are " << arrayOne[0] << " threes in the array." << std::endl;
	}*/
	arrayTwo[i / 2] = arrayOne[i - 1] + arrayOne[i];
	return; 
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
	const int half_of_array = 10; // Twice this number will be the size of the array
	const int array_size_cint = 2 * half_of_array;
	const int find_this_cint = 3;
	const int max_threads_cint = array_size_cint / 2;
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
	int arrayTwo_arr[half_of_array] = {0};
	for (int i = 0; i < max_threads_cint; ++i)
	{
		addition_threads[i] = std::thread(_addThrees, (2 * i) + 1, arrayOfThrees_arr, arrayTwo_arr, half_of_array);
	}
	for (int i = 0; i < max_threads_cint; ++i)
	{
		addition_threads[i].join();
	}
	//DEBUGGING:
	std::cout << "Array of threes: " << std::endl;
	for (int i = 0; i < array_size_cint; ++i)
	{
		std::cout << arrayOfThrees_arr[i];
	}
	std::cout << std::endl;
	std::cout << "Array Two: " << std::endl;
	for (int i = 0; i < half_of_array; ++i)
	{
		std::cout << arrayTwo_arr[i];
	}
	std::cout << std::endl;
	return 0;
}