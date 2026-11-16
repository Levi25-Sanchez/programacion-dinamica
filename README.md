# Programación Dinámica en C++

Este proyecto resuelve dos problemas clásicos usando **programación dinámica**, una técnica que consiste en no repetir trabajo: se resuelven primero los problemas pequeños, se guardan los resultados en una tabla y con ellos se arma la respuesta del problema grande.

## Los dos problemas

### 1. Escaleras

Una persona sube una escalera de **N escalones** y en cada paso puede subir **1 o 2 escalones**. ¿De cuántas formas distintas puede llegar exactamente al escalón N?

**La idea:** para llegar al escalón 5, la persona venía del escalón 4 (dio un paso de 1) o del escalón 3 (dio un paso de 2). Entonces:

```
formas(5) = formas(4) + formas(3)
```

Si vamos guardando ese resultado para cada escalón, nunca lo calculamos dos veces.

### 2. Cambio mínimo de monedas

Tienes varias denominaciones de monedas (con cantidad ilimitada de cada una) y quieres formar una cantidad exacta usando **la menor cantidad de monedas posible**.

**La idea:** para formar 6 con monedas de 1, 3 y 4, pruebo qué pasa si la última moneda es de 1, de 3 o de 4, y me quedo con la mejor opción, usando lo que ya calculé para cantidades más pequeñas. Además de decir cuántas monedas son, el programa te muestra **cuáles** usó.

> Ejemplo curioso: con monedas 1, 3 y 4, la cantidad 6 se forma con 3 + 3 (2 monedas). Si siempre tomaras la moneda más grande, usarías 4 + 1 + 1 (3 monedas). Por eso hace falta programación dinámica y no basta con elegir lo más grande.

## Cómo ejecutarlo

### Lo que necesitas

Un compilador de C++ (por ejemplo `g++`). Si no quieres instalar nada, puedes usar **GitHub Codespaces** desde este repositorio: botón verde **Code**, pestaña **Codespaces**, **Create codespace on main**. Ya trae `g++` listo.

### Compilar

Con `make`:

```bash
make
```

Sin `make`:

```bash
mkdir -p build
g++ -std=c++17 -O2 -o build/dp src/escaleras.cpp src/monedas.cpp src/main.cpp
```

### Usarlo

Hay dos formas. La primera es el menú, que te va preguntando los datos:

```bash
./build/dp
```

La segunda es escribir todo en una sola línea:

```bash
./build/dp escaleras 5
./build/dp monedas 1,3,4 6
```

En Windows, el programa se llama `dp.exe`.

## Ejemplos

**Escaleras con 5 escalones**

```
$ ./build/dp escaleras 5
Formas posibles: 8
Tabla DP:
[1, 1, 2, 3, 5, 8]
```

La tabla muestra cuántas formas hay de llegar a cada escalón, del 0 al 5.

**Monedas 1, 3 y 4 para formar 6**

```
$ ./build/dp monedas 1,3,4 6
Cantidad minima de monedas: 2
Combinacion: 3 + 3
Tabla DP:
[0, 1, 2, 1, 1, 2, 2]
```

La tabla dice cuántas monedas se necesitan como mínimo para formar 0, 1, 2, 3, 4, 5 y 6.

**Cuando no se puede formar la cantidad**

```
$ ./build/dp monedas 2 3
No es posible formar la cantidad con las monedas dadas.
Tabla DP:
[0, INF, 1, INF]
```

Con monedas de 2 nunca se llega a 3. `INF` significa "imposible de formar".

## Probar que funciona

```bash
make test
```

Las pruebas comparan los resultados del programa con soluciones de fuerza bruta (probar todas las posibilidades) y revisan casos especiales: cero escalones, cantidad cero, cantidades imposibles y datos inválidos. Si todo está bien, el final dice:

```
Verificaciones: 645, fallidas: 0
OK: todas las pruebas pasan
```

## Datos que acepta el programa

- **Escaleras:** un número entero de escalones entre 0 y 92. El límite existe porque, con más escalones, el resultado ya no cabe en un entero de 64 bits. Si te pasas, el programa te avisa en lugar de dar un número incorrecto.
- **Monedas:** denominaciones enteras mayores que 0 (las repetidas se ignoran y el orden no importa) y una cantidad entera entre 0 y 10 000 000.
- Si escribes algo inválido, como una letra o un número negativo, el programa muestra un mensaje de error en vez de fallar.

## Qué tan rápido es

| Problema | Tiempo | Memoria |
|---|---|---|
| Escaleras | O(N) | O(N) |
| Monedas | O(N · M) | O(N) |

En escaleras, N es el número de escalones. En monedas, N es la cantidad a formar y M es cuántas denominaciones hay. El informe en PDF explica por qué sale así.

## Qué hay en cada carpeta

```
.
├── Makefile                      Atajos para compilar y probar
├── README.md                     Este archivo
├── src/
│   ├── escaleras.h / .cpp        Problema 1
│   ├── monedas.h / .cpp          Problema 2
│   └── main.cpp                  Menú y lectura de datos
├── tests/
│   └── test_dp.cpp               Pruebas de validación
└── docs/
    ├── Informe_Programacion_Dinamica.pdf   Explicación completa
    └── capturas/                           Ejemplos de ejecución
```

## Para entender el código más a fondo

El archivo `docs/Informe_Programacion_Dinamica.pdf` explica, para cada problema, el estado de la tabla, la fórmula que la llena, los casos base, un ejemplo paso a paso y el análisis de complejidad. Los archivos de `src/` están comentados línea por línea.
