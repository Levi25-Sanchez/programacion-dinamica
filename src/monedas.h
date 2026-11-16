// Problema 2: Cambio mínimo de monedas (Programación Dinámica)
#pragma once
#include <climits>
#include <vector>

constexpr int INF = INT_MAX;                   // "cantidad no alcanzable"
constexpr int CANTIDAD_MAX = 10000000;         // evita tablas gigantes por error

struct ResultadoMonedas {
    bool posible;                  // false si la cantidad no se puede formar
    int minimo;                    // mínimo de monedas (válido si posible)
    std::vector<int> combinacion;  // monedas usadas, de mayor a menor
    std::vector<int> dp;           // tabla completa (INF si no alcanzable)
};

// Calcula el cambio mínimo. Lanza std::invalid_argument si la entrada no es válida.
ResultadoMonedas cambioMinimo(std::vector<int> monedas, int cantidad);
