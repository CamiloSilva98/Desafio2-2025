#include "Interfaz.h"
#include "Medidor.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
Interfaz::Interfaz() {
    plataforma = new Plataforma();
}

// Destructor
Interfaz::~Interfaz() {
    delete plataforma;
}

// Mostrar encabezado decorado
void Interfaz::mostrarEncabezado(const string& titulo) {
    cout << "\n|----------------------------------------------|" << endl;
    cout << "|         " << titulo;

    // Rellenar espacios para centrar
    int espacios = 37 - titulo.length();
    for (int i = 0; i < espacios; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    cout << "|----------------------------------------------|" << endl;
}

// Mostrar separador
void Interfaz::mostrarSeparador() {
    cout << "|----------------------------------------------|" << endl;
}

// Limpiar pantalla (multiplataforma)
void Interfaz::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausar ejecución
void Interfaz::pausar() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Leer opción numérica
int Interfaz::leerOpcion() {
    int opcion;
    cout << "\n> Ingresa tu opcion: ";

    while (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Error] Entrada invalida. Intenta de nuevo: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcion;
}

// Leer texto
string Interfaz::leerTexto(const string& prompt) {
    string texto;
    cout << prompt;
    getline(cin, texto);
    return texto;
}

// Leer entero con validación
int Interfaz::leerEntero(const string& prompt) {
    int numero;
    cout << prompt;

    while (!(cin >> numero)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Error] Debes ingresar un número. Intenta de nuevo: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}

// Menú principal
void Interfaz::menuPrincipal() {
    limpiarPantalla();
    mostrarEncabezado("UDEATUNES - STREAMING MUSICAL");

    cout << "\n            Bienvenido a UdeATunes" << endl;
    cout << "        Tu plataforma de musica favorita\n" << endl;

    mostrarSeparador();
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Acerca de" << endl;
    cout << "3. Salir" << endl;
    mostrarSeparador();
}

// Menú de login
void Interfaz::menuLogin() {
    limpiarPantalla();
    mostrarEncabezado("INICIO DE SESION");
    cout << "\nIngresa tus credenciales para acceder a la plataforma.\n" << endl;
}

// Método principal de ejecución
void Interfaz::iniciar() {
    bool ejecutando = true;

    while (ejecutando) {
        menuPrincipal();
        int opcion = leerOpcion();

        switch (opcion) {
        case 1:
            // Login y ejecución de la plataforma
            menuLogin();
            plataforma->ejecutar();
            break;

        case 2:
            limpiarPantalla();
            mostrarEncabezado("    ACERCA DE UDEATUNES");
            cout << "\n UdeATunes v1.0" << endl;
            cout << "   Sistema de gestion de streaming musical" << endl;
            cout << "\n Desarrollado por:" << endl;
            cout << "   - Brayan Camilo Silva Porras" << endl;
            cout << "   - Hamilton Alexander Suarez Perez" << endl;
            cout << "\n Universidad de Antioquia" << endl;
            cout << "   Informatica 2 - 2025-2" << endl;
            pausar();
            break;

        case 3:
            limpiarPantalla();
            mostrarEncabezado("       HASTA PRONTO!");
            cout << "\n           Gracias por usar UdeATunes" << endl;
            cout << "         Vuelve pronto por mas musica!\n" << endl;
            cout << "|----------------------------------------------|";
            ejecutando = false;
            break;

        default:
            cout << "\n[Error] Opción invalida. Intenta de nuevo." << endl;
            pausar();
            break;
        }
    }
}
