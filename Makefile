# Nombre del compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c99

# Archivos fuente
SRCS = main.c utils.c metrics.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
EXEC = app1

# Regla principal
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regla para compilar archivos .c a .o
%.o: %.c app1.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
