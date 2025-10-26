#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <chrono>
using namespace std;
using namespace std::chrono;

class Medidor {
private:
    steady_clock::time_point inicio, fin;

public:
    void iniciar() { inicio = steady_clock::now(); }
    void detener() { fin = steady_clock::now(); }

    double obtenerSegundos() const {
        return duration_cast<duration<double>>(fin - inicio).count();
    }

    void mostrarTiempo(const string& etiqueta) const {
        cout << etiqueta << ": " << obtenerSegundos() << " segundos" << endl;
    }
};

#endif
