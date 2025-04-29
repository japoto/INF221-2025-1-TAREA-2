/***************************************************************************************
*    Title: QuickSort.cpp (Median of Three)
*    Author: Kistler, J.
*    Date: 2023
*    Code version: Modificada para obtener memoria
*    Availability: https://github.com/Jake-Kistler/QuickSortMedianOfThree/blob/main/QuickSort.cpp
***************************************************************************************/


#include <vector>
#include <algorithm>
#include <random>
#include "MemoryTracker.h"
using namespace std;

// Función auxiliar para particionar
int partition(vector<int>& arr, int low, int high) {
    // Median-of-three para elegir pivote
    int mid = low + (high - low) / 2;
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[mid], arr[high]);
    
    int pivot = arr[mid];
    swap(arr[mid], arr[high]);  // Colocar pivote al final
    
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// Insertion Sort para pequeños subarreglos
void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// QuickSort iterativo con stack manual
void quickSortHelper(vector<int>& arr, int low, int high) {
    // Stack manual en lugar de recursión
    int stack[high - low + 1];
    int top = -1;
    
    stack[++top] = low;
    stack[++top] = high;
    
    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        
        // Usar Insertion Sort para pequeños subarreglos
        if (high - low < 20) {
            insertionSort(arr, low, high);
            continue;
        }
        
        int pi = partition(arr, low, high);
        
        // Push subarreglos izquierdo y derecho al stack
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

vector<int> quickSort(vector<int>& arr) {
    MemoryTracker::resetMemory();
    if (arr.empty()) return arr;
    
    MemoryTracker::TrackedVector<int> sortedArr = arr;
    quickSortHelper(sortedArr, 0, sortedArr.size() - 1);
    
    return sortedArr;
}