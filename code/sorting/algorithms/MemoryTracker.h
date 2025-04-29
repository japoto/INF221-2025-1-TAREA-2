// MemoryTracker.h
#ifndef MEMORYTRACKER_H
#define MEMORYTRACKER_H

#include <cstdlib>
#include <vector>

namespace MemoryTracker {
    extern long total_memory;
    
    inline void* allocate(size_t size) {
        total_memory += static_cast<long>(size);
        return malloc(size);
    }
    
    inline void deallocate(void* ptr, size_t size) {
        total_memory -= static_cast<long>(size);
        free(ptr);
    }
    
    template<typename T>
    class TrackedVector : public std::vector<T> {
    public:
        using std::vector<T>::vector;
        
        TrackedVector(const std::vector<T>& other) : std::vector<T>(other) {
            total_memory += this->capacity() * sizeof(T);
        }
        
        ~TrackedVector() {
            total_memory -= this->capacity() * sizeof(T);
        }
    };
    
    inline long getMemoryKB() {
        return total_memory / 1024;
    }
    
    inline void resetMemory() {
        total_memory = 0;
    }
}

#endif