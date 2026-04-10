#ifndef EJERCICIO_H
#define EJERCICIO_H
#include <string>

enum class TipoEjercicio { CARDIO, FUERZA };
enum class NivelIntensidad { BASICO, INTERMEDIO, AVANZADO, ALTO_RENDIMIENTO };

class Ejercicio {
private:
    std::string codigo, nombre, descripcion;
    TipoEjercicio tipo;
    NivelIntensidad nivel;
    int tiempo, ultimaSemana;

public:
    Ejercicio(std::string c="", std::string n="", TipoEjercicio t=TipoEjercicio::CARDIO, 
              NivelIntensidad niv=NivelIntensidad::BASICO, int ti=0, 
              std::string desc="", int sem=-1);
    
    std::string getCodigo() const { return codigo; }
    std::string getNombre() const { return nombre; }
    std::string getDescripcion() const { return descripcion; }
    TipoEjercicio getTipo() const { return tipo; }
    NivelIntensidad getNivel() const { return nivel; }
    int getTiempo() const { return tiempo; }
    int getUltimaSemana() const { return ultimaSemana; }
    
    std::string toString() const;
    bool disponible(int semana) const { return ultimaSemana != semana; }
    bool operator==(const std::string& c) const { return codigo == c; }
    
    void setNombre(const std::string& n) { nombre = n; }
    void setTipo(TipoEjercicio t) { tipo = t; }
    void setNivel(NivelIntensidad niv) { nivel = niv; }
    void setTiempo(int t) { tiempo = t; }
    void setDescripcion(const std::string& d) { descripcion = d; }
};
#endif