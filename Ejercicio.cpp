#include "Ejercicio.h"
#include <sstream>

Ejercicio::Ejercicio(std::string c, std::string n, TipoEjercicio t, 
                     NivelIntensidad niv, int ti, std::string desc, int sem)
    : codigo(c), nombre(n), tipo(t), nivel(niv), tiempo(ti), descripcion(desc), ultimaSemana(sem) {}

std::string Ejercicio::toString() const {
    std::ostringstream oss;
    std::string niv_str[] = {"Basico", "Intermedio", "Avanzado", "Alto Rend."};
    oss << codigo << ". " << nombre << " (" 
        << (tipo==TipoEjercicio::CARDIO ? "Cardio" : "Fuerza") 
        << " - " << niv_str[static_cast<int>(nivel)] << ")";
    if (tiempo > 0) oss << " [" << tiempo << "min]";
    oss << "\n   " << descripcion;
    return oss.str();
}