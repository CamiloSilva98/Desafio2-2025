#include "Fecha.h"

Fecha::Fecha()
{
    año = 2000;
    mes = 1;
    dia = 1;
}
// Constructor parametrizado
Fecha::Fecha(int año, int mes, int dia)
{
    this->año = año;
    this->mes = mes;
    this->dia = dia;

    // Validar y ajustar si es necesario
    if (!esValida())
    {
        this->año = 2000;
        this->mes = 1;
        this->dia = 1;
    }
}

// Constructor de copia
Fecha::Fecha(const Fecha& otra)
{
    año = otra.año;
    mes = otra.mes;
    dia = otra.dia;
}

// Destructor
Fecha::~Fecha()
{
    // No hay memoria dinámica que liberar en esta clase
}

// Operador de igualdad
bool Fecha::operator==(const Fecha& otra) const
{
    return (año == otra.año && mes == otra.mes && dia == otra.dia);
}

// Operador menor que (para ordenamiento)
bool Fecha::operator<(const Fecha& otra) const
{
    if (año != otra.año)
        return año < otra.año;
    if (mes != otra.mes)
        return mes < otra.mes;
    return dia < otra.dia;
}

// Operador de asignación
Fecha& Fecha::operator=(const Fecha& otra)
{
    // Protección contra autoasignación
    if (this != &otra)
    {
        año = otra.año;
        mes = otra.mes;
        dia = otra.dia;
    }
    return *this;
}

// Getters
int Fecha::getAño() const
{
    return año;
}

int Fecha::getMes() const
{
    return mes;
}

int Fecha::getDia() const
{
    return dia;
}

// Setters con validación
void Fecha::setAño(int año)
{
    if (año >= 1900 && año <= 2025)
    {
        this->año = año;
    }
}

void Fecha::setMes(int mes)
{
    if (mes >= 1 && mes <= 12)
    {
        this->mes = mes;
    }
}

void Fecha::setDia(int dia)
{
    if (dia >= 1 && dia <= 31)
    {
        // Validación básica, puede mejorarse según el mes
        this->dia = dia;
    }
}

// Método auxiliar para validar la fecha completa
bool Fecha::esValida() const
{
    // Validar año
    if (año < 1900 || año > 2026)
        return false;

    // Validar mes
    if (mes < 1 || mes > 12)
        return false;

    // Días por mes
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Año bisiesto
    if ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0)) {
        diasPorMes[2] = 29;
    }

    // Validar día
    if (dia < 1 || dia > diasPorMes[mes])
        return false;

    return true;
}
