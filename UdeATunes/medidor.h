#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <iostream>
using namespace std;

class Medidor {
private:
    inline static long long iteracionesTotales = 0;
    inline static long long memoriaTotal = 0;

public:
    static void incrementarIteraciones(long long cantidad = 1) {
        iteracionesTotales += cantidad;
    }

    static void sumarMemoria(long long bytes) {
        memoriaTotal += bytes;
    }

    static void restarMemoria(long long bytes) {
        memoriaTotal -= bytes;
        if (memoriaTotal < 0) {
            memoriaTotal = 0;
        }
    }

    static long long obtenerIteraciones() {
        return iteracionesTotales;
    }

    static long long obtenerMemoria() {
        return memoriaTotal;
    }

    static void resetear() {
        iteracionesTotales = 0;
    }

    static void mostrarMetricas() {
        cout << "\n========================================" << endl;
        cout << "       METRICAS DE EFICIENCIA" << endl;
        cout << "========================================" << endl;
        cout << "Iteraciones ejecutadas: " << iteracionesTotales << endl;
        cout << "Memoria consumida: " << memoriaTotal << " bytes";

        if (memoriaTotal >= 1024) {
            double kb = memoriaTotal / 1024.0;
            cout << " (" << kb << " KB)";
        }

        if (memoriaTotal >= 1048576) {
            double mb = memoriaTotal / 1048576.0;
            cout << " (" << mb << " MB)";
        }

        cout << endl;
        cout << "========================================\n" << endl;
    }
};

#endif // MEDIDOR_H
