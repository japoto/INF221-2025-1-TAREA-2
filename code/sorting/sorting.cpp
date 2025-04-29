#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <map>
#include "../algorithms/MemoryTracker.h"
using namespace std;
namespace fs = std::filesystem;

// ===== Sistema de medición de memoria =====
namespace MemoryTracker {
    long algorithm_memory = 0;
}

// Declaraciones de los algoritmos (deben estar en sus respectivos .cpp)
std::vector<int> selectionSort(std::vector<int>&);
std::vector<int> mergeSort(std::vector<int>&);
std::vector<int> quickSort(std::vector<int>&);
std::vector<int> sortArray(std::vector<int>&);

// Función para cargar datos
std::vector<int> cargarDatos(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<int> datos;
    int valor;
    while (in >> valor) {
        datos.push_back(valor);
    }
    return datos;
}

// Función para guardar resultados
void guardarDatos(const std::string& archivo, const std::vector<int>& datos) {
    std::ofstream out(archivo);
    for (size_t i = 0; i < datos.size(); ++i) {
        out << datos[i];
        if (i < datos.size() - 1) out << " ";
    }
    out << "\n";
}

struct Medicion {
    std::string nombreArchivo;
    double tiempoMs;
    long memoriaKB;
};

void ejecutarBenchmark(
    const string& nombre,
    vector<Medicion>& registros,
    const vector<string>& archivos,
    vector<int> (*algoritmo)(vector<int>&)
) {
    for (const auto& archivo : archivos) {
        auto arreglo = cargarDatos("data/array_input/" + archivo);
        
        MemoryTracker::resetMemory(); // Reiniciar ANTES de ejecutar
        auto inicio = chrono::steady_clock::now();
        auto ordenado = algoritmo(arreglo);
        auto fin = chrono::steady_clock::now();

        double tiempo = chrono::duration<double, milli>(fin - inicio).count();
        long memoria = MemoryTracker::getMemoryKB(); // Obtener después de ejecutar

        registros.push_back({archivo, tiempo, memoria});
    }
}

int main() {

    std::vector<std::string> listaArchivos;
    for (const auto& entrada : fs::directory_iterator("data/array_input")) {
        if (entrada.is_regular_file()) {
            listaArchivos.push_back(entrada.path().filename().string());
        }
    }

    std::map<std::string, std::vector<Medicion>> resultados;

    ejecutarBenchmark("selection", resultados["selection"], listaArchivos, selectionSort);
    ejecutarBenchmark("merge", resultados["merge"], listaArchivos, mergeSort);
    ejecutarBenchmark("quick", resultados["quick"], listaArchivos, quickSort);
    ejecutarBenchmark("sort", resultados["sort"], listaArchivos, sortArray);

    // Generar reporte
    std::ofstream reporte("data/measurements/bench.txt");
    reporte << "=== RESULTADOS DE BENCHMARK ===\n";
    reporte << "Formato: [Algoritmo] [Archivo] -> Tiempo (ms) | Memoria (KB)\n\n";

    for (const auto& [nombre, datos] : resultados) {
        reporte << "---- " << nombre << " ----\n";
        for (const auto& reg : datos) {
            reporte << nombre << " " << reg.nombreArchivo << " -> " 
                    << std::fixed << std::setprecision(6) << reg.tiempoMs << " ms | " 
                    << reg.memoriaKB << " KB\n";
        }
        reporte << "\n";
    }

    reporte << "=== FIN DE RESULTADOS ===\n";
    reporte << "Generado el: " << __DATE__ << " " << __TIME__ << "\n";

    return 0;
}