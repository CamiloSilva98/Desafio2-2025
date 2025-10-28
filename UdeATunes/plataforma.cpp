#include "Plataforma.h"
#include "Medidor.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
Plataforma::Plataforma() {
    gestorDatos = new GestorDatos();
    reproductor = nullptr;
    usuarioActivo = nullptr;
    sesionActiva = false;
}

// Destructor
Plataforma::~Plataforma() {
    if (reproductor != nullptr) {
        delete reproductor;
    }

    // Liberar usuarios
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        delete usuarios.obtener(i);
    }

    // Liberar artistas (también libera álbumes y canciones)
    for (int i = 0; i < artistas.getCantidad(); i++) {
        delete artistas.obtener(i);
    }

    // Liberar publicidades
    for (int i = 0; i < publicidades.getCantidad(); i++) {
        delete publicidades.obtener(i);
    }

    delete gestorDatos;
}

// Inicializar sistema
bool Plataforma::inicializar() {
    cout << "\n[Sistema] Cargando datos desde archivos..." << endl;

    gestorDatos->cargarTodo(usuarios, artistas, publicidades);

    if (usuarios.getCantidad() == 0 || artistas.getCantidad() == 0) {
        cout << "[Error] No se pudieron cargar los datos del sistema." << endl;
        return false;
    }

    cout << "[Sistema]  Datos cargados exitosamente." << endl;
    return true;
}

// Finalizar sistema
void Plataforma::finalizar() {
    cout << "\n[Sistema] Guardando cambios..." << endl;

    gestorDatos->guardarTodo(usuarios, artistas, publicidades);

    cout << "[Sistema]  Cambios guardados correctamente." << endl;
}

// Limpiar buffer de entrada
void Plataforma::limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Autenticación de usuario
bool Plataforma::autenticar() {
    string nickname;
    bool usuarioEncontrado = false;

    cout << "\n|----------------------------------------------|\n";
    cout << "|             INICIO DE SESION UdeATunes       |\n";
    cout << "|----------------------------------------------|\n";

    int intentos = 0;

    do {
        cout << "\n> Ingresa tu nickname: ";
        getline(cin, nickname);

        usuarioActivo = buscarUsuarioPorNickname(nickname);

        if (usuarioActivo == nullptr) {
            cout << "\n|----------------------------------------------|\n";
            cout << "|  Usuario no encontrado. Intenta nuevamente.  |\n";
            cout << "|----------------------------------------------|\n";

            intentos++;
        } else {
            usuarioEncontrado = true;
        }

    } while (!usuarioEncontrado);
    return true;
}


// Cerrar sesión
void Plataforma::cerrarSesion() {
    if (reproductor != nullptr) {
        delete reproductor;
        reproductor = nullptr;
    }

    usuarioActivo = nullptr;
    sesionActiva = false;

    cout << "\n[Sistema] Sesion cerrada correctamente." << endl;
}

// Mostrar bienvenida personalizada
void Plataforma::mostrarBienvenida() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|           BIENVENIDO A UDEATUNES!            |" << endl;
    cout << "|----------------------------------------------|" << endl;

    cout << "\n Usuario: " << usuarioActivo->getNickname() << endl;
    cout << " Ubicacion: " << usuarioActivo->getCiudad() << ", "
         << usuarioActivo->getPais() << endl;
    cout << " Membresia: " << usuarioActivo->getTipoMembresia() << endl;


    if (usuarioActivo->esPremium()) {
        cout << "\n Disfruta de tus beneficios premium:" << endl;
        cout << "    Sin publicidad" << endl;
        cout << "    Audio en alta calidad (320 kbps)" << endl;
        cout << "    Listas de favoritos personalizadas" << endl;
        cout << "    Retroceder hasta 4 canciones" << endl;
    } else {
        cout << "\n Actualiza a Premium y disfruta:" << endl;
        cout << "    Sin anuncios publicitarios" << endl;
        cout << "    Mejor calidad de audio" << endl;
        cout << "    Listas de favoritos ilimitadas" << endl;
    }

    cout << "\n" << endl;
}

// Mostrar despedida
void Plataforma::mostrarDespedida() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|          ¡GRACIAS POR USAR UDEATUNES!            |" << endl;
    cout << "|----------------------------------------------|" << endl;

    cout << "\n Nos vemos pronto, " << usuarioActivo->getNickname() << "!" << endl;
    cout << "   Tu musica te espera.\n" << endl;
}

// MENÚ USUARIO ESTÁNDAR
void Plataforma::menuUsuarioEstandar() {
    bool enMenu = true;

    while (enMenu && sesionActiva) {
        cout << "\n|----------------------------------------------|" << endl;
        cout << "    MENU PRINCIPAL - Usuario Estandar"   << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "1. Reproduccion aleatoria (modo automatico)" << endl;
        cout << "2. Reproduccion manual con controles" << endl;
        cout << "3. Ver historial de reproduccion" << endl;
        cout << "4. Buscar cancion" << endl;
        cout << "5. Cerrar sesion" << endl;
        cout << "|----------------------------------------------|" << endl;

        int opcion;
        cout << "\n> Opcion: ";
        cin >> opcion;
        limpiarBuffer();

        Medidor::resetear();

        switch (opcion) {
        case 1:
            reproduccionAleatoria();
            Medidor::mostrarMetricas();
            break;

        case 2:
            reproduccionManual();
            Medidor::mostrarMetricas();
            break;

        case 3:
            verHistorialReproduccion();
            Medidor::mostrarMetricas();
            break;

        case 4:
            buscarCancion();
            Medidor::mostrarMetricas();
            break;

        case 5:
            mostrarDespedida();
            cerrarSesion();
            enMenu = false;
            break;

        default:
            cout << "[Error] Opcion invalida." << endl;
            break;
        }
    }
}

// MENÚ USUARIO PREMIUM
void Plataforma::menuUsuarioPremium() {
    bool enMenu = true;

    while (enMenu && sesionActiva) {
        cout << "\n|----------------------------------------------|" << endl;
        cout << "      MENU PREMIUM    " << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "1. Reproduccion aleatoria (modo automatico)" << endl;
        cout << "2. Reproduccion manual con controles avanzados" << endl;
        cout << "3. Ver historial de reproduccion" << endl;
        cout << "4. Buscar cancion" << endl;
        cout << "5. Gestionar lista de favoritos" << endl;
        cout << "6. Reproducir favoritos" << endl;
        cout << "7. Seguir lista de otro usuario" << endl;
        cout << "8. Cerrar sesion" << endl;
        cout << "|----------------------------------------------|" << endl;

        int opcion;
        cout << "\n> Opcion: ";
        cin >> opcion;
        limpiarBuffer();

        Medidor::resetear();

        switch (opcion) {
        case 1:
            reproduccionAleatoria();
            Medidor::mostrarMetricas();
            break;

        case 2:
            reproduccionManual();
            Medidor::mostrarMetricas();
            break;

        case 3:
            verHistorialReproduccion();
            Medidor::mostrarMetricas();
            break;

        case 4:
            buscarCancion();
            Medidor::mostrarMetricas();
            break;

        case 5:
            gestionarFavoritos();
            Medidor::mostrarMetricas();
            break;

        case 6:
            reproducirFavoritos();
            Medidor::mostrarMetricas();
            break;

        case 7:
            seguirListaOtroUsuario();
            Medidor::mostrarMetricas();
            break;

        case 8:
            mostrarDespedida();
            cerrarSesion();
            enMenu = false;
            break;

        default:
            cout << "[Error] Opcion invalida." << endl;
            break;
        }
    }
}

// Reproducción aleatoria automática
void Plataforma::reproduccionAleatoria() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|     REPRODUCCION ALEATORIA AUTOMATICA        |" << endl;
    cout << "|----------------------------------------------|" << endl;

    reproductor->reproduccionAleatoriaTemporizador();
}

// Reproducción manual con controles
void Plataforma::reproduccionManual() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|       REPRODUCCION MANUAL CON CONTROLES      |" << endl;
    cout << "|----------------------------------------------|" << endl;

    reproductor->iniciarReproduccionManual();

    bool reproduciendo = true;
    while (reproduciendo && reproductor->estaReproduciendo()) {
        cout << "\n|----------------------------------------------|" << endl;
        cout << "  CONTROLES" << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "1. Siguiente" << endl;

        if (usuarioActivo->esPremium()) {
            cout << "2. Anterior (Premium)" << endl;
            cout << "3. Repetir ON/OFF (Premium)" << endl;
        }

        cout << "4. Detener y salir" << endl;
        cout << "|----------------------------------------------|" << endl;

        int opcion;
        cout << "\n> Opción: ";
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
        case 1:
            reproductor->siguiente();
            break;

        case 2:
            if (usuarioActivo->esPremium()) {
                reproductor->anterior();
            } else {
                cout << "[Error] Funcion exclusiva para usuarios Premium." << endl;
            }
            break;

        case 3:
            if (usuarioActivo->esPremium()) {
                reproductor->toggleRepetir();
            } else {
                cout << "[Error] Funcion exclusiva para usuarios Premium." << endl;
            }
            break;

        case 4:
            reproductor->detenerReproduccion();
            reproduciendo = false;
            break;

        default:
            cout << "[Error] Opcion invalida." << endl;
            break;
        }
    }
}

// Ver historial de reproducción
void Plataforma::verHistorialReproduccion() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|        HISTORIAL DE REPRODUCCION             |" << endl;
    cout << "|----------------------------------------------|" << endl;

    if (usuarioActivo->getCantidadHistorico() == 0) {
        cout << "\n[Info] Aun no has reproducido ninguna cancion." << endl;
        return;
    }

    cout << "\nUltimas canciones reproducidas:\n" << endl;

    for (int i = usuarioActivo->getCantidadHistorico() - 1; i >= 0; i--) {
        Medidor::incrementarIteraciones();
        Cancion* cancion = usuarioActivo->obtenerDelHistorico(i);

        if (cancion != nullptr) {
            cout << (usuarioActivo->getCantidadHistorico() - i) << ". "
                 << cancion->getNombre() << " (ID: " << cancion->getId() << ")" << endl;
        }
    }
}

// Buscar canción por ID
void Plataforma::buscarCancion() {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|                BUSCAR CANCION                |" << endl;
    cout << "|----------------------------------------------|" << endl;

    int id;
    cout << "\n> Ingresa el ID de la cancion (9 digitos): ";
    cin >> id;
    limpiarBuffer();

    Cancion* cancion = buscarCancionPorId(id);

    if (cancion == nullptr) {
        cout << "\n[Error] No se encuntra ninguna canción con ese ID." << endl;
        return;
    }

    cout << "\n|----------------------------------------------|" << endl;
    cout << "|  CANCION ENCONTRADA                          |" << endl;
    cout << "|----------------------------------------------|" << endl;
    cout << "| Titulo: " << cancion->getNombre() << endl;
    cout << "| ID: " << cancion->getId() << endl;
    cout << "| Duracion: " << cancion->getDuracion() << " segundos" << endl;
    cout << "| Reproducciones: " << cancion->getReproducciones() << endl;
    cout << "|----------------------------------------------|" << endl;
}

// Buscar canción por ID (método auxiliar)
Cancion* Plataforma::buscarCancionPorId(int id) {
    return gestorDatos->buscarCancionPorId(artistas, id);
}

// Buscar usuario por nickname
Usuario* Plataforma::buscarUsuarioPorNickname(const string& nickname) {
    return gestorDatos->buscarUsuarioPorNickname(usuarios, nickname);
}

// GESTIONAR FAVORITOS (PREMIUM)
void Plataforma::gestionarFavoritos() {
    bool enSubmenu = true;

    while (enSubmenu) {
        cout << "\n|----------------------------------------------|" << endl;
        cout << "|       GESTION DE LISTA DE FAVORITOS          |" << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "| 1. Ver mis favoritos                         |" << endl;
        cout << "| 2. Agregar canción a favoritos               |" << endl;
        cout << "| 3. Eliminar cancion de favoritos             |" << endl;
        cout << "| 4. Volver al menu principal                  |" << endl;
        cout << "|----------------------------------------------|" << endl;

        int opcion;
        cout << "\n> Opcion: ";
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
        case 1:
            verFavoritos();
            break;

        case 2:
            agregarAFavoritos();
            break;

        case 3:
            eliminarDeFavoritos();
            break;

        case 4:
            enSubmenu = false;
            break;

        default:
            cout << "[Error] Opcion invalida." << endl;
            break;
        }
    }
}

// Ver favoritos
void Plataforma::verFavoritos() {
    ListaFavoritos* lista = usuarioActivo->getListaFavoritos();

    if (lista == nullptr || lista->estaVacia()) {
        cout << "\n[Info] Tu lista de favoritos esta vacía." << endl;
        return;
    }

    cout << "\n🎵 MI LISTA DE FAVORITOS (" << lista->getCantidad() << "/10000)" << endl;
    cout << "|----------------------------------------------|\n" << endl;

    for (int i = 0; i < lista->getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Cancion* cancion = lista->obtenerCancion(i);

        if (cancion != nullptr) {
            cout << (i + 1) << ". " << cancion->getNombre()
            << " (ID: " << cancion->getId() << ")" << endl;
        }
    }
}

// Agregar a favoritos
void Plataforma::agregarAFavoritos() {
    ListaFavoritos* lista = usuarioActivo->getListaFavoritos();

    if (lista == nullptr) {
        cout << "[Error] No tienes una lista de favoritos creada." << endl;
        return;
    }

    if (lista->estaLlena()) {
        cout << "[Error] Tu lista de favoritos está llena (10,000 canciones)." << endl;
        return;
    }

    int id;
    cout << "\n> Ingresa el ID de la canción a agregar: ";
    cin >> id;
    limpiarBuffer();

    Cancion* cancion = buscarCancionPorId(id);

    if (cancion == nullptr) {
        cout << "[Error] No se encontro una canción con ese ID." << endl;
        return;
    }

    if (lista->contiene(id)) {
        cout << "[Error] Esta cancion ya esta en tus favoritos." << endl;
        return;
    }

    if (lista->agregar(cancion)) {
        cout << "\n Cancion agregada a favoritos: " << cancion->getNombre() << endl;
    } else {
        cout << "[Error] No se pudo agregar la cancion." << endl;
    }
}

// Eliminar de favoritos
void Plataforma::eliminarDeFavoritos() {
    ListaFavoritos* lista = usuarioActivo->getListaFavoritos();

    if (lista == nullptr || lista->estaVacia()) {
        cout << "[Info] Tu lista de favoritos esta vacia." << endl;
        return;
    }

    int id;
    cout << "\n> Ingresa el ID de la cancion a eliminar: ";
    cin >> id;
    limpiarBuffer();

    if (lista->eliminar(id)) {
        cout << "\n Cancion eliminada de favoritos." << endl;
    } else {
        cout << "[Error] No se encontro esa cancion en tus favoritos." << endl;
    }
}

// Reproducir favoritos
void Plataforma::reproducirFavoritos() {
    ListaFavoritos* lista = usuarioActivo->getListaFavoritos();

    if (lista == nullptr || lista->estaVacia()) {
        cout << "[Info] Tu lista de favoritos esta vacia." << endl;
        return;
    }

    cout << "\n¿Como deseas reproducir tus favoritos?" << endl;
    cout << "1. En orden original" << endl;
    cout << "2. Modo aleatorio" << endl;

    int opcion;
    cout << "\n> Opcion: ";
    cin >> opcion;
    limpiarBuffer();

    bool modoAleatorio = (opcion == 2);
    reproductor->reproducirFavoritos(modoAleatorio);
}

// Seguir lista de otro usuario
void Plataforma::seguirListaOtroUsuario() {
    string nickname;
    cout << "\n> Ingresa el nickname del usuario premium a seguir: ";
    getline(cin, nickname);

    Usuario* otroUsuario = buscarUsuarioPorNickname(nickname);

    if (otroUsuario == nullptr || !otroUsuario->esPremium()) {
        cout << "[Error] No se encuntra un usuario premium con ese nickname." << endl;
        return;
    }

    ListaFavoritos* listaOtro = otroUsuario->getListaFavoritos();

    if (listaOtro == nullptr || listaOtro->estaVacia()) {
        cout << "[Info] Ese usuario no tiene canciones en favoritos." << endl;
        return;
    }

    ListaFavoritos* miLista = usuarioActivo->getListaFavoritos();

    if (miLista == nullptr) {
        cout << "[Error] No tienes una lista de favoritos creada." << endl;
        return;
    }

    int agregadas = 0;

    for (int i = 0; i < listaOtro->getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Cancion* cancion = listaOtro->obtenerCancion(i);

        if (cancion != nullptr && !miLista->contiene(cancion->getId())) {
            if (miLista->agregar(cancion)) {
                agregadas++;
            }
        }

        if (miLista->estaLlena()) {
            break;
        }
    }

    cout << "\n Se agregaron " << agregadas << " canciones nuevas a tus favoritos." << endl;
}

// MÉTODO PRINCIPAL: EJECUTAR
void Plataforma::ejecutar() {
    if (!inicializar()) {
        return;
    }

    if (!autenticar()) {
        return;
    }

    mostrarBienvenida();

    cout << "Presiona ENTER para continuar...";
    cin.get();

    if (usuarioActivo->esPremium()) {
        menuUsuarioPremium();
    } else {
        menuUsuarioEstandar();
    }

    finalizar();
}

// Getters
Usuario* Plataforma::getUsuarioActivo() {
    return usuarioActivo;
}

bool Plataforma::hayUsuarioActivo() const {
    return usuarioActivo != nullptr && sesionActiva;
}
