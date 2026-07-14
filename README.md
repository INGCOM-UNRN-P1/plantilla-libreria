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

## Script de Gestión Local

El proyecto incluye un script de gestión local para administrar la librería de forma autónoma:

* **Renombrar librería**: `./manage.sh rename <nuevo_nombre>` (Renombra la librería y actualiza las referencias y nombres de archivos).
* **Crear nuevo módulo**: `./manage.sh add-module <nombre_modulo>` (Crea un esqueleto de cabecera y código fuente en `include/` y `src/`).
* **Compilar**: `./manage.sh build`
* **Probar**: `./manage.sh test`
* **Limpiar**: `./manage.sh clean`

