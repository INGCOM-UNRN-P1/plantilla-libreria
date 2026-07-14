#include <stdio.h>
#include "plantilla.h"

int main(void) {
    int a = 5;
    int b = 7;
    int resultado = sumar(a, b);
    printf("Ejemplo de uso de la librería:\n");
    printf("%d + %d = %d\n", a, b, resultado);
    return 0;
}
