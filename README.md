# Plantilla para Librerías en C

Estructura de proyecto base para desarrollar, probar y ejecutar librerías en C.

## 🧪 `tda/contracts.h` — Invariantes en runtime para TDAs

Cabecera C99 pura (header-only) para validar contratos e invariantes de Tipos
de Datos Abstractos durante las pruebas:

```c
#include <tda/contracts.h>

Lista *lista_insertar(Lista *l, int valor) {
    TDA_REQUIERE(l != NULL);              // precondición
    TDA_INVARIANTE(l, lista_es_valida);   // invariante estructural (antes)
    ...
    TDA_GARANTIZA(l->tam > 0);            // postcondición
    TDA_INVARIANTE(l, lista_es_valida);   // invariante (después)
    return l;
}
```

- Una violación imprime `archivo:línea`, la condición rota y aborta: el test falla con diagnóstico claro.
- Con `-DNDEBUG` los contratos se compilan fuera (cero costo).
- Helpers genéricos: `tda_siguiente(nodo, offset)` y `tda_tiene_ciclo(primero, offset_sig, max_nodos)` para detectar ciclos en listas sin conocer el tipo concreto.
- El encapsulamiento se defiende en compilación: declará el struct completo sólo en el `.c` (tipo opaco en el `.h`).

Pruebas: `make test` (incluye `tests/test_contracts.c`). Se compila estricto:
`-std=c99 -Wall -Wextra -Werror -pedantic`.

---

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

## 🔗 Integración con Plantilla-TP

Esta librería posee un esquema estructurado compatible con proyectos basados en **plantilla-TP**.

Para agregar esta librería a tu TP:
1. Asegurate de que la librería tenga el nombre que querés (renombrala usando `./manage.sh rename <nuevo_nombre>` si es necesario).
2. Subí el código a tu repositorio de Git remoto.
3. En el directorio raíz de tu TP, ejecutá:
   ```bash
   ./tp.sh add-lib <nombre_libreria> <url_git_libreria>
   ```
   *Nota: El gestor del TP detectará la especificación en `library.spec` (o `library.json`), conservará la estructura original (`include/` y `src/`) y compilará la biblioteca estática en `build/` de manera totalmente integrada.*


