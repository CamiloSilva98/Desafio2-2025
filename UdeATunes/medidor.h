#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <iostream>
using namespace std;

/**
 * Clase estática para medir eficiencia del sistema
 * - Cuenta iteraciones en bucles
 * - Suma memoria consumida por objetos
 * - Muestra métricas al finalizar funcionalidades
 */
class Medidor {
private:
    static long long iteracionesTotales;
    static long long memoriaTotal;

public:
    // Incrementar contador de iteraciones
    static void incrementarIteraciones(long long cantidad = 1)
    {
        iteracionesTotales += cantidad;
    }

    // Registrar memoria asignada
    static void sumarMemoria(long long bytes)
    {
        memoriaTotal += bytes;
    }

    // Registrar memoria liberada
    static void restarMemoria(long long bytes)
    {
        memoriaTotal -= bytes;
        if (memoriaTotal < 0)
        {
            memoriaTotal = 0;  // Protección
        }
    }

    // Obtener total de iteraciones
    static long long obtenerIteraciones()
    {
        return iteracionesTotales;
    }

    // Obtener total de memoria
    static long long obtenerMemoria()
    {
        return memoriaTotal;
    }

    // Resetear métricas de iteraciones (usar al inicio de cada funcionalidad)
    static void resetear()
    {
        iteracionesTotales = 0;
        // NO resetear memoria, es acumulativa del sistema
    }

    // Mostrar métricas formateadas
    static void mostrarMetricas()
    {
        cout << "\n========================================" << endl;
        cout << "       METRICAS DE EFICIENCIA" << endl;
        cout << "========================================" << endl;
        cout << "Iteraciones ejecutadas: " << iteracionesTotales << endl;
        cout << "Memoria consumida: " << memoriaTotal << " bytes";

        // Mostrar en KB si es grande
        if (memoriaTotal >= 1024)
        {
            double kb = memoriaTotal / 1024.0;
            cout << " (" << kb << " KB)";
        }

        // Mostrar en MB si es muy grande
        if (memoriaTotal >= 1048576)
        {
            double mb = memoriaTotal / 1048576.0;
            cout << " (" << mb << " MB)";
        }

        cout << endl;
        cout << "========================================\n" << endl;
    }
};

// Inicialización de variables estáticas
long long Medidor::iteracionesTotales = 0;
long long Medidor::memoriaTotal = 0;

#endif // MEDIDOR_H
