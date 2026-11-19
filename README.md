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

<!-- corbel:readme:inicio — generado por `corbel readme`: no editar a mano -->

**Versión:** 1.1.0

## Uso

```bash
make         # compila la librería, el ejemplo y las pruebas
make test    # corre las pruebas
make run     # corre el programa de ejemplo
make readme  # actualiza este README desde el código
make clean   # borra lo compilado
```

## Cómo agregarla a un TP

Desde la raíz de un TP hecho con `plantilla-TP`:

```bash
./tp.sh add-lib matematica https://github.com/usuario/matematica-libreria.git
```

## API

### `include/matematica.h`

Operaciones aritméticas de ejemplo de la plantilla.

| Nombre | Qué hace |
| :-- | :-- |
| [`sumar`](#sumar) | Suma dos enteros. |

#### `sumar`

```c
int sumar(int a, int b);
```

Suma dos enteros.

| Parámetro | Descripción |
| :-- | :-- |
| `a` | Primer entero. |
| `b` | Segundo entero. |

**Devuelve:** La suma de a y b.

### `include/tda/contracts.h`

Contratos de precondición, postcondición e invariante para TDAs, en runtime (C99).

| Nombre | Qué hace |
| :-- | :-- |
| [`tda_siguiente`](#tda_siguiente) | Devuelve el nodo siguiente siguiendo el puntero ubicado en `offset_sig`. |
| [`tda_tiene_ciclo`](#tda_tiene_ciclo) | Recorre acotadamente la cadena empezando en `primero` y reporta si existe un ciclo (un nodo revisitado). |
| `TDA_REQUIERE` | Precondición: si `cond` es falsa, informa archivo y línea y aborta. |
| `TDA_GARANTIZA` | Postcondición: si `cond` es falsa, informa archivo y línea y aborta. |
| `TDA_INVARIANTE` | Invariante: si `validador(estructura)` da 0, informa archivo y línea y aborta. |

#### `tda_siguiente`

```c
static inline void *tda_siguiente(const void *nodo, size_t offset_sig);
```

Devuelve el nodo siguiente siguiendo el puntero ubicado en `offset_sig`.

| Parámetro | Descripción |
| :-- | :-- |
| `nodo` | Nodo actual (puede ser NULL). |
| `offset_sig` | Desplazamiento del campo `siguiente` dentro del nodo (`offsetof`). |

**Devuelve:** El nodo siguiente, o NULL si `nodo` es NULL.

#### `tda_tiene_ciclo`

```c
static inline int tda_tiene_ciclo(const void *primero, size_t offset_sig, size_t max_nodos);
```

Recorre acotadamente la cadena empezando en `primero` y reporta si existe un ciclo (un nodo revisitado).

| Parámetro | Descripción |
| :-- | :-- |
| `primero` | Primer nodo de la cadena (puede ser NULL). |
| `offset_sig` | Desplazamiento del campo `siguiente` dentro del nodo (`offsetof`). |
| `max_nodos` | Cota de nodos a recorrer, para no colgar la batería de pruebas ante corrupción grave. |

**Devuelve:** 0 si no hay ciclo, 1 si se detectó uno.

<!-- corbel:readme:fin -->

## Script de Gestión Local

El proyecto incluye un script de gestión local para administrar la librería de forma autónoma:

* **Renombrar librería**: `./manage.sh rename <nuevo_nombre>` (Renombra la librería y actualiza las referencias y nombres de archivos).
* **Crear nuevo módulo**: `./manage.sh add-module <nombre_modulo>` (Crea un esqueleto de cabecera y código fuente en `include/` y `src/`).
* **Compilar**: `./manage.sh build`
* **Probar**: `./manage.sh test`
* **Limpiar**: `./manage.sh clean`
* **Actualizar el README**: `./manage.sh readme` (o `make readme`): regenera, con `corbel`, la parte de este archivo entre las marcas `corbel:readme` (uso, cómo agregarla a un TP y la API de `include/`) desde los docblocks. Lo demás se escribe a mano.

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


