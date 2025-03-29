# CS 33211 Operating Systems Project 1: Producer-Consumer Problem

The project involved implementing a solution to the producer-consumer problem using semaphores to synchronize the producer and consumer.

For my implementation, I used an integer array of size two as my buffer for the producer to produce items into, and the consumer to consume items from.

The producer produces a total of twenty random integers, and the consumer consumes the twenty integers. Only two items are allowed inside the buffer at one time. The two-item restriction is controlled using two semaphores empty and full. 
Empty prevents the consumer from consuming when the buffer is empty and full prevents the producer from adding items when the buffer is full. 

I also used a third semaphore (mutex) in order to synchronize the producer and consumer and ensure that only one could modify the shared memory at a time.

## To Compile and run
Compile and run using these commands in your Linux terminal

```bash
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer
```

## Examples
![image](Example.png)
