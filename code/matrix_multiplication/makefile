# Configuración del compilador
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDFLAGS := 

# Detección del sistema operativo
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
    LDFLAGS += -lpsapi
else
    SYSTEM := $(shell uname -s)
endif

# Directorios
ALG_DIR := algorithms
DATA_DIR := data
BIN_DIR := .

# Archivos fuente
MAIN_SRC := matrix_multiplication.cpp
ALG_SRC := $(ALG_DIR)/naive.cpp $(ALG_DIR)/strassen.cpp

# Archivos objeto
MAIN_OBJ := $(MAIN_SRC:.cpp=.o)
ALG_OBJ := $(ALG_SRC:.cpp=.o)
ALL_OBJ := $(MAIN_OBJ) $(ALG_OBJ)

# Nombre del ejecutable
TARGET := matrix_multiplication

# Regla principal
all: $(TARGET)

# Enlazar el ejecutable
$(TARGET): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar archivo principal
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar algoritmos (los .o se quedan en algorithms/)
$(ALG_DIR)/%.o: $(ALG_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	rm -f $(TARGET) $(ALL_OBJ)

# Limpiar y recompilar
rebuild: clean all

# Ejecutar
run: all
	./$(TARGET)

.PHONY: all clean rebuild run