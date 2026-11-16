/*
 * Pruebas de validación: se compara la solución DP contra soluciones de
 * fuerza bruta independientes y contra los ejemplos del enunciado.
 */
#include <iostream>
#include <random>
#include <set>
#include <stdexcept>
#include <vector>

#include "../src/escaleras.h"
#include "../src/monedas.h"

static int total = 0, fallos = 0;
#define CHECK(cond)                                                          \
    do {                                                                     \
        total++;                                                             \
        if (!(cond)) { fallos++; std::cout << "FALLO linea " << __LINE__ << ": " #cond "\n"; } \
    } while (0)

template <typename F>
bool lanza(F f) {
    try { f(); } catch (const std::invalid_argument&) { return true; }
    return false;
}

// Cuenta secuencias de pasos 1/2 que suman n (recursión pura).
uint64_t formasFuerzaBruta(int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    return formasFuerzaBruta(n - 1) + formasFuerzaBruta(n - 2);
}

// Mínimo de monedas por recursión exhaustiva (solo para cantidades pequeñas).
int minimoFuerzaBruta(const std::vector<int>& m, int resto) {
    if (resto == 0) return 0;
    int mejor = INF;
    for (int c : m) {
        if (c <= resto) {
            int sub = minimoFuerzaBruta(m, resto - c);
            if (sub != INF && sub + 1 < mejor) mejor = sub + 1;
        }
    }
    return mejor;
}

int main() {
    // ---- Escaleras ----
    CHECK(contarFormas(5).formas == 8);
    CHECK((contarFormas(5).dp == std::vector<uint64_t>{1, 1, 2, 3, 5, 8}));
    CHECK((contarFormas(7).dp == std::vector<uint64_t>{1, 1, 2, 3, 5, 8, 13, 21}));
    CHECK(contarFormas(4).formas == 5);
    CHECK((contarFormas(0).dp == std::vector<uint64_t>{1}));
    CHECK((contarFormas(1).dp == std::vector<uint64_t>{1, 1}));
    CHECK(contarFormas(2).formas == 2);
    for (int n = 0; n <= 25; n++) CHECK(contarFormas(n).formas == formasFuerzaBruta(n));
    CHECK(contarFormas(92).formas == 12200160415121876738ULL);  // máximo que cabe en 64 bits
    CHECK(lanza([] { contarFormas(-1); }));
    CHECK(lanza([] { contarFormas(93); }));

    // ---- Monedas: ejemplos del enunciado ----
    ResultadoMonedas r = cambioMinimo({1, 3, 4}, 6);
    CHECK(r.posible && r.minimo == 2);
    CHECK((r.combinacion == std::vector<int>{3, 3}));
    CHECK((r.dp == std::vector<int>{0, 1, 2, 1, 1, 2, 2}));

    r = cambioMinimo({1, 2, 5}, 11);
    CHECK(r.posible && r.minimo == 3);
    CHECK((r.combinacion == std::vector<int>{5, 5, 1}));
    CHECK((r.dp == std::vector<int>{0, 1, 1, 2, 2, 1, 2, 2, 3, 3, 2, 3}));

    // ---- Monedas: casos borde ----
    r = cambioMinimo({2, 5}, 0);
    CHECK(r.posible && r.minimo == 0 && r.combinacion.empty() && r.dp.size() == 1);
    r = cambioMinimo({2}, 3);
    CHECK(!r.posible && r.dp[3] == INF);
    CHECK(!cambioMinimo({5, 10}, 3).posible);
    CHECK(cambioMinimo({5, 1, 5, 2, 1}, 11).minimo == 3);  // repetidas y desordenadas
    CHECK((cambioMinimo({7}, 21).combinacion == std::vector<int>{7, 7, 7}));
    CHECK(cambioMinimo({1, 3, 4}, 6).minimo == 2);          // un voraz daría 3

    // ---- Monedas: contra fuerza bruta (200 casos aleatorios) ----
    std::mt19937 azar(2024);
    for (int caso = 0; caso < 200; caso++) {
        std::set<int> conj;
        int k = 1 + azar() % 4;
        while ((int)conj.size() < k) conj.insert(1 + azar() % 9);
        std::vector<int> monedas(conj.begin(), conj.end());
        int cantidad = azar() % 15;

        ResultadoMonedas res = cambioMinimo(monedas, cantidad);
        int esperado = minimoFuerzaBruta(monedas, cantidad);
        CHECK(res.posible == (esperado != INF));
        if (res.posible) {
            int suma = 0;
            for (int c : res.combinacion) suma += c;
            CHECK(res.minimo == esperado);
            CHECK(suma == cantidad);                       // la combinación suma lo pedido
            CHECK((int)res.combinacion.size() == res.minimo);  // y usa el mínimo de monedas
        }
    }

    // ---- Entradas inválidas ----
    CHECK(lanza([] { cambioMinimo({}, 5); }));
    CHECK(lanza([] { cambioMinimo({0, 1}, 5); }));
    CHECK(lanza([] { cambioMinimo({-1}, 5); }));
    CHECK(lanza([] { cambioMinimo({1}, -1); }));

    std::cout << "Verificaciones: " << total << ", fallidas: " << fallos << "\n";
    std::cout << (fallos == 0 ? "OK: todas las pruebas pasan\n" : "HAY FALLOS\n");
    return fallos == 0 ? 0 : 1;
}
