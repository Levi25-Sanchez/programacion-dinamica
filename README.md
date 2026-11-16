# Actividad: Programación Dinámica

Solución en **C++17** de dos problemas de optimización resueltos con
Programación Dinámica (PD, enfoque *bottom-up* con tabla):

| # | Problema | Archivos | Estado DP | Tiempo | Espacio |
|---|----------|----------|-----------|--------|---------|
| 1 | Escaleras (formas de subir N escalones con pasos de 1 o 2) | `src/escaleras.cpp/.h` | `dp[i]` = formas de llegar al escalón `i` | O(N) | O(N) |
| 2 | Cambio mínimo de monedas | `src/monedas.cpp/.h` | `dp[a]` = mínimo de monedas para formar `a` | O(N·M) | O(N) |

> En el problema 2, `N` es la cantidad objetivo y `M` el número de denominaciones.

## Requisitos

- Un compilador con soporte C++17 (g++ 7 o superior, clang++, MSVC) y `make` (opcional).
- No se usan librerías externas.

## Compilar y ejecutar

Con `make` (Linux, macOS, MSYS2/MinGW):

```bash
make                         # genera build/dp
./build/dp                   # menú interactivo
./build/dp escaleras 5
./build/dp monedas 1,3,4 6
```

Sin `make`:

```bash
mkdir -p build
g++ -std=c++17 -O2 -o build/dp src/escaleras.cpp src/monedas.cpp src/main.cpp
```

### Ejemplos de salida

```text
$ ./build/dp escaleras 5
Formas posibles: 8
Tabla DP:
[1, 1, 2, 3, 5, 8]

$ ./build/dp monedas 1,3,4 6
Cantidad minima de monedas: 2
Combinacion: 3 + 3
Tabla DP:
[0, 1, 2, 1, 1, 2, 2]
```

Si una cantidad no se puede formar, el programa lo indica y muestra `INF`
en la tabla para las cantidades inalcanzables:

```text
$ ./build/dp monedas 2 3
No es posible formar la cantidad con las monedas dadas.
Tabla DP:
[0, INF, 1, INF]
```

## Pruebas

```bash
make test
```

Compara la solución DP contra soluciones de fuerza bruta (todas las N de 0 a 25
y 200 casos aleatorios de monedas), los ejemplos del enunciado, casos borde
(`N = 0`, cantidad `0`, cantidad imposible, `N = 92`) y entradas inválidas.

## Estructura

```text
.
├── Makefile
├── README.md
├── src/
│   ├── escaleras.h / escaleras.cpp   # Problema 1
│   ├── monedas.h / monedas.cpp       # Problema 2
│   └── main.cpp                      # Menú interactivo y línea de comandos
├── tests/
│   └── test_dp.cpp                   # Validación con fuerza bruta y casos borde
└── docs/
    ├── Informe_Programacion_Dinamica.pdf
    └── capturas/                     # Evidencias de ejecución
```

## Entradas válidas

- **Escaleras:** `N` entero entre 0 y 92 (con enteros de 64 bits, `dp[92] =
  12200160415121876738` es el mayor resultado que cabe; con más escalones el
  programa muestra un error en lugar de desbordarse).
- **Monedas:** denominaciones enteras > 0 (se ignoran repetidas y el orden no
  importa) y cantidad entera entre 0 y 10 000 000. Con entradas inválidas el
  programa muestra un mensaje de error en lugar de fallar.
