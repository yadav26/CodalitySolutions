#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <cassert>


// Creating a lockless multiple producers, multiple consumers (MPMC) queue involves careful 
// consideration of memory ordering and atomic operations. Implementing such a queue can be 
// complex and requires a solid understanding of memory models, atomic operations, and thread synchronization.

// Below is a simple example of a lockless MPMC queue using C++11 atomics. 
// This implementation uses a fixed-size ring buffer to store elements, and it ensures that enqueue 
// and dequeue operations are lock-free.

template <typename T, size_t Size>
class MPMCQueue {
public:
    MPMCQueue() : head(0), tail(0) {
        buffer.resize(Size);
    }

    bool Enqueue(const T& value) {
        size_t currentTail = tail.load(std::memory_order_relaxed);
        size_t nextTail = (currentTail + 1) % Size;

        if (nextTail == head.load(std::memory_order_acquire)) {
            // Queue is full
            return false;
        }

        buffer[currentTail] = value;
        tail.store(nextTail, std::memory_order_release);

        return true;
    }

    bool Dequeue(T& value) {
        size_t currentHead = head.load(std::memory_order_relaxed);
        size_t currentTail = tail.load(std::memory_order_acquire);

        if (currentHead == currentTail) {
            // Queue is empty
            return false;
        }

        value = buffer[currentHead];
        head.store((currentHead + 1) % Size, std::memory_order_release);

        return true;
    }

private:
    std::vector<T> buffer;
    alignas(64) std::atomic<size_t> head;
    alignas(64) std::atomic<size_t> tail;
};

const int NumProducers = 4;
const int NumConsumers = 4;
const int QueueSize = 10;

MPMCQueue<int, QueueSize> queue;

void ProducerFunction(int id) {
    for (int i = 0; i < 20; ++i) {
        while (!queue.Enqueue(id * 100 + i)) {
            // Wait if the queue is full
            std::this_thread::yield();
        }
    }
}

void ConsumerFunction(int id) {
    for (int i = 0; i < 20; ++i) {
        int value;
        while (!queue.Dequeue(value)) {
            // Wait if the queue is empty
            std::this_thread::yield();
        }
        std::cout << "Consumer " << id << " dequeued: " << value << std::endl;
    }
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < NumProducers; ++i) {
        producers.emplace_back(ProducerFunction, i);
    }

    for (int i = 0; i < NumConsumers; ++i) {
        consumers.emplace_back(ConsumerFunction, i);
    }

    for (auto& producer : producers) {
        producer.join();
    }

    for (auto& consumer : consumers) {
        consumer.join();
    }

    assert(queue.Enqueue(42) == false);  // The queue is full

    std::cout << "All producers and consumers finished." << std::endl;

    return 0;
}