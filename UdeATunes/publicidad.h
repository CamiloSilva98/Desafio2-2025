#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>
using namespace std;

class Publicidad {
private:
    int id;
    string mensaje;
    char categoria;  // 'C', 'B', 'A' (AAA se representa como 'A')
    int ultimaVezMostrada;  // Contador para evitar repeticiones consecutivas

public:
    // Constructor por defecto
    Publicidad();

    // Constructor parametrizado
    Publicidad(int id, string mensaje, char categoria);

    // Constructor de copia
    Publicidad(const Publicidad& otra);

    // Destructor
    ~Publicidad();

    // Sobrecarga de operadores
    bool operator==(const Publicidad& otra) const;
    bool operator<(const Publicidad& otra) const;
    Publicidad& operator=(const Publicidad& otra);

    // Método de cálculo de peso (para selección probabilística)
    int calcularPeso() const;

    // Getters
    int getId() const;
    string getMensaje() const;
    char getCategoria() const;
    int getUltimaVezMostrada() const;

    // Setters con validación
    void setId(int id);
    void setMensaje(string mensaje);
    void setCategoria(char categoria);
    void setUltimaVezMostrada(int valor);
};

#endif // PUBLICIDAD_H
