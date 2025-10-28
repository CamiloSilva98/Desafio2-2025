#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <string>
#include "GestorDatos.h"
#include "Reproductor.h"
#include "Usuario.h"
#include "Cancion.h"
#include "Artista.h"
#include "Publicidad.h"
#include "Arreglo.h"

using namespace std;

class Plataforma {
private:
    GestorDatos* gestorDatos;
    Reproductor* reproductor;
    Usuario* usuarioActivo;
    bool sesionActiva;

    // Datos en memoria
    ArregloDinamico<Usuario*> usuarios;
    ArregloDinamico<Artista*> artistas;
    ArregloDinamico<Publicidad*> publicidades;

    // Métodos privados de menús
    void menuUsuarioEstandar();
    void menuUsuarioPremium();

    // Funcionalidades comunes
    void reproduccionAleatoria();
    void reproduccionManual();
    void verHistorialReproduccion();
    void buscarCancion();

    // Funcionalidades premium
    void gestionarFavoritos();
    void agregarAFavoritos();
    void eliminarDeFavoritos();
    void verFavoritos();
    void seguirListaOtroUsuario();
    void reproducirFavoritos();

    // Métodos auxiliares
    void mostrarBienvenida();
    void mostrarDespedida();
    bool autenticar();
    void cerrarSesion();
    Cancion* buscarCancionPorId(int id);
    Usuario* buscarUsuarioPorNickname(const string& nickname);
    void limpiarBuffer();

public:
    // Constructor y destructor
    Plataforma();
    ~Plataforma();

    // Método principal
    void ejecutar();

    // Métodos de inicialización
    bool inicializar();
    void finalizar();

    // Getters para acceso externo
    Usuario* getUsuarioActivo();
    bool hayUsuarioActivo() const;
};

#endif // PLATAFORMA_H
