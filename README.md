# CS 33211 Operating Systems Project 1: Producer-Consumer Problem
The project involved implementing a solution to the producer-consumer problem using semaphores to synchronize the producer and consumer.

For my implementation, I used an integer array of size two as my buffer for the producer to produce items into, and the consumer to consume items from.


## To Compile and run
Compile and run using these commands in your Linux terminal

```bash
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer
```

## Examples
![image](Example.png)
