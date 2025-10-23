#ifndef ARREGLODINAMICO_H
#define ARREGLODINAMICO_H

#include <iostream>
using namespace std;

template <typename T>
class ArregloDinamico {
private:
    T* elementos;
    int cantidad;
    int capacidad;

    const int CAPACIDAD_INICIAL = 10;
    const float FACTOR_CRECIMIENTO = 1.5;

    // Método privado para redimensionar el arreglo
    void redimensionar();

public:
    // Constructor
    ArregloDinamico();

    // Constructor de copia
    ArregloDinamico(const ArregloDinamico<T>& otro);

    // Destructor
    ~ArregloDinamico();

    // Sobrecarga de operadores
    ArregloDinamico<T>& operator=(const ArregloDinamico<T>& otro);
    T& operator[](int indice);
    const T& operator[](int indice) const;

    // Métodos principales
    void agregar(T elemento);
    void eliminar(int indice);
    T obtener(int indice) const;
    void modificar(int indice, T elemento);

    // Getters
    int getCantidad() const;
    int getCapacidad() const;
    bool estaVacio() const;

    // Utilidades
    void limpiar();
    bool existe(int indice) const;
};

template <typename T>
ArregloDinamico<T>::ArregloDinamico() {
    capacidad = CAPACIDAD_INICIAL;
    cantidad = 0;
    elementos = new T[capacidad];
}

// Constructor de copia
template <typename T>
ArregloDinamico<T>::ArregloDinamico(const ArregloDinamico<T>& otro) {
    capacidad = otro.capacidad;
    cantidad = otro.cantidad;
    elementos = new T[capacidad];

    // Copiar cada elemento
    for (int i = 0; i < cantidad; i++) {
        elementos[i] = otro.elementos[i];
    }
}

// Destructor
template <typename T>
ArregloDinamico<T>::~ArregloDinamico() {
    delete[] elementos;
}

// Operador de asignación
template <typename T>
ArregloDinamico<T>& ArregloDinamico<T>::operator=(const ArregloDinamico<T>& otro) {
    if (this != &otro) {
        // Liberar memoria actual
        delete[] elementos;

        // Copiar datos del otro
        capacidad = otro.capacidad;
        cantidad = otro.cantidad;
        elementos = new T[capacidad];

        for (int i = 0; i < cantidad; i++) {
            elementos[i] = otro.elementos[i];
        }
    }
    return *this;
}

// Operador [] para acceso directo
template <typename T>
T& ArregloDinamico<T>::operator[](int indice) {
    if (indice < 0 || indice >= cantidad) {
        cerr << "Error: Indice fuera de rango" << endl;
        // Retornar el primero como fallback (no ideal, pero evita crash)
        return elementos[0];
    }
    return elementos[indice];
}

// Operador [] const
template <typename T>
const T& ArregloDinamico<T>::operator[](int indice) const {
    if (indice < 0 || indice >= cantidad) {
        cerr << "Error: Indice fuera de rango" << endl;
        return elementos[0];
    }
    return elementos[indice];
}

// Agregar elemento
template <typename T>
void ArregloDinamico<T>::agregar(T elemento) {
    // Si está lleno, redimensionar
    if (cantidad >= capacidad) {
        redimensionar();
    }

    elementos[cantidad] = elemento;
    cantidad++;
}

// Eliminar elemento por índice
template <typename T>
void ArregloDinamico<T>::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad) {
        cerr << "Error: Indice fuera de rango" << endl;
        return;
    }

    // Desplazar elementos hacia la izquierda
    for (int i = indice; i < cantidad - 1; i++) {
        elementos[i] = elementos[i + 1];
    }

    cantidad--;
}

// Obtener elemento
template <typename T>
T ArregloDinamico<T>::obtener(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        cerr << "Error: Indice fuera de rango" << endl;
        return T(); // Retorna valor por defecto del tipo T
    }
    return elementos[indice];
}

// Modificar elemento
template <typename T>
void ArregloDinamico<T>::modificar(int indice, T elemento) {
    if (indice < 0 || indice >= cantidad) {
        cerr << "Error: Indice fuera de rango" << endl;
        return;
    }
    elementos[indice] = elemento;
}

// Obtener cantidad
template <typename T>
int ArregloDinamico<T>::getCantidad() const {
    return cantidad;
}

// Obtener capacidad
template <typename T>
int ArregloDinamico<T>::getCapacidad() const {
    return capacidad;
}

// Verificar si está vacío
template <typename T>
bool ArregloDinamico<T>::estaVacio() const {
    return cantidad == 0;
}

// Limpiar todos los elementos
template <typename T>
void ArregloDinamico<T>::limpiar() {
    cantidad = 0;
}

// Verificar si existe un índice
template <typename T>
bool ArregloDinamico<T>::existe(int indice) const {
    return (indice >= 0 && indice < cantidad);
}

// Redimensionar (método privado)
template <typename T>
void ArregloDinamico<T>::redimensionar() {
    // Nueva capacidad con factor 1.5
    int nuevaCapacidad = static_cast<int>(capacidad * FACTOR_CRECIMIENTO);

    // Crear nuevo arreglo
    T* nuevoArreglo = new T[nuevaCapacidad];

    // Copiar elementos existentes
    for (int i = 0; i < cantidad; i++) {
        nuevoArreglo[i] = elementos[i];
    }

    // Liberar memoria antigua
    delete[] elementos;

    // Actualizar puntero y capacidad
    elementos = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

#endif // ARREGLODINAMICO_H
