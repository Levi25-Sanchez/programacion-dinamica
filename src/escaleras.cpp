/*
 * Problema 1: Escaleras (Programación Dinámica)
 *
 * Un personaje sube una escalera de N escalones avanzando 1 o 2 escalones
 * por movimiento. Se calcula de cuántas formas distintas puede llegar
 * exactamente al escalón N.
 *
 * Estado DP   : dp[i] = número de formas de llegar exactamente al escalón i.
 * Recurrencia : dp[i] = dp[i-1] + dp[i-2]      (para i >= 2)
 * Casos base  : dp[0] = 1 (una forma de "estar en el suelo": no moverse)
 *               dp[1] = 1 (solo se puede llegar con un paso de 1)
 */
#include "escaleras.h"

#include <stdexcept>

ResultadoEscaleras contarFormas(int n) {
    if (n < 0 || n > N_MAX_ESCALERAS) {
        throw std::invalid_argument(
            "N debe estar entre 0 y " + std::to_string(N_MAX_ESCALERAS) +
            " (con mas escalones el resultado no cabe en 64 bits).");
    }

    // Tabla DP: dp[i] = formas de llegar exactamente al escalón i.
    std::vector<uint64_t> dp(n + 1, 0);

    // Caso base 1: hay exactamente una forma de estar en el escalón 0.
    dp[0] = 1;

    // Caso base 2: al escalón 1 solo se llega con un paso de 1 escalón.
    if (n >= 1) dp[1] = 1;

    // Llenado bottom-up: al escalón i se llega desde i-1 (paso de 1)
    // o desde i-2 (paso de 2); las formas de ambos casos se suman.
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return {dp[n], dp};
}
