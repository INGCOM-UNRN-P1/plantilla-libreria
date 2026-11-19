/**
 * @file contracts.h
 * @brief Contratos de precondición, postcondición e invariante para TDAs, en runtime (C99).
 *
 * c-tda-contracts: contratos de precondición/postcondición/invariante con
 * reporte pedagógico, y helpers genéricos para validar estructuras enlazadas
 * (detección de ciclos) sin conocer el layout más allá del offset del campo
 * `siguiente`.
 *
 * Uso típico dentro de una primitiva del TDA:
 *
 *     Lista *lista_insertar(Lista *l, int valor) {
 *         TDA_REQUIERE(l != NULL);
 *         TDA_INVARIANTE(l, lista_es_valida);
 *         ... implementación ...
 *         TDA_GARANTIZA(l->tam > 0);
 *         TDA_INVARIANTE(l, lista_es_valida);
 *         return l;
 *     }
 *
 * Compilación:
 *   - Normal: los contratos se evalúan; una violación imprime archivo:línea y
 *     la condición rota, y aborta (comportamiento deseado en las pruebas).
 *   - Con -DNDEBUG: los contratos se compilan fuera (cero costo de runtime).
 *
 * Encapsulamiento: el struct del TDA debe declararse COMPLETO sólo en el .c.
 * El header público declara `typedef struct lista Lista;` (tipo incompleto):
 * si el código cliente intenta `l->tam`, obtiene un error de compilación
 * "dereference of incomplete type" — el encapsulamiento se defiende en tiempo
 * de compilación, no en runtime.
 */

#ifndef TDA_CONTRACTS_H
#define TDA_CONTRACTS_H

#include <stddef.h>

/* ---------------------------------------------------------------------------
 * Contador pedagógico por unidad de traducción: cuántos contratos corrieron.
 * Útil para que la suite verifique que los contratos SE evaluaron.
 * ------------------------------------------------------------------------- */
extern size_t tda_contratos_evaluados_;
size_t tda_contratos_evaluados_;

/**
 * @def TDA_REQUIERE(cond)
 * @brief Precondición: si `cond` es falsa, informa archivo y línea y aborta.
 * @param cond Condición que tiene que valer al entrar a la primitiva.
 */

/**
 * @def TDA_GARANTIZA(cond)
 * @brief Postcondición: si `cond` es falsa, informa archivo y línea y aborta.
 * @param cond Condición que la primitiva promete al salir.
 */

/**
 * @def TDA_INVARIANTE(estructura, validador)
 * @brief Invariante: si `validador(estructura)` da 0, informa archivo y línea y aborta.
 * @param estructura La estructura del TDA a validar.
 * @param validador Función que devuelve distinto de 0 si la estructura es válida.
 */

#ifdef NDEBUG
/* Versión producción: sin evaluación, sin costo. */
#define TDA_REQUIERE(cond)                 ((void)0)
#define TDA_GARANTIZA(cond)                ((void)0)
#define TDA_INVARIANTE(estructura, validador) ((void)0)
#define tda_contratos_evaluados()          ((size_t)0)

#else /* modo verificación */
#include <stdio.h>
#include <stdlib.h>

#define TDA_REQUIERE(cond)                                                    \
    do {                                                                      \
        if (!(cond)) {                                                        \
            fprintf(stderr,                                                   \
                    "❌ PRECONDICIÓN rota  %s:%d  TDA_REQUIERE(%s)\n",        \
                    __FILE__, __LINE__, #cond);                               \
            abort();                                                          \
        }                                                                     \
    } while (0)

#define TDA_GARANTIZA(cond)                                                   \
    do {                                                                      \
        if (!(cond)) {                                                        \
            fprintf(stderr,                                                   \
                    "❌ POSTCONDICIÓN rota  %s:%d  TDA_GARANTIZA(%s)\n",      \
                    __FILE__, __LINE__, #cond);                               \
            abort();                                                          \
        }                                                                     \
    } while (0)

#define TDA_INVARIANTE(estructura, validador)                                 \
    do {                                                                      \
        if (!(validador)(estructura)) {                                       \
            fprintf(stderr,                                                   \
                    "❌ INVARIANTE roto  %s:%d  %s(estructura)\n",            \
                    __FILE__, __LINE__, #validador);                          \
            abort();                                                          \
        }                                                                     \
        tda_contratos_evaluados_++;                                           \
    } while (0)

#define tda_contratos_evaluados() (tda_contratos_evaluados_)

#endif /* NDEBUG */

/* ---------------------------------------------------------------------------
 * Helpers genéricos para invariantes estructurales sobre nodos enlazados.
 * No requieren conocer el tipo: basta el offset del campo `siguiente`.
 * ------------------------------------------------------------------------- */

/**
 * @brief Devuelve el nodo siguiente siguiendo el puntero ubicado en `offset_sig`.
 * @param nodo Nodo actual (puede ser NULL).
 * @param offset_sig Desplazamiento del campo `siguiente` dentro del nodo (`offsetof`).
 * @return El nodo siguiente, o NULL si `nodo` es NULL.
 */
static inline void *tda_siguiente(const void *nodo, size_t offset_sig)
{
    if (nodo == NULL) {
        return NULL;
    }
    void *sig;
    __builtin_memcpy(&sig, (const char *)nodo + offset_sig, sizeof sig);
    return sig;
}

/**
 * @brief Recorre acotadamente la cadena empezando en `primero` y reporta si existe
 * un ciclo (un nodo revisitado).
 * @param primero Primer nodo de la cadena (puede ser NULL).
 * @param offset_sig Desplazamiento del campo `siguiente` dentro del nodo (`offsetof`).
 * @param max_nodos Cota de nodos a recorrer, para no colgar la batería de pruebas
 * ante corrupción grave.
 * @return 0 si no hay ciclo, 1 si se detectó uno.
 */
static inline int tda_tiene_ciclo(const void *primero, size_t offset_sig,
                                  size_t max_nodos)
{
    const void *vistos[256];
    size_t n_vistos = 0;
    const void *actual = primero;

    while (actual != NULL && n_vistos < max_nodos) {
        for (size_t i = 0; i < n_vistos; i++) {
            if (vistos[i] == actual) {
                return 1; /* nodo revisitado: ciclo */
            }
        }
        if (n_vistos < sizeof vistos / sizeof vistos[0]) {
            vistos[n_vistos++] = actual;
        }
        actual = tda_siguiente(actual, offset_sig);
    }
    return 0;
}

#endif /* TDA_CONTRACTS_H */
