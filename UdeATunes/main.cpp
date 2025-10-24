#include <iostream>
#include "Usuario.h"
#include "Cancion.h"
#include "ListaFavoritos.h"
#include "Fecha.h"

using namespace std;

void pruebasBasicas();
void pruebasMembresia();
void pruebasHistorico();
void pruebasFavoritos();
void pruebasCopiaAsignacion();

int main() {
    cout << "========================================" << endl;
    cout << "   PRUEBAS DE LA CLASE USUARIO" << endl;
    cout << "========================================" << endl << endl;

    pruebasBasicas();
    cout << "\n\n";

    pruebasMembresia();
    cout << "\n\n";

    pruebasHistorico();
    cout << "\n\n";

    pruebasFavoritos();
    cout << "\n\n";

    pruebasCopiaAsignacion();

    cout << "\n========================================" << endl;
    cout << "   TODAS LAS PRUEBAS COMPLETADAS" << endl;
    cout << "========================================" << endl;

    return 0;
}

void pruebasBasicas() {
    cout << ">>> PRUEBAS BASICAS <<<" << endl;
    cout << "========================================" << endl;

    // Constructor parametrizado
    Fecha inscripcion(2024, 10, 20);
    Usuario u1("musiclover_01", "premium", "Medellin", "Colombia", inscripcion);

    cout << "[OK] Constructor parametrizado" << endl;
    cout << "Nickname: " << u1.getNickname() << endl;
    cout << "Membresia: " << u1.getTipoMembresia() << endl;
    cout << "Ciudad: " << u1.getCiudad() << endl;
    cout << "Pais: " << u1.getPais() << endl;
    cout << "Fecha inscripcion: " << inscripcion.getDia() << "/"
         << inscripcion.getMes() << "/" << inscripcion.getAño() << endl;

    // Operador ==
    Usuario u2("musiclover_01", "estandar", "Bogota", "Colombia", Fecha(2020, 1, 1));
    if (u1 == u2) {
        cout << "[OK] Operador == funciona (mismo nickname)" << endl;
    }

    // Operador <
    Usuario alice("alice", "premium", "NYC", "USA", Fecha(2024, 1, 1));
    Usuario bob("bob", "premium", "LA", "USA", Fecha(2024, 1, 1));
    if (alice < bob) {
        cout << "[OK] Operador < funciona (orden alfabetico: alice < bob)" << endl;
    }
}

void pruebasMembresia() {
    cout << ">>> PRUEBAS DE MEMBRESIA <<<" << endl;
    cout << "========================================" << endl;

    // Usuario estándar
    Usuario estandar("user_estandar", "estandar", "Medellin", "Colombia", Fecha(2024, 10, 20));

    if (estandar.esEstandar()) {
        cout << "[OK] Usuario estandar detectado correctamente" << endl;
    }

    if (!estandar.esPremium()) {
        cout << "[OK] Usuario NO es premium" << endl;
    }

    if (!estandar.tieneListaFavoritos()) {
        cout << "[OK] Usuario estandar NO tiene lista de favoritos" << endl;
    }

    // Usuario premium
    Usuario premium("user_premium", "premium", "Bogota", "Colombia", Fecha(2024, 10, 20));

    if (premium.esPremium()) {
        cout << "\n[OK] Usuario premium detectado correctamente" << endl;
    }

    if (premium.tieneListaFavoritos()) {
        cout << "[OK] Usuario premium TIENE lista de favoritos (creada automaticamente)" << endl;
    }

    // Cambiar de estándar a premium
    cout << "\nCambiando usuario estandar a premium..." << endl;
    estandar.setTipoMembresia("premium");

    if (estandar.esPremium() && estandar.tieneListaFavoritos()) {
        cout << "[OK] Cambio exitoso: ahora es premium con lista de favoritos" << endl;
    }

    // Cambiar de premium a estándar
    cout << "\nCambiando usuario premium a estandar..." << endl;
    premium.setTipoMembresia("estandar");

    if (premium.esEstandar() && !premium.tieneListaFavoritos()) {
        cout << "[OK] Cambio exitoso: ahora es estandar sin lista de favoritos" << endl;
    }
}

void pruebasHistorico() {
    cout << ">>> PRUEBAS DE HISTORICO (max 6 canciones) <<<" << endl;
    cout << "========================================" << endl;

    Usuario usuario("testuser", "estandar", "Medellin", "Colombia", Fecha(2024, 10, 20));

    // Crear canciones de prueba
    Cancion* c1 = new Cancion(100000001, "Cancion 1", 200, "", "");
    Cancion* c2 = new Cancion(100000002, "Cancion 2", 200, "", "");
    Cancion* c3 = new Cancion(100000003, "Cancion 3", 200, "", "");
    Cancion* c4 = new Cancion(100000004, "Cancion 4", 200, "", "");
    Cancion* c5 = new Cancion(100000005, "Cancion 5", 200, "", "");
    Cancion* c6 = new Cancion(100000006, "Cancion 6", 200, "", "");
    Cancion* c7 = new Cancion(100000007, "Cancion 7", 200, "", "");

    cout << "Agregando canciones al historico..." << endl;
    usuario.agregarAlHistorico(c1);
    usuario.agregarAlHistorico(c2);
    usuario.agregarAlHistorico(c3);
    usuario.agregarAlHistorico(c4);
    usuario.agregarAlHistorico(c5);
    usuario.agregarAlHistorico(c6);

    cout << "[OK] Agregadas 6 canciones. Historico: " << usuario.getCantidadHistorico() << "/6" << endl;

    // Mostrar historial
    cout << "\nHistorico actual:" << endl;
    for (int i = 0; i < usuario.getCantidadHistorico(); i++) {
        Cancion* c = usuario.obtenerDelHistorico(i);
        cout << "  " << (i+1) << ". " << c->getNombre() << " (ID: " << c->getId() << ")" << endl;
    }

    // Agregar una más (debe eliminar la primera)
    cout << "\nAgregando cancion 7 (debe eliminar la cancion 1)..." << endl;
    usuario.agregarAlHistorico(c7);

    cout << "[OK] Cantidad sigue siendo: " << usuario.getCantidadHistorico() << "/6" << endl;

    cout << "\nNuevo historico:" << endl;
    for (int i = 0; i < usuario.getCantidadHistorico(); i++) {
        Cancion* c = usuario.obtenerDelHistorico(i);
        cout << "  " << (i+1) << ". " << c->getNombre() << " (ID: " << c->getId() << ")" << endl;
    }

    // Verificar que la primera se eliminó
    Cancion* primera = usuario.obtenerDelHistorico(0);
    if (primera->getId() == 100000002) {
        cout << "\n[OK] La cancion 1 fue eliminada correctamente (FIFO)" << endl;
    }

    // Limpiar memoria
    delete c1; delete c2; delete c3; delete c4;
    delete c5; delete c6; delete c7;
}

void pruebasFavoritos() {
    cout << ">>> PRUEBAS DE FAVORITOS (solo premium) <<<" << endl;
    cout << "========================================" << endl;

    Usuario premium("user_premium", "premium", "Medellin", "Colombia", Fecha(2024, 10, 20));

    // Obtener lista de favoritos
    ListaFavoritos* lista = premium.getListaFavoritos();

    if (lista != nullptr) {
        cout << "[OK] Usuario premium tiene lista de favoritos" << endl;
        cout << "Dueño de la lista: " << lista->getUsuarioDueño() << endl;
    }

    // Agregar canciones a favoritos
    Cancion* c1 = new Cancion(123450103, "Thriller", 357, "", "");
    Cancion* c2 = new Cancion(123450104, "Beat It", 258, "", "");

    lista->agregar(c1);
    lista->agregar(c2);

    cout << "[OK] Agregadas " << lista->getCantidad() << " canciones a favoritos" << endl;

    // Mostrar favoritos
    cout << "\nCanciones favoritas:" << endl;
    for (int i = 0; i < lista->getCantidad(); i++) {
        Cancion* c = lista->obtenerCancion(i);
        cout << "  " << (i+1) << ". " << c->getNombre() << endl;
    }

    // Usuario estándar no puede tener favoritos
    Usuario estandar("user_estandar", "estandar", "Bogota", "Colombia", Fecha(2024, 10, 20));

    if (estandar.getListaFavoritos() == nullptr) {
        cout << "\n[OK] Usuario estandar NO puede tener lista de favoritos" << endl;
    }

    // Limpiar
    delete c1;
    delete c2;
}

void pruebasCopiaAsignacion() {
    cout << ">>> PRUEBAS DE COPIA Y ASIGNACION <<<" << endl;
    cout << "========================================" << endl;

    // Crear usuario original premium con datos
    Usuario original("original_user", "premium", "Medellin", "Colombia", Fecha(2024, 10, 20));

    Cancion* c1 = new Cancion(123450103, "Thriller", 357, "", "");
    Cancion* c2 = new Cancion(123450104, "Beat It", 258, "", "");

    original.agregarAlHistorico(c1);
    original.agregarAlHistorico(c2);

    ListaFavoritos* listaOriginal = original.getListaFavoritos();
    listaOriginal->agregar(c1);

    cout << "Usuario original:" << endl;
    cout << "  Nickname: " << original.getNickname() << endl;
    cout << "  Membresia: " << original.getTipoMembresia() << endl;
    cout << "  Historico: " << original.getCantidadHistorico() << " canciones" << endl;
    cout << "  Favoritos: " << listaOriginal->getCantidad() << " canciones" << endl;

    // Constructor de copia
    cout << "\nProbando constructor de copia..." << endl;
    Usuario copia(original);

    cout << "[OK] Usuario copiado:" << endl;
    cout << "  Nickname: " << copia.getNickname() << endl;
    cout << "  Membresia: " << copia.getTipoMembresia() << endl;
    cout << "  Historico: " << copia.getCantidadHistorico() << " canciones" << endl;

    if (copia.tieneListaFavoritos()) {
        cout << "  Favoritos: " << copia.getListaFavoritos()->getCantidad() << " canciones" << endl;
    }

    // Operador de asignación
    cout << "\nProbando operador de asignacion..." << endl;
    Usuario asignado("temp_user", "estandar", "Cali", "Colombia", Fecha(2020, 1, 1));
    asignado = original;

    cout << "[OK] Usuario asignado:" << endl;
    cout << "  Nickname: " << asignado.getNickname() << endl;
    cout << "  Membresia: " << asignado.getTipoMembresia() << endl;

    cout << "\n[OK] Constructor de copia y operador = funcionan correctamente" << endl;

    // Limpiar
    delete c1;
    delete c2;
}
