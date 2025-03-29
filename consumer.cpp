// Consumer.cpp
// This program implements a consumer process that consumes random numbers from shared memory.
// It uses semaphores to synchronize access to the shared memory with a producer process.
// Author: Shane Gallo
// Date: 03/28/2025

#include "sharedmem.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    
    //Open shared memory
    int shared = shm_open("sharedmem", O_CREAT | O_RDWR, 0666);
    ftruncate(shared, sizeof(sharedMem));
    sharedMem* mem = (sharedMem*)mmap(NULL, sizeof(sharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0);

    for(int i = 0; i < MAX_ITEMS; ++i) {
        sem_wait(&mem->full); // Wait for items to consume
        sem_wait(&mem->mutex); // Acquire mutex

        int value = mem->buffer[mem->out]; // Consume the item from the buffer
        std::cout << "Consumed: " << value << " from slot: " << mem->out << std::endl;
        mem->out = (mem->out + 1) % BUFFER_SIZE; // Update index for next item

        sem_post(&mem->mutex); // Release mutex
        sem_post(&mem->empty); // signal that buffer is empty
        sleep(rand() % 2); 
    }
    
    //Unmap shared memory and unlink the semaphore
    munmap(mem, sizeof(sharedMem));
    shm_unlink("sharedmem");
    close(shared);
}