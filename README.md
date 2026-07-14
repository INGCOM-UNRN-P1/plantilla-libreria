# Plantilla para Librerías en C

Estructura de proyecto base para desarrollar, probar y ejecutar librerías en C.

## Estructura del Proyecto

* **`include/`**: Archivos de cabecera (`.h`) públicos de la librería.
* **`src/`**: Implementación de la librería (`.c`).
* **`examples/`**: Programas de ejemplo que utilizan la librería.
* **`tests/`**: Suite de pruebas unitarias.
* **`Makefile`**: Orquestador de la compilación, pruebas y ejecución.

## Requisitos

* GCC (o cualquier compilador compatible con C99)
* GNU Make

## Uso

Compilá todo el proyecto (librería estática, ejemplo y pruebas):
```bash
make
```

Ejecutá las pruebas unitarias:
```bash
make test
```

Ejecutá el programa de ejemplo:
```bash
make run
```

Limpiá los archivos compilados:
```bash
make clean
```
