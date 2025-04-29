CXX = g++  # Compilador
CXXFLAGS = -std=c++17 -O2 -Ialgorithms  # Flags para el compilador

# Archivos fuente
SRC = sorting.cpp algorithms/selectionsort.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/sort.cpp algorithms/MemoryTracker.cpp

# Archivos objeto
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable
TARGET = sorting

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)  # Compila y enlaza el ejecutable

# Regla para compilar archivos en la carpeta algorithms
algorithms/%.o: algorithms/%.cpp algorithms/MemoryTracker.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuera de la carpeta algorithms
%.o: %.cpp algorithms/MemoryTracker.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar MemoryTracker.cpp específicamente
algorithms/MemoryTracker.o: algorithms/MemoryTracker.cpp algorithms/MemoryTracker.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)  # Elimina el ejecutable y objetos intermedi