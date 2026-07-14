#include <stdio.h>
#include <assert.h>
#include "plantilla.h"

void test_sumar(void) {
    assert(sumar(2, 3) == 5);
    assert(sumar(-1, 1) == 0);
    assert(sumar(0, 0) == 0);
    printf("test_sumar: PASSED\n");
}

int main(void) {
    printf("Corriendo pruebas unitarias...\n");
    test_sumar();
    printf("Todas las pruebas pasaron exitosamente.\n");
    return 0;
}
