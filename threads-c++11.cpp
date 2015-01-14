#include <iostream>
#include <thread>
#include <mutex>

std::mutex my_mutex;

void foo(int tid)
{
  //std::lock_guard<std::mutex> lock(my_mutex);
	//This next line is causing things to print out in odd places, such as the endl for one thread
	//far from the rest of the line.  An interesting thing
  std::cout << "Launched by thread " << tid << std::endl;
}

int main()
{  // The main function
  const int MAX_THREADS = 10;
  std::thread my_threads[MAX_THREADS];
  for (int index = 0; index < MAX_THREADS; ++index)
    {
      my_threads[index] = std::thread(foo, index);
    }

  std::cout << MAX_THREADS << " THREADS LAUNCHED FROM main()..." << std::endl;

  // synchronize threads:
  for (int index = 0; index < MAX_THREADS; ++index)
    {
      my_threads[index].join();
    }

  return 0;
}
