#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "Plataforma.h"
#include <iostream>
#include <string>

using namespace std;

class Interfaz {
private:
    Plataforma* plataforma;

    // Métodos de visualización
    void mostrarEncabezado(const string& titulo);
    void mostrarSeparador();
    void limpiarPantalla();
    void pausar();

    // Métodos de entrada
    int leerOpcion();
    string leerTexto(const string& prompt);
    int leerEntero(const string& prompt);

    // Menús principales
    void menuPrincipal();
    void menuLogin();

public:
    // Constructor y destructor
    Interfaz();
    ~Interfaz();

    // Método principal
    void iniciar();
};

#endif // INTERFAZ_H
