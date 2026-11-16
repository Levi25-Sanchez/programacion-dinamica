/*
 * Problema 2: Cambio mínimo de monedas (Programación Dinámica)
 *
 * Dado un conjunto de denominaciones (existencia ilimitada) y una cantidad
 * objetivo, se calcula el mínimo de monedas para formar exactamente esa
 * cantidad y una combinación que lo logra.
 *
 * Estado DP      : dp[a] = mínimo de monedas necesarias para formar la cantidad a.
 * Recurrencia    : dp[a] = min( dp[a - c] + 1 ) para cada moneda c <= a
 *                  con dp[a - c] alcanzable.
 * Casos base     : dp[0] = 0 (formar 0 no requiere monedas)
 *                  dp[a] = INF al inicio (aún no se conoce forma de lograrlo)
 * Reconstrucción : usada[a] = moneda elegida para lograr dp[a]. Se retrocede
 *                  desde 'cantidad' restando monedas hasta llegar a 0.
 */
#include "monedas.h"

#include <algorithm>
#include <functional>
#include <stdexcept>

ResultadoMonedas cambioMinimo(std::vector<int> monedas, int cantidad) {
    // ---- Validación de la entrada ----
    if (cantidad < 0 || cantidad > CANTIDAD_MAX) {
        throw std::invalid_argument("La cantidad debe estar entre 0 y " +
                                    std::to_string(CANTIDAD_MAX) + ".");
    }
    if (monedas.empty()) {
        throw std::invalid_argument("Debe proporcionar al menos una denominacion.");
    }
    for (int c : monedas) {
        if (c <= 0) throw std::invalid_argument("Las denominaciones deben ser enteros positivos.");
    }

    // Ordenar y quitar repetidas: así el ciclo interno puede cortarse con 'break'.
    std::sort(monedas.begin(), monedas.end());
    monedas.erase(std::unique(monedas.begin(), monedas.end()), monedas.end());

    // Tabla DP e historial de decisiones (para reconstruir la combinación).
    std::vector<int> dp(cantidad + 1, INF);
    std::vector<int> usada(cantidad + 1, 0);

    // Caso base: formar 0 cuesta 0 monedas.
    dp[0] = 0;

    // Llenado bottom-up de la cantidad 1 hasta la cantidad objetivo.
    for (int a = 1; a <= cantidad; a++) {
        for (int c : monedas) {
            if (c > a) break;  // las siguientes monedas (más grandes) tampoco caben
            // Si a - c es alcanzable, usar una moneda c da dp[a - c] + 1 monedas.
            if (dp[a - c] != INF && dp[a - c] + 1 < dp[a]) {
                dp[a] = dp[a - c] + 1;
                usada[a] = c;
            }
        }
    }

    // Si la cantidad objetivo nunca se volvió alcanzable, no hay solución.
    if (dp[cantidad] == INF) return {false, 0, {}, dp};

    // Reconstrucción: desde la cantidad objetivo, restar la moneda elegida.
    std::vector<int> combinacion;
    for (int a = cantidad; a > 0; a -= usada[a]) combinacion.push_back(usada[a]);
    std::sort(combinacion.begin(), combinacion.end(), std::greater<int>());  // mayor a menor

    return {true, dp[cantidad], combinacion, dp};
}
