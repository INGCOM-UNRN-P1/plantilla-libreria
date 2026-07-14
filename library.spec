# Especificación de la librería para integración por shell script

LIB_NAME="plantilla"
LIB_VERSION="1.0.0"
LIB_BUILD_CMD="make"
LIB_CLEAN_CMD="make clean"

# Archivos a exportar (formato: "origen:destino")
LIB_HEADERS=(
  "include/plantilla.h:include/plantilla.h"
)
LIB_BINARIES=(
  "build/libplantilla.a:lib/libplantilla.a"
)
