# Especificación de la librería para integración por shell script

LIB_NAME="matematica"
LIB_VERSION="1.0.0"
LIB_BUILD_CMD="make"
LIB_CLEAN_CMD="make clean"

# Archivos a exportar (formato: "origen:destino")
LIB_HEADERS=(
  "include/matematica.h:include/matematica.h"
  "include/tda/contracts.h:include/tda/contracts.h"
)
LIB_BINARIES=(
  "build/libmatematica.a:lib/libmatematica.a"
)
