/***************************************************************************************
*    Title: Selection Sort Algorithm
*    Author: GeeksforGeeks
*    Date: No disponible
*    Code version: No especificada
*    Availability: https://www.geeksforgeeks.org/selection-sort-algorithm-2/
***************************************************************************************/
#include <vector>
#include <algorithm> 
#include "MemoryTracker.h"  
using namespace std;

vector<int> selectionSort(vector<int>& arr) {
    MemoryTracker::resetMemory();
    
    // Usamos MemoryTracker::TrackedVector para el seguimiento de memoria
    MemoryTracker::TrackedVector<int> sortedArr = arr;  // Solo esta línea
    if (sortedArr.empty()) return {};  // Manejar caso de arreglo vacío
    
    // No necesitamos declarar otro sortedArr aquí, ya que ya tenemos la copia arriba
    
    for (size_t i = 0; i < sortedArr.size() - 1; ++i) {
        // Encontrar el mínimo elemento en el arreglo no ordenado
        size_t min_idx = i;
        for (size_t j = i + 1; j < sortedArr.size(); ++j) {
            if (sortedArr[j] < sortedArr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Intercambiar el elemento mínimo encontrado con el primer elemento
        if (min_idx != i) {
            swap(sortedArr[i], sortedArr[min_idx]);
        }
    }
    
    return sortedArr;  // Devolvemos el arreglo ordenado
}
