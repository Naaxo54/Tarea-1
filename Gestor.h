#ifndef GESTOR_H
#define GESTOR_H
#include "Ejercicio.h"
#include <vector>
#include <string>

class Gestor {
private:
    std::vector<Ejercicio> ejercicios;
    std::vector<Ejercicio> filtrarPorNivel(NivelIntensidad nivel) {
        std::vector<Ejercicio> res;
        for (const auto& e : ejercicios) if (e.getNivel() == nivel) res.push_back(e);
        return res;
    }
public:
    bool agregar(const Ejercicio& e);
    bool eliminar(const std::string& codigo);
    bool actualizar(const std::string& codigo, const Ejercicio& nuevo);
    Ejercicio* buscar(const std::string& codigo);
    
    std::vector<Ejercicio> buscarNivel(NivelIntensidad nivel) { return filtrarPorNivel(nivel); }
    std::vector<Ejercicio> generarRutina(int cant, NivelIntensidad nivel, int semana);
    void listar() const;
    int tiempoTotal(const std::vector<Ejercicio>& rutina) const;
    size_t size() const { return ejercicios.size(); }
    bool cargarDesdeArchivo(const std::string& archivo);
    bool guardarEnArchivo(const std::string& archivo) const;
};
#endif