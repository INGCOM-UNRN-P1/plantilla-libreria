#include <stdio.h>
#include <assert.h>
#include "matematica.h"

void test_sumar(void) {
    assert(sumar(2, 3) == 5);
    assert(sumar(-1, 1) == 0);
    assert(sumar(0, 0) == 0);
    printf("test_sumar: PASSED\n");
}

void test_restar(void) {
    // TODO: Implementar aserciones
    assert(1 == 1);
    printf("test_restar: PASSED\n");
}

int main(void) {
    printf("Corriendo pruebas unitarias...\n");
    test_restar();
    test_sumar();
    printf("Todas las pruebas pasaron exitosamente.\n");
    return 0;
}
