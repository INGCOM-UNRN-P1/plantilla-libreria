#!/bin/bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
    echo "Uso: $0 <ruta_proyecto_destino>"
    exit 1
fi

TARGET_PROJECT="$(cd "$1" && pwd)"
SPEC_FILE="library.spec"

if [ ! -f "$SPEC_FILE" ]; then
    echo "Error: No se encontró el archivo de especificación '$SPEC_FILE'."
    exit 1
fi

# Cargar especificación
# shellcheck source=/dev/null
source "$SPEC_FILE"

echo "Integrando librería '${LIB_NAME}' v${LIB_VERSION} en '${TARGET_PROJECT}'..."

# Compilar librería
echo "Compilando librería ejecutando: ${LIB_BUILD_CMD}"
eval "${LIB_BUILD_CMD}"

# Copiar cabeceras
for item in "${LIB_HEADERS[@]}"; do
    src="${item%%:*}"
    dst="${item##*:}"
    full_dst="${TARGET_PROJECT}/${dst}"
    
    mkdir -p "$(dirname "$full_dst")"
    cp "$src" "$full_dst"
    echo "Copiado: $src -> $full_dst"
done

# Copiar binarios
for item in "${LIB_BINARIES[@]}"; do
    src="${item%%:*}"
    dst="${item##*:}"
    full_dst="${TARGET_PROJECT}/${dst}"
    
    mkdir -p "$(dirname "$full_dst")"
    cp "$src" "$full_dst"
    echo "Copiado: $src -> $full_dst"
done

echo "Integración completada con éxito."
