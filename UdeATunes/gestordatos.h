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
    // Rutas de los archivos
    string rutaUsuarios;
    string rutaArtistas;
    string rutaAlbumes;
    string rutaCanciones;
    string rutaCreditos;
    string rutaPublicidad;
    string rutaFavoritos;

    // Métodos auxiliares privados
    ArregloDinamico<string> parsearLinea(string linea, char delimitador);
    Fecha parsearFecha(string fecha);  // Formato: año-mes-día

public:
    // Constructor
    GestorDatos();

    // Constructor con rutas personalizadas
    GestorDatos(string carpetaData);

    // Destructor
    ~GestorDatos();

    // Métodos de carga (leer archivos → objetos en memoria)
    void cargarUsuarios(ArregloDinamico<Usuario*>& usuarios);
    void cargarArtistas(ArregloDinamico<Artista*>& artistas);
    void cargarAlbumes(ArregloDinamico<Artista*>& artistas);  // Asocia álbumes a artistas
    void cargarCanciones(ArregloDinamico<Artista*>& artistas);  // Asocia canciones a álbumes
    void cargarCreditos(ArregloDinamico<Artista*>& artistas);  // Asocia créditos a canciones
    void cargarPublicidad(ArregloDinamico<Publicidad*>& publicidades);
    void cargarFavoritos(ArregloDinamico<Usuario*>& usuarios, ArregloDinamico<Artista*>& artistas);

    // Métodos de guardado (objetos en memoria → archivos)
    void guardarUsuarios(ArregloDinamico<Usuario*>& usuarios);
    void guardarArtistas(ArregloDinamico<Artista*>& artistas);
    void guardarAlbumes(ArregloDinamico<Artista*>& artistas);
    void guardarCanciones(ArregloDinamico<Artista*>& artistas);
    void guardarCreditos(ArregloDinamico<Artista*>& artistas);
    void guardarPublicidad(ArregloDinamico<Publicidad*>& publicidades);
    void guardarFavoritos(ArregloDinamico<Usuario*>& usuarios);

    // Método para guardar todo
    void guardarTodo(ArregloDinamico<Usuario*>& usuarios,
                     ArregloDinamico<Artista*>& artistas,
                     ArregloDinamico<Publicidad*>& publicidades);

    // Método para cargar todo
    void cargarTodo(ArregloDinamico<Usuario*>& usuarios,
                    ArregloDinamico<Artista*>& artistas,
                    ArregloDinamico<Publicidad*>& publicidades);

    // Métodos de búsqueda auxiliares
    Cancion* buscarCancionPorId(ArregloDinamico<Artista*>& artistas, int idCancion);
    Usuario* buscarUsuarioPorNickname(ArregloDinamico<Usuario*>& usuarios, string nickname);

    // Validación
    bool validarIntegridad();
};

#endif // GESTORDATOS_H
