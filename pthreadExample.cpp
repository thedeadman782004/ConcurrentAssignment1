#include <iostream>
#include <pthread.h>

// NOTE: This seems to be running sequentially, or something because the "Threading "
// prints out in order rather than in a random order. 

#if defined(__cplusplus)
extern "C"
#endif

void *print_message(void*)
{
	for(int index = 0; index < 5; ++index)
	{
		std::cout << "Threading " << index << std::endl;
	}
	return NULL;
}

int main() 
{
	int threads = 5;
	pthread_t t1[threads];
	for(int index = 0; index < threads; ++index)
	{
		t1[index] = index;
	}
	
	for(int index = 0; index < threads; ++index)
	{
		pthread_create(&t1[index], NULL, &print_message, NULL);
	}
    std::cout << "Hello";

    void* result;
	for(int index = 0; index < threads; ++index)
	{
		pthread_join(t1[index],&result);
	}
    return 0;
}