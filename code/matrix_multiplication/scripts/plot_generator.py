import matplotlib.pyplot as plt
import numpy as np
import os
import re
from collections import defaultdict

# ==== CONFIGURACIÓN GENERAL ====

# Ruta del archivo de datos
INPUT_FILE = 'C:/Users/japoto/Desktop/INF221-2025-1-TAREA-1/code/matrix_multiplication/data/measurements/bench.txt'

# Carpeta donde se guardarán los gráficos
OUTPUT_FOLDER = 'C:/Users/japoto/Desktop/INF221-2025-1-TAREA-1/code/matrix_multiplication/data/plots'

# Crear carpeta si no existe
os.makedirs(OUTPUT_FOLDER, exist_ok=True)

# Colores por algoritmo
COLORS = {'naive': 'blue', 'strassen': 'green'}

# ==== FUNCIÓN PARA LEER Y ORGANIZAR LOS DATOS ====

def leer_datos(filepath):
    data = defaultdict(lambda: defaultdict(list))
    pattern = r'(\w+)\s(\d+)_([a-zA-Z]+)_D\d+_\w+ -> ([\d\.]+) ms \| (\d+) KB'
    
    with open(filepath, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    for line in lines:
        match = re.match(pattern, line.strip())
        if match:
            algoritmo = match.group(1)  # naive o strassen
            tamano = int(match.group(2))  # tamaño matriz
            tipo_matriz = match.group(3)  # densa, diagonal, dispersa
            tiempo = float(match.group(4))  # tiempo en ms
            memoria = int(match.group(5))  # memoria en KB

            data[tipo_matriz][algoritmo].append((tamano, tiempo, memoria))
    
    return data


def graficar_comparativo_global(datos, output_folder):
    plt.figure(figsize=(10, 8))

    # Consolidar datos por algoritmo
    datos_algoritmos = defaultdict(list)

    for datos_tipo in datos.values():
        for algoritmo, entradas in datos_tipo.items():
            datos_algoritmos[algoritmo].extend(entradas)

    # Gráfico de tiempo de ejecución
    plt.subplot(2, 1, 1)
    for algoritmo, entradas in datos_algoritmos.items():
        entradas_ordenadas = sorted(entradas, key=lambda x: x[0])
        tamanos = [e[0] for e in entradas_ordenadas]
        tiempos = [e[1] for e in entradas_ordenadas]
        plt.plot(tamanos, tiempos, 'o-', label=algoritmo, color=COLORS.get(algoritmo, 'black'))

    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Tamaño matriz (n x n)')
    plt.ylabel('Tiempo (ms)')
    plt.title('Comparación global de tiempo (sin separar tipos de matriz)')
    plt.legend()
    plt.grid(True)

    # Gráfico de memoria
    plt.subplot(2, 1, 2)
    for algoritmo, entradas in datos_algoritmos.items():
        entradas_ordenadas = sorted(entradas, key=lambda x: x[0])
        tamanos = [e[0] for e in entradas_ordenadas]
        memorias = [e[2] for e in entradas_ordenadas]
        plt.plot(tamanos, memorias, 'o-', label=algoritmo, color=COLORS.get(algoritmo, 'black'))

    plt.xscale('log')
    plt.xlabel('Tamaño matriz (n x n)')
    plt.ylabel('Memoria (KB)')
    plt.title('Comparación global de memoria (sin separar tipos de matriz)')
    plt.legend()
    plt.grid(True)

    # Guardar figura
    plt.tight_layout()
    filename = f"{output_folder}/comparacion_global_algoritmos.png"
    plt.savefig(filename)
    plt.close()
    print(f"Gráfico comparativo global (solo por algoritmo) guardado en: {filename}")
# ==== FUNCIÓN PARA GRAFICAR POR TIPO DE MATRIZ ====

def graficar_tipo_matriz(tipo_matriz, datos, output_folder):
    plt.figure(figsize=(14, 6))

    # Subgráfico 1: Tiempo
    plt.subplot(1, 2, 1)
    for algoritmo, entradas in datos.items():
        entradas_ordenadas = sorted(entradas, key=lambda x: x[0])
        tamanos = [e[0] for e in entradas_ordenadas]
        tiempos = [e[1] for e in entradas_ordenadas]
        plt.plot(tamanos, tiempos, 'o-', label=algoritmo, color=COLORS.get(algoritmo, 'black'))

    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Tamaño matriz (n x n)')
    plt.ylabel('Tiempo (ms)')
    plt.title(f'Tiempo de ejecución - {tipo_matriz.capitalize()}')
    plt.legend()
    plt.grid(True)

    # Subgráfico 2: Memoria
    plt.subplot(1, 2, 2)
    for algoritmo, entradas in datos.items():
        entradas_ordenadas = sorted(entradas, key=lambda x: x[0])
        tamanos = [e[0] for e in entradas_ordenadas]
        memorias = [e[2] for e in entradas_ordenadas]
        plt.plot(tamanos, memorias, 'o-', label=algoritmo, color=COLORS.get(algoritmo, 'black'))

    plt.xscale('log')
    plt.xlabel('Tamaño matriz (n x n)')
    plt.ylabel('Memoria (KB)')
    plt.title(f'Consumo de memoria - {tipo_matriz.capitalize()}')
    plt.legend()
    plt.grid(True)

    # Guardar figura
    plt.tight_layout()
    filename = f"{output_folder}/{tipo_matriz}_plots.png"
    plt.savefig(filename)
    plt.close()
    print(f"Gráficos de '{tipo_matriz}' guardados en: {filename}")

# ==== FUNCIÓN PRINCIPAL ====

def main():
    datos = leer_datos(INPUT_FILE)

    for tipo_matriz, datos_tipo in datos.items():
        graficar_tipo_matriz(tipo_matriz, datos_tipo, OUTPUT_FOLDER)
    graficar_comparativo_global(datos, OUTPUT_FOLDER)
if __name__ == "__main__":
    main()