#ifndef CREDITO_H
#define CREDITO_H

#include <string>
using namespace std;

class Credito
{
private:
    string nombre;
    string apellido;
    string codigoAfiliacion;
    string tipo; // productor, músico, compositor, etc.

public:
    // Constructor parametrizado
    Credito(string nombre, string apellido, string codigoAfiliacion, string tipo);

    // Constructor de copia
    Credito(const Credito& otro);

    // Destructor
    ~Credito();

    // Sobrecarga de operadores
    bool operator==(const Credito& otro) const;
    bool operator<(const Credito& otro) const;
    Credito& operator=(const Credito& otro);

    // Getters
    string getNombre() const;
    string getApellido() const;
    string getCodigoAfiliacion() const;
    string getTipo() const;

    // Setters con validación
    void setNombre(string nombre);
    void setApellido(string apellido);
    void setCodigoAfiliacion(string codigoAfiliacion);
    void setTipo(string tipo);
};

#endif // CREDITO_H
