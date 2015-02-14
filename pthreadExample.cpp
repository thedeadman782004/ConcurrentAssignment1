#include <iostream>
#include <pthread.h>
//using namespace std;

#if defined(__cplusplus)
extern "C"
#endif

void *print_message(void*)
{
    std::cout << "Threading\n";
	return NULL;
}

int main() 
{
	int threads = 5;
    pthread_t t1[threads];
	
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