# Suma de Arreglos Paralela con OpenMP

Programa en C++ que realiza la suma de dos arreglos de 1000 elementos utilizando programación paralela con OpenMP.

## Compilación

### Visual Studio
1. Abrir el archivo `.cpp` en Visual Studio
2. Ir a **Proyecto > Propiedades > C/C++ > Lenguaje**
3. Establecer **Compatibilidad con Open MP** en **Sí (/openmp)**
4. Compilar y ejecutar

### Línea de comandos (MSVC)
```
cl /openmp suma_arreglos_paralela.cpp
```

### g++ (MinGW / Linux)
```
g++ -fopenmp -o suma_arreglos_paralela suma_arreglos_paralela.cpp
```

### CMake
```
mkdir build && cd build
cmake ..
cmake --build .
```
