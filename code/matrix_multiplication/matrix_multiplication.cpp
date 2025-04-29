#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <map>
#include <ctime>
#include <iomanip>

namespace fs = std::filesystem;

using Matrix = std::vector<std::vector<int>>;

// Declaraciones de funciones de multiplicación (implementadas en otros archivos)
Matrix naiveMultiply(const Matrix& A, const Matrix& B);
Matrix strassenMultiply(const Matrix& A, const Matrix& B);

struct Resultado {
    std::string archivo;
    double tiempo;
    long memoria;
};

// Función mejorada para obtener memoria actual
long obtenerMemoriaActual() {
    long memoria = 0;
    std::ifstream status("/proc/self/status");
    std::string linea;
    
    while (std::getline(status, linea)) {
        if (linea.rfind("VmRSS:", 0) == 0) {
            std::istringstream iss(linea);
            std::string etiqueta, tamanio, unidad;
            iss >> etiqueta >> tamanio >> unidad;
            memoria = std::stol(tamanio);
            break;
        }
    }
    return memoria;
}

// Función para limpieza profunda de memoria
void limpiezaProfundaMemoria() {
    std::vector<Matrix> temporal;
    temporal.reserve(10);
    for (int i = 0; i < 10; ++i) {
        temporal.emplace_back(100, std::vector<int>(100));
    }
    temporal.clear();
}

// Función para leer matrices desde archivo
Matrix leerMatriz(const std::string& path) {
    std::ifstream file(path);
    Matrix matriz;
    std::string linea;
    
    while (std::getline(file, linea)) {
        std::istringstream iss(linea);
        std::vector<int> fila;
        int valor;
        while (iss >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }
    return matriz;
}

// Función para guardar matrices en archivo
void guardarMatriz(const std::string& path, const Matrix& mat) {
    std::ofstream file(path);
    for (const auto& fila : mat) {
        for (size_t i = 0; i < fila.size(); ++i) {
            file << fila[i];
            if (i != fila.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
}

// Función principal de procesamiento
void procesarAlgoritmo(
    const std::string& nombreAlgoritmo,
    std::vector<Resultado>& resultados,
    const std::vector<std::string>& bases,
    Matrix (*func)(const Matrix&, const Matrix&)
) {
    for (const auto& base : bases) {
        // Limpieza inicial y medición de memoria base
        limpiezaProfundaMemoria();
        long memoriaInicial = obtenerMemoriaActual();
        
        // Cargar matrices de entrada
        Matrix M1 = leerMatriz("data/matrix_input/" + base + "_1.txt");
        Matrix M2 = leerMatriz("data/matrix_input/" + base + "_2.txt");
        
        // Limpieza antes de la medición principal
        limpiezaProfundaMemoria();
        memoriaInicial = obtenerMemoriaActual();
        
        // Medición de tiempo y ejecución
        auto inicio = std::chrono::high_resolution_clock::now();
        Matrix resultado = func(M1, M2);
        auto fin = std::chrono::high_resolution_clock::now();
        
        // Medición de memoria después de la ejecución
        long memoriaFinal = obtenerMemoriaActual();
        long memoriaUsada = memoriaFinal - memoriaInicial;
        
        // Cálculo de memoria teórica si la medición falla
        if (memoriaUsada <= 0) {
            size_t n = M1.size();
            memoriaUsada = (n * n * sizeof(int) * 3) / 1024; // 3 matrices en memoria
        }
        
        // Guardar resultados
        guardarMatriz("data/matrix_output/" + base + "_" + nombreAlgoritmo + ".txt", resultado);
        double tiempo = std::chrono::duration<double, std::milli>(fin - inicio).count();
        resultados.push_back({base, tiempo, memoriaUsada});
        
        // Mostrar resultados inmediatos
        std::cout << nombreAlgoritmo << " " << base << " -> " 
                 << std::fixed << std::setprecision(3) << tiempo << " ms | " 
                 << memoriaUsada << " KB\n";
        
        // Liberación cuidadosa de memoria
        M1.clear(); M1.shrink_to_fit();
        M2.clear(); M2.shrink_to_fit();
        resultado.clear(); resultado.shrink_to_fit();
    }
}

int main() {
    // Obtener lista de archivos de entrada
    std::vector<std::string> bases;
    for (const auto& entry : fs::directory_iterator("data/matrix_input")) {
        std::string filename = entry.path().filename().string();
        if (filename.find("_1.txt") != std::string::npos) {
            bases.push_back(filename.substr(0, filename.find("_1.txt")));
        }
    }

    // Procesar ambos algoritmos
    std::map<std::string, std::vector<Resultado>> mediciones;
    
    std::cout << "=== Inicio de mediciones ===" << std::endl;
    procesarAlgoritmo("naive", mediciones["naive"], bases, naiveMultiply);
    procesarAlgoritmo("strassen", mediciones["strassen"], bases, strassenMultiply);
    std::cout << "=== Mediciones completadas ===" << std::endl;

    // Guardar resultados en archivo
    std::ofstream salida("data/measurements/bench.txt");
    for (const auto& [algoritmo, res] : mediciones) {
        for (const auto& r : res) {
            salida << algoritmo << " " << r.archivo << " -> " 
                  << r.tiempo << " ms | " << r.memoria << " KB\n";
        }
    }

    return 0;
}