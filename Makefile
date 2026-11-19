# Configuración del compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude
LDFLAGS =

# Directorios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
EXAMPLES_DIR = ejemplos
TESTS_DIR = tests

# Nombres de salidas
LIB_NAME = matematica
LIB_A = $(BUILD_DIR)/lib$(LIB_NAME).a
EXAMPLE_BIN = $(BUILD_DIR)/example_main
# Antes de `all`: make expande los prerrequisitos al leer la regla.
TEST_SRCS = $(wildcard $(TESTS_DIR)/test_*.c)
TEST_BINS = $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRCS))

# Fuentes y Objetos de la librería
LIB_SRCS = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))

# Regla por defecto: compila todo (librería, ejemplos y pruebas)
.PHONY: all
all: $(LIB_A) $(EXAMPLE_BIN) $(TEST_BINS)

# Crear directorio de compilación
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para compilar archivos objeto de la librería
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para empaquetar la librería estática
$(LIB_A): $(LIB_OBJS)
	ar rcs $@ $^

# Regla para compilar el ejemplo enlazando la librería
$(EXAMPLE_BIN): $(EXAMPLES_DIR)/main.c $(LIB_A)
	$(CC) $(CFLAGS) $< -o $@ -L$(BUILD_DIR) -l$(LIB_NAME)

# Pruebas unitarias: un ejecutable por archivo tests/test_*.c
$(BUILD_DIR)/test_%: $(TESTS_DIR)/test_%.c $(LIB_A)
	$(CC) $(CFLAGS) $< -o $@ -L$(BUILD_DIR) -l$(LIB_NAME)

# Ejecutar las pruebas unitarias
.PHONY: test
test: $(TEST_BINS)
	@set -e; for bin in $(TEST_BINS); do \
		echo "Ejecutando $$bin..."; \
		./$$bin; \
	done

# Ejecutar el programa de ejemplo
.PHONY: run
run: $(EXAMPLE_BIN)
	@echo "Ejecutando programa de ejemplo..."
	@./$(EXAMPLE_BIN)

# Limpiar archivos generados
.PHONY: clean
clean:
	@echo "Limpiando directorio de compilación..."
	rm -rf $(BUILD_DIR)
