#include "Gestor.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Gestor::agregar(const Ejercicio& e) {
    for (const auto& ex : ejercicios) if (ex == e.getCodigo()) return false;
    ejercicios.push_back(e);
    return true;
}

bool Gestor::eliminar(const std::string& codigo) {
    for (auto it = ejercicios.begin(); it != ejercicios.end(); ++it) {
        if (it->getCodigo() == codigo) {
            ejercicios.erase(it);
            return true;
        }
    }
    return false;
}

Ejercicio* Gestor::buscar(const std::string& codigo) {
    for (auto& e : ejercicios) if (e.getCodigo() == codigo) return &e;
    return nullptr;
}

std::vector<Ejercicio> Gestor::generarRutina(int cant, NivelIntensidad nivel, int semana) {
    auto candidatos = filtrarPorNivel(nivel);
    std::vector<Ejercicio> rutina;
    for (const auto& e : candidatos) {
        if (e.disponible(semana) && rutina.size() < static_cast<size_t>(cant)) {
            rutina.push_back(e);
        }
    }
    return rutina;
}

void Gestor::listar() const {
    if (ejercicios.empty()) { std::cout << "No hay ejercicios\n"; return; }
    for (size_t i = 0; i < ejercicios.size(); ++i)
        std::cout << i+1 << ". " << ejercicios[i].toString() << "\n\n";
}

int Gestor::tiempoTotal(const std::vector<Ejercicio>& rutina) const {
    int total = 0;
    for (const auto& e : rutina) total += e.getTiempo();
    return total;
}

bool Gestor::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "No se pudo abrir " << archivo << "\n";
        return false;
    }
    
    std::string linea;
    int lineNum = 0;
    while (std::getline(file, linea)) {
        lineNum++;
        std::istringstream iss(linea);
        std::string codigo, nombre, tipoStr, nivelStr, tiempoStr, desc;
        
        std::getline(iss, codigo, '|');
        std::getline(iss, nombre, '|');
        std::getline(iss, tipoStr, '|');
        std::getline(iss, nivelStr, '|');
        std::getline(iss, tiempoStr, '|');
        std::getline(iss, desc);
        
        // Convertir strings a tipos
        TipoEjercicio tipo = (tipoStr == "FUERZA") ? TipoEjercicio::FUERZA : TipoEjercicio::CARDIO;
        int nivelInt = std::stoi(nivelStr);
        int tiempo = std::stoi(tiempoStr);
        
        Ejercicio e(codigo, nombre, tipo, static_cast<NivelIntensidad>(nivelInt-1), tiempo, desc);
        if (!agregar(e)) {
            std::cout << "Linea " << lineNum << " duplicada: " << codigo << "\n";
        }
    }
    file.close();
    std::cout << "Cargados " << ejercicios.size() << " ejercicios desde " << archivo << "\n";
    return true;
}

bool Gestor::actualizar(const std::string& codigo, const Ejercicio& nuevo) {
    for (auto& e : ejercicios) {
        if (e.getCodigo() == codigo) {
            // Actualizar solo los campos necesarios
            e.setNombre(nuevo.getNombre());
            e.setTipo(nuevo.getTipo());
            e.setNivel(nuevo.getNivel());
            e.setTiempo(nuevo.getTiempo());
            e.setDescripcion(nuevo.getDescripcion());
            return true;
        }
    }
    return false;
}

bool Gestor::guardarEnArchivo(const std::string& archivo) const {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cout << "No se pudo crear " << archivo << "\n";
        return false;
    }
    
    for (const auto& e : ejercicios) {
        file << e.getCodigo() << "|" 
             << e.getNombre() << "|" 
             << (e.getTipo() == TipoEjercicio::FUERZA ? "FUERZA" : "CARDIO") << "|"
             << (static_cast<int>(e.getNivel()) + 1) << "|"
             << e.getTiempo() << "|"
             << e.getDescripcion() << "\n";
    }
    file.close();
    std::cout << "Guardados " << ejercicios.size() << " ejercicios en " << archivo << "\n";
    return true;
}