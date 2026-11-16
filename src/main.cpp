/*
 * Programa principal: ejecuta los dos problemas de Programación Dinámica.
 *
 * Uso interactivo (menú):      ./build/dp
 * Uso por línea de comandos:   ./build/dp escaleras 5
 *                              ./build/dp monedas 1,3,4 6
 */
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "escaleras.h"
#include "monedas.h"

// Imprime una tabla DP como "[a, b, c]"; INF se muestra como "INF".
template <typename T>
void imprimirTabla(const std::vector<T>& dp, bool usaInf) {
    std::cout << "[";
    for (size_t i = 0; i < dp.size(); i++) {
        if (i > 0) std::cout << ", ";
        if (usaInf && dp[i] == static_cast<T>(INF)) std::cout << "INF";
        else std::cout << dp[i];
    }
    std::cout << "]\n";
}

// Convierte texto a entero validando que no haya basura ni desbordamiento.
int parsearEntero(const std::string& texto, const std::string& nombre) {
    char* fin = nullptr;
    errno = 0;
    long long v = std::strtoll(texto.c_str(), &fin, 10);
    if (texto.empty() || *fin != '\0' || errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        throw std::invalid_argument(nombre + " debe ser un numero entero.");
    }
    return static_cast<int>(v);
}

// Convierte "1,3,4" o "1 3 4" en {1, 3, 4}.
std::vector<int> parsearMonedas(std::string texto) {
    for (char& ch : texto) if (ch == ',') ch = ' ';
    std::istringstream ss(texto);
    std::vector<int> monedas;
    std::string tok;
    while (ss >> tok) monedas.push_back(parsearEntero(tok, "Cada moneda"));
    return monedas;
}

void ejecutarEscaleras(int n) {
    ResultadoEscaleras r = contarFormas(n);
    std::cout << "Formas posibles: " << r.formas << "\n";
    std::cout << "Tabla DP:\n";
    imprimirTabla(r.dp, false);
}

void ejecutarMonedas(const std::vector<int>& monedas, int cantidad) {
    ResultadoMonedas r = cambioMinimo(monedas, cantidad);
    if (!r.posible) {
        std::cout << "No es posible formar la cantidad con las monedas dadas.\n";
    } else {
        std::cout << "Cantidad minima de monedas: " << r.minimo << "\n";
        std::cout << "Combinacion: ";
        if (r.combinacion.empty()) std::cout << "(ninguna)";
        for (size_t i = 0; i < r.combinacion.size(); i++) {
            if (i > 0) std::cout << " + ";
            std::cout << r.combinacion[i];
        }
        std::cout << "\n";
    }
    std::cout << "Tabla DP:\n";
    imprimirTabla(r.dp, true);
}

void menu() {
    std::string opcion, a, b;
    while (true) {
        std::cout << "\n=== Programacion Dinamica ===\n1. Escaleras\n"
                     "2. Cambio minimo de monedas\n0. Salir\nElige una opcion: ";
        if (!std::getline(std::cin, opcion)) return;
        try {
            if (opcion == "1") {
                std::cout << "Numero de escalones N: ";
                std::getline(std::cin, a);
                ejecutarEscaleras(parsearEntero(a, "N"));
            } else if (opcion == "2") {
                std::cout << "Monedas (ej. 1,3,4): ";
                std::getline(std::cin, a);
                std::cout << "Cantidad objetivo: ";
                std::getline(std::cin, b);
                ejecutarMonedas(parsearMonedas(a), parsearEntero(b, "La cantidad"));
            } else if (opcion == "0") {
                return;
            } else {
                std::cout << "Opcion no valida.\n";
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) { menu(); return 0; }
    try {
        std::string modo = argv[1];
        if (modo == "escaleras" && argc == 3) {
            ejecutarEscaleras(parsearEntero(argv[2], "N"));
        } else if (modo == "monedas" && argc == 4) {
            ejecutarMonedas(parsearMonedas(argv[2]), parsearEntero(argv[3], "La cantidad"));
        } else {
            std::cout << "Uso:\n  dp                      (menu interactivo)\n"
                         "  dp escaleras N\n  dp monedas 1,3,4 CANTIDAD\n";
            return 1;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
