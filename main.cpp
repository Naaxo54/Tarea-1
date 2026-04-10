#include "Gestor.h"
#include <iostream>
#include <limits>

Gestor gestor;
int semana = 1;

void limpiar() { std::cin.clear(); std::cin.ignore(10000,'\n'); }
std::string input(const std::string& msg="") { 
    std::string s; 
    if (!msg.empty()) std::cout << msg;
    std::getline(std::cin >> std::ws, s); 
    return s; 
}
int num(const std::string& msg) {
    int n; std::cout << msg;
    while (!(std::cin >> n)) { limpiar(); std::cout << "Numero valido: "; }
    limpiar(); return n;
}

NivelIntensidad nivel() {
    std::cout << "[1]Basico [2]Intermedio [3]Avanzado [4]Alto Rend: ";
    return static_cast<NivelIntensidad>(num("") - 1);
}
TipoEjercicio tipo() {
    std::cout << "[1]Cardio [2]Fuerza: ";
    return num("") == 2 ? TipoEjercicio::FUERZA : TipoEjercicio::CARDIO;
}

void menu() {
    std::cout << "\n=====================================\n"
              << "    SISTEMA RUTINAS DE ENTRENAMIENTO\n"
              << "=====================================\n"
              << "1. Crear    2. Eliminar   3. Buscar\n"
              << "4. Por Nivel 5. Rutina   6. Actualizar\n"
              << "7. Listar 8. Cargar  9. Guardar\n"
              << "0. Salir\n"
              << "=====================================\n> ";
}

int main() {
    int op;
    while (true) {
        menu();
        std::cin >> op; limpiar();
        if (op == 0) break;
        
        switch(op) {
            case 1: {
                Ejercicio e(input("Codigo: "), input("Nombre: "), tipo(), nivel(),
                           num("Tiempo(min): "), input("Descripcion: "));
                std::cout << (gestor.agregar(e) ? "Creado correctamente!" : "Codigo duplicado!");
                break;
            }
            case 2: {
                std::cout << (gestor.eliminar(input("Codigo: ")) ? "Eliminado!" : "No encontrado");
                break;
            }
            case 3: {
                if (Ejercicio* e = gestor.buscar(input("Codigo: ")))
                    std::cout << "\n" << e->toString() << "\n";
                else std::cout << "No encontrado\n";
                break;
            }
            case 4: {
                auto lista = gestor.buscarNivel(nivel());
                std::cout << "\n" << lista.size() << " ejercicios encontrados:\n";
                for (const auto& e : lista) std::cout << e.toString() << "\n";
                break;
            }
            case 5: {
                int cant = num("Cantidad ejercicios: ");
                auto rutina = gestor.generarRutina(cant, nivel(), semana);
                if (rutina.empty()) {
                    std::cout << "Sin ejercicios disponibles\n";
                } else {
                    std::cout << "\nRUTINA SEMANA #" << semana++ << "\n"
                              << rutina.size() << " ejercicios | " 
                              << gestor.tiempoTotal(rutina) << "min total\n\n";
                    for (size_t i = 0; i < rutina.size(); ++i)
                        std::cout << i+1 << ". " << rutina[i].toString() << "\n";
                }
                break;
            }
            case 6: {
                std::string codigo = input("Codigo a actualizar: ");
                Ejercicio* original = gestor.buscar(codigo);
                if (original) {
                    std::cout << "Actual: " << original->toString() << "\n";
            
                    Ejercicio actualizado(
                        codigo,                                    // Mismo código
                        input("Nuevo nombre [" + original->getNombre() + "]: "),
                        tipo(),
                        nivel(),
                        num("Nuevo tiempo [" + std::to_string(original->getTiempo()) + "]: "),
                        input("Nueva descripcion: ")
                    );
            
                    if (gestor.actualizar(codigo, actualizado)) {
                        std::cout << "Actualizado correctamente\n";
                    }
                } else {
                    std::cout << "Ejercicio no encontrado\n";
                }
                break;
            }
            case 7: {
                std::cout << "\n" << gestor.size() << " EJERCICIOS TOTALES:\n";
                gestor.listar();
                break;
            }
            case 8: {
                std::string archivo = input("Archivo TXT: ");
                gestor.cargarDesdeArchivo(archivo);
                break;
            }
            case 9: {
                std::string archivo = input("Guardar como: ");
                gestor.guardarEnArchivo(archivo);
                break;
            }
            default: std::cout << "Opcion invalida";
        }
        std::cout << "\n\nPresione Enter para continuar...";
        std::cin.get();
    }
    std::cout << "\nGracias por usar el sistema!\n";
    return 0;
}