#include <algorithm>
#include <vector>
#include "MemoryTracker.h"  

std::vector<int> sortArray(std::vector<int>& arr) {
    // Reiniciar contador (std::sort es in-place y usa O(1) espacio adicional en teoría)
    MemoryTracker::resetMemory();
    MemoryTracker::TrackedVector<int> sortedArr = arr; 
    std::sort(arr.begin(), arr.end());
    
    return arr;
}