#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <string>
#include <fstream>
#include "Arreglo.h"
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "Credito.h"
#include "Publicidad.h"
#include "Fecha.h"

using namespace std;

class GestorDatos {
private:
    ArregloDinamico<Usuario*> usuarios;
    ArregloDinamico<Artista*> artistas;
    ArregloDinamico<Publicidad*> publicidades;

    // Paths de archivos
    const string PATH_USUARIOS = "usuarios.txt";
    const string PATH_ARTISTAS = "artistas.txt";
    const string PATH_ALBUMES = "albumes.txt";
    const string PATH_CANCIONES = "canciones.txt";
    const string PATH_CREDITOS = "creditos.txt";
    const string PATH_PUBLICIDAD = "publicidad.txt";
    const string PATH_FAVORITOS = "favoritos.txt";

    // Métodos privados de carga
    bool cargarUsuarios();
    bool cargarArtistas();
    bool cargarAlbumes();
    bool cargarCanciones();
    bool cargarCreditos();
    bool cargarPublicidad();
    bool cargarFavoritos();

    // Métodos privados de guardado
    bool guardarUsuarios();
    bool guardarArtistas();
    bool guardarAlbumes();
    bool guardarCanciones();
    bool guardarCreditos();
    bool guardarPublicidad();
    bool guardarFavoritos();

    // Métodos auxiliares
    ArregloDinamico<string> dividirCadena(const string& cadena, char delimitador);
    Fecha parsearFecha(const string& fechaStr);

    // Búsquedas auxiliares
    Artista* buscarArtistaPorId(int id);
    Album* buscarAlbum(int idArtista, int idAlbum);
    Cancion* buscarCancionPorId(int id);

public:
    // Constructor y destructor
    GestorDatos();
    ~GestorDatos();

    // Métodos principales
    bool cargarDatos();
    bool guardarDatos();

    // Búsqueda de usuarios
    Usuario* buscarUsuario(const string& nickname);

    // Getters para acceso a datos
    ArregloDinamico<Usuario*>& getUsuarios();
    ArregloDinamico<Artista*>& getArtistas();
    ArregloDinamico<Publicidad*>& getPublicidades();
};

#endif // GESTORDATOS_H
