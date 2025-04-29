/***************************************************************************************
*    Title: Merge Sort
*    Author: GeeksforGeeks
*    Date: 2025
*    Code version: Modificada para leer memoria 
*    Availability: https://www.geeksforgeeks.org/merge-sort/
***************************************************************************************/


#include <vector>
#include "MemoryTracker.h"  

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales con MemoryTracker
    int* L = (int*)MemoryTracker::allocate(n1 * sizeof(int));
    int* R = (int*)MemoryTracker::allocate(n2 * sizeof(int));

    // Copiar datos a los arreglos temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Mezclar los arreglos temporales
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar memoria
    MemoryTracker::deallocate(L, n1 * sizeof(int));
    MemoryTracker::deallocate(R, n2 * sizeof(int));
}

// El resto del código permanece igual
void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

vector<int> mergeSort(vector<int>& arr) {
    MemoryTracker::resetMemory();
    if (arr.empty()) return arr;
    
    MemoryTracker::TrackedVector<int> sortedArr = arr; // Ahora se mide
    mergeSortHelper(sortedArr, 0, sortedArr.size() - 1);
    return sortedArr;
}