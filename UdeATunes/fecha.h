#ifndef FECHA_H
#define FECHA_H

class Fecha
{
private:
    int año;
    int mes;
    int dia;

public:
    // Constructor parametrizado
    Fecha(int año, int mes, int dia);

    // Constructor de copia
    Fecha(const Fecha& otra);

    // Destructor
    ~Fecha();

    // Sobrecarga de operadores
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    Fecha& operator=(const Fecha& otra);

    // Getters
    int getAño() const;
    int getMes() const;
    int getDia() const;

    // Setters con validación
    void setAño(int año);
    void setMes(int mes);
    void setDia(int dia);

    // Método auxiliar para validar la fecha
    bool esValida() const;
};

#endif // FECHA_H
