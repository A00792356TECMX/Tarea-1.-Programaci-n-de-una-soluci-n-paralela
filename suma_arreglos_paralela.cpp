#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    const int N = 1000;
    int A[N], B[N], R[N], R_sec[N];

    // Arreglo para registrar que hilo proceso cada indice
    int hilo_asignado[N];

    srand(static_cast<unsigned>(time(nullptr)));

    // Inicializar arreglos A y B con valores aleatorios entre 1 y 100
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100 + 1;
        B[i] = rand() % 100 + 1;
    }

    int num_threads = omp_get_max_threads();
    cout << "=============================================" << endl;
    cout << "  SUMA DE ARREGLOS PARALELA CON OpenMP" << endl;
    cout << "=============================================" << endl;
    cout << "Numero de hilos disponibles: " << num_threads << endl;
    cout << "Tamano de los arreglos: " << N << endl;
    cout << endl;

    // =============================================
    // 1. SUMA SECUENCIAL (un solo hilo)
    // =============================================
    double inicio_sec = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        R_sec[i] = A[i] + B[i];
    }

    double fin_sec = omp_get_wtime();
    double tiempo_sec = fin_sec - inicio_sec;

    // =============================================
    // 2. SUMA PARALELA (multiples hilos)
    // =============================================
    double inicio_par = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        R[i] = A[i] + B[i];
        hilo_asignado[i] = omp_get_thread_num();
    }

    double fin_par = omp_get_wtime();
    double tiempo_par = fin_par - inicio_par;

    // =============================================
    // 3. VERIFICACION DE RESULTADOS
    // =============================================
    cout << "--- Primeros 20 elementos ---" << endl;
    cout << "Indice\tA\tB\tR (A+B)\tHilo" << endl;
    cout << "------\t---\t---\t-------\t----" << endl;
    for (int i = 0; i < 20; i++) {
        cout << i << "\t" << A[i] << "\t" << B[i] << "\t" << R[i]
             << "\t" << hilo_asignado[i] << endl;
    }

    cout << endl;
    cout << "--- Ultimos 5 elementos ---" << endl;
    cout << "Indice\tA\tB\tR (A+B)\tHilo" << endl;
    cout << "------\t---\t---\t-------\t----" << endl;
    for (int i = N - 5; i < N; i++) {
        cout << i << "\t" << A[i] << "\t" << B[i] << "\t" << R[i]
             << "\t" << hilo_asignado[i] << endl;
    }

    // Validar resultados
    bool correcto = true;
    for (int i = 0; i < N; i++) {
        if (R[i] != A[i] + B[i]) {
            correcto = false;
            cout << "Error en el indice " << i << endl;
            break;
        }
    }

    cout << endl;
    if (correcto) {
        cout << "Verificacion: Todos los " << N << " resultados son correctos." << endl;
    } else {
        cout << "Verificacion: Se encontraron errores." << endl;
    }

    // =============================================
    // 4. COMPARACION DE TIEMPOS
    // =============================================
    cout << endl;
    cout << "=============================================" << endl;
    cout << "  COMPARACION DE TIEMPOS" << endl;
    cout << "=============================================" << endl;
    cout << "Tiempo secuencial (1 hilo):    " << tiempo_sec << " segundos" << endl;
    cout << "Tiempo paralelo (" << num_threads << " hilos):    " << tiempo_par << " segundos" << endl;
    if (tiempo_par > 0) {
        cout << "Speedup:                       " << tiempo_sec / tiempo_par << "x" << endl;
    }

    // =============================================
    // 5. DISTRIBUCION DE TRABAJO POR HILO
    // =============================================
    cout << endl;
    cout << "=============================================" << endl;
    cout << "  DISTRIBUCION DE TRABAJO POR HILO" << endl;
    cout << "=============================================" << endl;

    for (int t = 0; t < num_threads; t++) {
        int primero = -1, ultimo = -1, conteo = 0;
        for (int i = 0; i < N; i++) {
            if (hilo_asignado[i] == t) {
                if (primero == -1) primero = i;
                ultimo = i;
                conteo++;
            }
        }
        cout << "  Hilo " << t << ": indices [" << primero << " - " << ultimo
             << "] -> " << conteo << " elementos" << endl;
    }

    return 0;
}
