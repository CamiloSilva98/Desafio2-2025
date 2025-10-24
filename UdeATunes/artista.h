#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include "Arreglo.h"
#include "Album.h"

using namespace std;

class Artista {
private:
    int id;  // 5 dígitos
    int edad;
    string paisOrigen;
    int seguidores;
    int posicionTendencias;
    ArregloDinamico<Album*> albumes;

public:
    // Constructor por defecto
    Artista();

    // Constructor parametrizado
    Artista(int id, int edad, string paisOrigen, int seguidores, int posicionTendencias);

    // Constructor de copia
    Artista(const Artista& otro);

    // Destructor
    ~Artista();

    // Sobrecarga de operadores
    bool operator==(const Artista& otro) const;
    bool operator<(const Artista& otro) const;
    Artista& operator=(const Artista& otro);

    // Métodos de álbumes
    void agregarAlbum(Album* album);
    Album* obtenerAlbum(int indice) const;
    int getCantidadAlbumes() const;

    // Getters
    int getId() const;
    int getEdad() const;
    string getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionTendencias() const;

    // Setters con validación
    void setId(int id);
    void setEdad(int edad);
    void setPaisOrigen(string pais);
    void setSeguidores(int seguidores);
    void setPosicionTendencias(int posicion);
};

#endif // ARTISTA_H
