#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <string>
#include "Arreglo.h"
#include "Cancion.h"

using namespace std;

class ListaFavoritos {
private:
    ArregloDinamico<Cancion*> canciones;
    string usuarioDueño;
    const int MAX_CANCIONES = 10000;  // Límite según preinforme

public:
    // Constructor por defecto
    ListaFavoritos();

    // Constructor parametrizado
    ListaFavoritos(string usuarioDueño);

    // Constructor de copia
    ListaFavoritos(const ListaFavoritos& otra);

    // Destructor
    ~ListaFavoritos();

    // Sobrecarga de operadores
    bool operator==(const ListaFavoritos& otra) const;
    ListaFavoritos& operator=(const ListaFavoritos& otra);

    // Métodos principales
    bool agregar(Cancion* cancion);  // Retorna false si está llena o duplicada
    bool eliminar(int idCancion);    // Elimina por ID de canción
    bool contiene(int idCancion) const;  // Verifica si existe la canción
    Cancion* obtenerCancion(int indice) const;

    // Métodos de búsqueda
    int buscarIndicePorId(int idCancion) const;

    // Getters
    int getCantidad() const;
    string getUsuarioDueño() const;
    bool estaLlena() const;
    bool estaVacia() const;

    // Setters
    void setUsuarioDueño(string usuario);
};

#endif // LISTAFAVORITOS_H
