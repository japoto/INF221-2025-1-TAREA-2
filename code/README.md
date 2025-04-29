# Documentación
Los algoritmos utilizados en este proyecto han sido debidamente citados dentro de los archivos de código fuente, en formato de comentario estructurado.

## Multiplicación de matrices

Multiplicación clásica (Naive Multiply): basada en el algoritmo tradicional de triple bucle.

Multiplicación de Strassen: basada en la técnica optimizada de divide y vencerás.

Ambos métodos utilizan estructuras de vectores (`std::vector`) para el manejo de matrices.

### Programa principal
El programa principal es `matrix_multiplication`, acompañado de un `Makefile` que automatiza la compilación y ejecución de todos los casos de prueba, midiendo tanto el tiempo de ejecución como el uso de memoria.  
**Nota:** Para la correcta ejecución, se recomienda utilizar un entorno compatible como **WSL (Windows Subsystem for Linux)**.

### Scripts
Los scripts de generación de datos fueron proporcionados por los ayudantes y **no se realizaron modificaciones** sobre ellos.  
Para ejecutar los scripts de generación de gráficos, es necesario tener instaladas las siguientes dependencias:

```bash
pip install matplotlib
pip install numpy
```

## Ordenamiento de arreglo unidimensional

Selection Sort: algoritmo simple de ordenamiento por selección.

Merge Sort: algoritmo de ordenamiento por mezcla (divide y vencerás).

QuickSort optimizado: implementado con "mediana de tres" y optimización mediante Insertion Sort para subarreglos pequeños.

Sort STL (`std::sort`): función estándar de la STL de C++.

### Programa principal
El programa principal es `sorting`, acompañado de un `Makefile` que automatiza la compilación y ejecución de todos los casos de prueba, midiendo tanto el tiempo de ejecución como el uso de memoria.  
**Nota:** Para la correcta ejecución, se recomienda utilizar un entorno compatible como **WSL (Windows Subsystem for Linux)**.

### Scripts
Los scripts de generación de datos fueron proporcionados por los ayudantes y **no se realizaron modificaciones** sobre ellos.  
Para ejecutar los scripts de generación de gráficos, es necesario tener instaladas las siguientes dependencias:

```bash
pip install matplotlib
pip install numpy
```
