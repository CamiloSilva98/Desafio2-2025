//#include <iostream>
#include "Interfaz.h"
using namespace std;
/**
 * UDEATUNES - Sistema de Gestión de Streaming Musical
 *
 * Desarrollado por:
 * - Hamilton Alexander Suárez Pérez
 * - Brayan Camilo Silva Porras
 *
 *
 * Universidad de Antioquia
 * Informática 2 - 2025-2
 */
int main()
{
    Interfaz* interfaz = new Interfaz();
    interfaz->iniciar();
    delete interfaz;
    return 0;
}
