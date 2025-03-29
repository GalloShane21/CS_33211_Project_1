#ifndef OS_SHAREDMEM_HPP
#define OS_SHAREDMEM_HPP 

#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>        

#define BUFFER_SIZE 2
#define MAX_ITEMS 20

struct sharedMem {
    int buffer[BUFFER_SIZE];
    int in = 0;
    int out = 0;
    sem_t empty, full, mutex;
};

#endif // OS_SHAREDMEM_HPP