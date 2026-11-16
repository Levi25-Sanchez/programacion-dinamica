// Problema 1: Escaleras (Programación Dinámica)
#pragma once
#include <cstdint>
#include <vector>

// Con unsigned 64 bits, el mayor N cuyo resultado cabe es 92 (dp[92] = 12200160415121876738).
constexpr int N_MAX_ESCALERAS = 92;

struct ResultadoEscaleras {
    uint64_t formas;           // dp[N]
    std::vector<uint64_t> dp;  // tabla completa (índices 0..N)
};

// Calcula de cuántas formas se llega al escalón n con pasos de 1 o 2.
// Lanza std::invalid_argument si n < 0 o n > N_MAX_ESCALERAS.
ResultadoEscaleras contarFormas(int n);
