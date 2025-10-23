#include <iostream>
#include "Arreglo.h"
#include "Credito.h"
#include "Fecha.h"

using namespace std;

void pruebasBasicas();
void pruebasConEnteros();
void pruebasConPunteros();
void pruebasConObjetos();
void pruebasRedimensionamiento();

int main() {
    cout << "========================================" << endl;
    cout << "   PRUEBAS ARREGLODINAMICO<T>" << endl;
    cout << "========================================" << endl << endl;

    pruebasBasicas();
    cout << "\n\n";

    pruebasConEnteros();
    cout << "\n\n";

    pruebasConPunteros();
    cout << "\n\n";

    pruebasConObjetos();
    cout << "\n\n";

    pruebasRedimensionamiento();

    cout << "\n========================================" << endl;
    cout << "   TODAS LAS PRUEBAS COMPLETADAS" << endl;
    cout << "========================================" << endl;

    return 0;
}

void pruebasBasicas() {
    cout << ">>> PRUEBAS BASICAS <<<" << endl;
    cout << "========================================" << endl;

    ArregloDinamico<int> arr;

    cout << "[OK] Constructor: Capacidad inicial = " << arr.getCapacidad()
         << ", Cantidad = " << arr.getCantidad() << endl;

    if (arr.estaVacio()) {
        cout << "[OK] Arreglo esta vacio al inicio" << endl;
    }

    // Agregar elementos
    arr.agregar(10);
    arr.agregar(20);
    arr.agregar(30);

    cout << "[OK] Se agregaron 3 elementos. Cantidad = " << arr.getCantidad() << endl;

    // Obtener elementos
    cout << "[OK] Elementos: " << arr.obtener(0) << ", "
         << arr.obtener(1) << ", " << arr.obtener(2) << endl;
}

void pruebasConEnteros() {
    cout << ">>> PRUEBAS CON ENTEROS <<<" << endl;
    cout << "========================================" << endl;

    ArregloDinamico<int> numeros;

    // Agregar números
    for (int i = 1; i <= 5; i++) {
        numeros.agregar(i * 10);
    }

    cout << "[OK] Agregados 5 numeros" << endl;
    cout << "Contenido: ";
    for (int i = 0; i < numeros.getCantidad(); i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Modificar un elemento
    numeros.modificar(2, 999);
    cout << "[OK] Modificado indice 2 a 999: " << numeros[2] << endl;

    // Eliminar un elemento
    numeros.eliminar(1);
    cout << "[OK] Eliminado indice 1. Nueva cantidad: " << numeros.getCantidad() << endl;
    cout << "Contenido: ";
    for (int i = 0; i < numeros.getCantidad(); i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Constructor de copia
    ArregloDinamico<int> copia(numeros);
    cout << "[OK] Constructor de copia. Cantidad: " << copia.getCantidad() << endl;

    // Operador de asignación
    ArregloDinamico<int> asignado;
    asignado = numeros;
    cout << "[OK] Operador de asignacion. Cantidad: " << asignado.getCantidad() << endl;
}

void pruebasConPunteros() {
    cout << ">>> PRUEBAS CON PUNTEROS (Credito*) <<<" << endl;
    cout << "========================================" << endl;

    ArregloDinamico<Credito*> creditos;

    // Crear y agregar créditos
    Credito* c1 = new Credito("Juan", "Perez", "PROD-001", "productor");
    Credito* c2 = new Credito("Maria", "Garcia", "MUS-002", "musico");
    Credito* c3 = new Credito("Carlos", "Lopez", "COMP-003", "compositor");

    creditos.agregar(c1);
    creditos.agregar(c2);
    creditos.agregar(c3);

    cout << "[OK] Agregados 3 creditos (punteros)" << endl;

    // Acceder a los créditos
    cout << "Creditos en el arreglo:" << endl;
    for (int i = 0; i < creditos.getCantidad(); i++) {
        Credito* c = creditos[i];
        cout << "  " << i << ". " << c->getNombre() << " " << c->getApellido()
             << " (" << c->getTipo() << ")" << endl;
    }

    // Buscar un crédito específico
    cout << "[OK] Segundo credito (indice 1): " << creditos[1]->getNombre()
         << " " << creditos[1]->getApellido() << endl;

    // Limpiar memoria
    for (int i = 0; i < creditos.getCantidad(); i++) {
        delete creditos[i];
    }
    cout << "[OK] Memoria de creditos liberada" << endl;
}

void pruebasConObjetos() {
    cout << ">>> PRUEBAS CON OBJETOS (Fecha) <<<" << endl;
    cout << "========================================" << endl;

    ArregloDinamico<Fecha> fechas;

    // Agregar fechas
    fechas.agregar(Fecha(2025, 1, 15));
    fechas.agregar(Fecha(2024, 6, 20));
    fechas.agregar(Fecha(2023, 12, 31));

    cout << "[OK] Agregadas 3 fechas" << endl;

    // Mostrar fechas
    cout << "Fechas en el arreglo:" << endl;
    for (int i = 0; i < fechas.getCantidad(); i++) {
        Fecha f = fechas[i];
        cout << "  " << f.getAño() << "/" << f.getMes() << "/" << f.getDia() << endl;
    }

    // Ordenar usando operador <
    cout << "\nComparando fechas:" << endl;
    if (fechas[2] < fechas[1] && fechas[1] < fechas[0]) {
        cout << "[OK] Las fechas estan en orden cronologico inverso" << endl;
    }
}

void pruebasRedimensionamiento() {
    cout << ">>> PRUEBAS DE REDIMENSIONAMIENTO <<<" << endl;
    cout << "========================================" << endl;

    ArregloDinamico<int> arr;

    cout << "Capacidad inicial: " << arr.getCapacidad() << endl;

    // Agregar más elementos que la capacidad inicial (10)
    cout << "Agregando 15 elementos..." << endl;
    for (int i = 1; i <= 15; i++) {
        arr.agregar(i);
        if (i == 10) {
            cout << "  Capacidad despues de 10 elementos: " << arr.getCapacidad() << endl;
        }
    }

    cout << "[OK] Capacidad final: " << arr.getCapacidad()
         << " (factor 1.5x aplicado)" << endl;
    cout << "[OK] Cantidad de elementos: " << arr.getCantidad() << endl;

    // Verificar que todos los elementos se guardaron correctamente
    bool todosCorrectos = true;
    for (int i = 0; i < arr.getCantidad(); i++) {
        if (arr[i] != i + 1) {
            todosCorrectos = false;
            break;
        }
    }

    if (todosCorrectos) {
        cout << "[OK] Todos los elementos se mantuvieron correctos despues del redimensionamiento" << endl;
    } else {
        cout << "[ERROR] Algunos elementos se perdieron en el redimensionamiento" << endl;
    }

    // Limpiar
    arr.limpiar();
    cout << "[OK] Arreglo limpiado. Cantidad: " << arr.getCantidad()
         << ", Capacidad: " << arr.getCapacidad() << " (mantiene capacidad)" << endl;
}
