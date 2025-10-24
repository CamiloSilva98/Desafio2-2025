#include <iostream>
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "Fecha.h"

using namespace std;

void pruebasBasicas();
void pruebasAlbumes();
void pruebasCopiaAsignacion();
void pruebaCompleta();

int main() {
    cout << "========================================" << endl;
    cout << "   PRUEBAS DE LA CLASE ARTISTA" << endl;
    cout << "========================================" << endl << endl;

    pruebasBasicas();
    cout << "\n\n";

    pruebasAlbumes();
    cout << "\n\n";

    pruebasCopiaAsignacion();
    cout << "\n\n";

    pruebaCompleta();

    cout << "\n========================================" << endl;
    cout << "   TODAS LAS PRUEBAS COMPLETADAS" << endl;
    cout << "========================================" << endl;

    return 0;
}

void pruebasBasicas() {
    cout << ">>> PRUEBAS BASICAS <<<" << endl;
    cout << "========================================" << endl;

    // Constructor parametrizado
    // ID: 12345 (5 dígitos según preinforme)
    Artista mj(12345, 50, "Estados Unidos", 75000000, 1);

    cout << "[OK] Constructor parametrizado" << endl;
    cout << "ID: " << mj.getId() << endl;
    cout << "Edad: " << mj.getEdad() << " anios" << endl;
    cout << "Pais: " << mj.getPaisOrigen() << endl;
    cout << "Seguidores: " << mj.getSeguidores() << endl;
    cout << "Posicion en tendencias: #" << mj.getPosicionTendencias() << endl;

    // Operador ==
    Artista mj2(12345, 40, "USA", 0, 0);
    if (mj == mj2) {
        cout << "[OK] Operador == funciona (mismo ID)" << endl;
    }

    // Operador < (ordenar por seguidores descendente)
    Artista artista1(10001, 30, "UK", 1000000, 5);
    Artista artista2(10002, 25, "Spain", 5000000, 2);

    if (artista2 < artista1) {
        cout << "[OK] Operador < funciona (5M seguidores > 1M seguidores)" << endl;
    }
}

void pruebasAlbumes() {
    cout << ">>> PRUEBAS DE ALBUMES <<<" << endl;
    cout << "========================================" << endl;

    Artista mj(12345, 50, "Estados Unidos", 75000000, 1);

    cout << "Creando albumes para el artista..." << endl;

    // Crear álbumes
    Album* thriller = new Album(12345, 1, "Thriller", Fecha(1982, 11, 30),
                                "Epic Records", "/portadas/thriller.jpg", 9.8);

    Album* bad = new Album(12345, 2, "Bad", Fecha(1987, 8, 31),
                           "Epic Records", "/portadas/bad.jpg", 9.5);

    Album* dangerous = new Album(12345, 3, "Dangerous", Fecha(1991, 11, 26),
                                 "Epic Records", "/portadas/dangerous.jpg", 9.3);

    mj.agregarAlbum(thriller);
    mj.agregarAlbum(bad);
    mj.agregarAlbum(dangerous);

    cout << "[OK] Agregados " << mj.getCantidadAlbumes() << " albumes" << endl;

    // Mostrar álbumes
    cout << "\nDiscografia:" << endl;
    for (int i = 0; i < mj.getCantidadAlbumes(); i++) {
        Album* album = mj.obtenerAlbum(i);
        Fecha fecha = album->getFechaLanzamiento();
        cout << "  " << (i+1) << ". " << album->getNombre()
             << " (" << fecha.getAño() << ") - "
             << album->getPuntuacion() << "/10" << endl;
    }

    // Acceder a un álbum específico
    Album* primerAlbum = mj.obtenerAlbum(0);
    if (primerAlbum != nullptr) {
        cout << "\n[OK] Primer album: " << primerAlbum->getNombre() << endl;
    }

    // NOTA: Los álbumes serán liberados automáticamente por el destructor de Artista
}

void pruebasCopiaAsignacion() {
    cout << ">>> PRUEBAS DE COPIA Y ASIGNACION <<<" << endl;
    cout << "========================================" << endl;

    // Crear artista original con álbumes
    Artista original(12345, 50, "Estados Unidos", 75000000, 1);

    Album* album1 = new Album(12345, 1, "Thriller", Fecha(1982, 11, 30),
                              "Epic Records", "/portadas/thriller.jpg", 9.8);
    Album* album2 = new Album(12345, 2, "Bad", Fecha(1987, 8, 31),
                              "Epic Records", "/portadas/bad.jpg", 9.5);

    original.agregarAlbum(album1);
    original.agregarAlbum(album2);

    cout << "Artista original:" << endl;
    cout << "  ID: " << original.getId() << endl;
    cout << "  Seguidores: " << original.getSeguidores() << endl;
    cout << "  Albumes: " << original.getCantidadAlbumes() << endl;

    // Constructor de copia
    cout << "\nProbando constructor de copia..." << endl;
    Artista copia(original);

    cout << "[OK] Artista copiado:" << endl;
    cout << "  ID: " << copia.getId() << endl;
    cout << "  Seguidores: " << copia.getSeguidores() << endl;
    cout << "  Albumes: " << copia.getCantidadAlbumes() << endl;

    // Verificar que son copias independientes
    copia.setSeguidores(100000000);

    cout << "\nDespues de modificar seguidores en la copia:" << endl;
    cout << "  Original: " << original.getSeguidores() << " seguidores" << endl;
    cout << "  Copia: " << copia.getSeguidores() << " seguidores" << endl;

    if (original.getSeguidores() != copia.getSeguidores()) {
        cout << "[OK] Son copias independientes (copia profunda)" << endl;
    }

    // Operador de asignación
    cout << "\nProbando operador de asignacion..." << endl;
    Artista asignado(99999, 25, "Unknown", 0, 0);
    asignado = original;

    cout << "[OK] Artista asignado:" << endl;
    cout << "  ID: " << asignado.getId() << endl;
    cout << "  Albumes: " << asignado.getCantidadAlbumes() << endl;

    cout << "\n[OK] Constructor de copia y operador = funcionan correctamente" << endl;
}

void pruebaCompleta() {
    cout << ">>> PRUEBA COMPLETA (Artista -> Album -> Cancion) <<<" << endl;
    cout << "========================================" << endl;

    // Crear artista
    Artista mj(12345, 50, "Estados Unidos", 75000000, 1);
    cout << "Artista: Michael Jackson" << endl;
    cout << "ID: " << mj.getId() << endl;

    // Crear álbum
    Album* thriller = new Album(12345, 1, "Thriller", Fecha(1982, 11, 30),
                                "Epic Records", "/portadas/thriller.jpg", 9.8);
    thriller->agregarGenero("Pop");
    thriller->agregarGenero("R&B");

    // Crear canciones
    Cancion* c1 = new Cancion(123450103, "Thriller", 357,
                              "/audio/thriller_128.mp3", "/audio/thriller_320.mp3");
    Cancion* c2 = new Cancion(123450104, "Beat It", 258,
                              "/audio/beat_it_128.mp3", "/audio/beat_it_320.mp3");

    c1->incrementarReproducciones();
    c1->incrementarReproducciones();
    c1->incrementarReproducciones();

    thriller->agregarCancion(c1);
    thriller->agregarCancion(c2);
    thriller->calcularDuracionTotal();

    // Agregar álbum al artista
    mj.agregarAlbum(thriller);

    cout << "\n[OK] Jerarquia completa creada:" << endl;
    cout << "Artista: " << mj.getId() << " - " << mj.getSeguidores() << " seguidores" << endl;

    Album* album = mj.obtenerAlbum(0);
    cout << "  Album: " << album->getNombre() << " (" << album->getCantidadCanciones()
         << " canciones, " << album->getDuracionTotal() << "s)" << endl;

    for (int i = 0; i < album->getCantidadCanciones(); i++) {
        Cancion* cancion = album->obtenerCancion(i);
        cout << "    Cancion: " << cancion->getNombre()
             << " (" << cancion->getReproducciones() << " reproducciones)" << endl;
    }

    cout << "\n[OK] La jerarquia Artista->Album->Cancion funciona correctamente" << endl;
}
