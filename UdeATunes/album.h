#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Arreglo.h"
#include "Cancion.h"
#include "Fecha.h"

using namespace std;

class Album {
private:
    int idArtista;  // 5 dígitos del artista
    int idAlbum;    // 2 dígitos del álbum
    string nombre;
    ArregloDinamico<string> generos;
    Fecha fechaLanzamiento;
    int duracionTotal;  // En segundos
    string selloDisco;
    string rutaPortada;
    float puntuacion;
    ArregloDinamico<Cancion*> canciones;

public:
    // Constructor por defecto
    Album();

    // Constructor parametrizado
    Album(int idArtista, int idAlbum, string nombre, Fecha fechaLanzamiento,
          string selloDisco, string rutaPortada, float puntuacion);

    // Constructor de copia
    Album(const Album& otro);

    // Destructor
    ~Album();

    // Sobrecarga de operadores
    bool operator==(const Album& otro) const;
    bool operator<(const Album& otro) const;
    Album& operator=(const Album& otro);

    // Métodos de canciones
    void agregarCancion(Cancion* cancion);
    Cancion* obtenerCancion(int indice) const;
    int getCantidadCanciones() const;

    // Métodos de géneros
    void agregarGenero(string genero);
    string obtenerGenero(int indice) const;
    int getCantidadGeneros() const;

    // Métodos de cálculo
    void calcularDuracionTotal();

    // Getters
    int getIdArtista() const;
    int getIdAlbum() const;
    string getNombre() const;
    Fecha getFechaLanzamiento() const;
    int getDuracionTotal() const;
    string getSelloDisco() const;
    string getRutaPortada() const;
    float getPuntuacion() const;

    // Setters con validación
    void setIdArtista(int idArtista);
    void setIdAlbum(int idAlbum);
    void setNombre(string nombre);
    void setFechaLanzamiento(Fecha fecha);
    void setDuracionTotal(int duracion);
    void setSelloDisco(string sello);
    void setRutaPortada(string ruta);
    void setPuntuacion(float puntuacion);
};

#endif // ALBUM_H
