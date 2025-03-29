// producer.cpp
// This program implements a producer process that produces random numbers and stores them in shared memory.
// It uses semaphores to synchronize access to the shared memory with a consumer process.
// Author: Shane Gallo
// Date: 03/28/2025

#include "sharedmem.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>

int main() {
    srand(time(0));

    //Open shared memory
    int shared = shm_open("sharedmem", O_CREAT | O_RDWR, 0666);
    ftruncate(shared, sizeof(sharedMem));
    sharedMem* mem = (sharedMem*)mmap(NULL, sizeof(sharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0);

    //Initialize semaphores
    sem_init(&mem->empty, 1, BUFFER_SIZE);
    sem_init(&mem->full, 1, 0);
    sem_init(&mem->mutex, 1, 1);

    for(int i = 0; i < MAX_ITEMS; ++i) {
        sem_wait(&mem->empty); // Wait until there is space to produce
        sem_wait(&mem->mutex); // Acquire mutex 

        int value = rand() % 100; 
        mem->buffer[mem->in] = value; // store random number in buffer
        std::cout << "Produced: " << value << " into slot: " << mem->in << std::endl;
        mem->in = (mem->in + 1) % BUFFER_SIZE; // Update index for next item

        sem_post(&mem->mutex); // Release mutex
        sem_post(&mem->full); // signal that buffer is full
        sleep(rand() % 2);
    }

    //Unmap shared memory and unlink the semaphore
    munmap(mem, sizeof(sharedMem));
    sem_unlink("sharedmem");
    close(shared);
}