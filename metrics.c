#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "app1.h"

char* pms(int *size, struct order *orders) {
    int max_ventas = 0;
    char *mas_vendida = NULL;

    // Se recorren todas las órdenes para encontrar la pizza más vendida

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity > max_ventas) {
            max_ventas = orders[i].quantity;
            mas_vendida = orders[i].pizza_name; // Se guarda el nombre de la pizza
        }
    }

    return mas_vendida;
}

char* pls(int *size, struct order *orders) {
    int min_ventas = orders[0].quantity; 
    char *menos_vendida = orders[0].pizza_name;

    // Igual que la anterior, se recorren las órdenes para encontrar la pizza menos vendida
    for (int i = 1; i < *size; i++) {
        if (orders[i].quantity < min_ventas) {
            min_ventas = orders[i].quantity;
            menos_vendida = orders[i].pizza_name;
        }
    }

    return menos_vendida;
}


// REVISAR DMS Y DLS: no acumula las ventas por fecha


char* dms(int *size, struct order *orders) {
    double valor_maxventas = 0.0;
    char *fecha_maxventas = NULL;

    // Se recorren todas las órdenes y se calcula el total por fecha
    for (int i = 0; i < *size; i++) {
        double valor_actual = orders[i].total_price;

        // Si la fecha aún no existe en la variable, se inicializa
        if (fecha_maxventas == NULL || valor_actual > valor_maxventas) {
            valor_maxventas = valor_actual;
            fecha_maxventas = orders[i].order_date; // Se guarda la fecha con más ventas
        }
    }

    return fecha_maxventas;

}

char* dls(int *size, struct order *orders) {
    double valor_minventas = orders[0].total_price; 
    char *fecha_minventas = orders[0].order_date;

    for (int i = 1; i < *size; i++) {
        double valor_actual = orders[i].total_price;

        // Si se encuentra un valor menor, se actualiza

        if (valor_actual < valor_minventas) {
            valor_minventas = valor_actual;
            fecha_minventas = orders[i].order_date;
        }
    }

    return fecha_minventas;
}

char* apo(int *size, struct order *orders) {
    int total_pizzas = 0;

    // Se suman todas las cantidades de pizzas
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
    }

    // Calcular el promedio
    double promedio_pizzas = (double) total_pizzas / *size;

    // Convertir a string
    static char result[50];
    snprintf(result, sizeof(result), "%.2f", promedio_pizzas);

    return result;
}

char* apd(int *size, struct order *orders) {
    int total_pizzas = 0;
    int dias_unicos = 0;
    char *ultimo_dia = NULL;

    // Se recorren las órdenes y se suman las pizzas por día
    
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        // Se cuentan los días únicos

        if (ultimo_dia == NULL || strcmp(ultimo_dia, orders[i].order_date) != 0) {
            dias_unicos++;
            ultimo_dia = orders[i].order_date;
        }
    }

    // Calcular promedio

    double promedio_diario = (double) total_pizzas / dias_unicos;

    // Convertir a string
    
    static char result[50];
    snprintf(result, sizeof(result), "%.2f", promedio_diario);

    return result;
}

char* ims(int *size, struct order *orders) {
    struct cuenta_ingredientes {
        char ingrediente[100];
        int contador;
    };

    struct cuenta_ingredientes ingredientes[100];
    int cuenta_ingredientes = 0;

    for (int i = 0; i < *size; i++) {
        char lista_ingredientes[200];
        strcpy(lista_ingredientes, orders[i].pizza_ingredients);

        char *token = strtok(lista_ingredientes, ", "); // Separa los ingredientes
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < cuenta_ingredientes; j++) {
                if (strcmp(ingredientes[j].ingrediente, token) == 0) {
                    ingredientes[j].contador += orders[i].quantity;
                    found = 1;
                    break;
                }
            }

            if (!found && cuenta_ingredientes < 100) {
                strcpy(ingredientes[cuenta_ingredientes].ingrediente, token);
                ingredientes[cuenta_ingredientes].contador = orders[i].quantity;
                cuenta_ingredientes++;
            }

            token = strtok(NULL, ", ");

        }
    }

    // Encontrar el ingrediente más vendido

    int max_count = 0;
    char *mas_vendido = malloc(100);
    if (!mas_vendido) return "Error de memoria";

    for (int i = 0; i < cuenta_ingredientes; i++) {
        if (ingredientes[i].contador > max_count) {
            max_count = ingredientes[i].contador;
            strcpy(mas_vendido, ingredientes[i].ingrediente);
        }
    }

    return mas_vendido;
} 

char* hp(int *size, struct order *orders) {
    struct contador_categoria {
        char categoria[50];
        int contador;
    };

    struct contador_categoria categorias[10];
    int contador_categoria = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < contador_categoria; j++) {
            if (strcmp(categorias[j].categoria, orders[i].pizza_category) == 0) {
                categorias[j].contador += orders[i].quantity;
                found = 1;
                break;
            }
        }

        if (!found && contador_categoria < 10) {
            strcpy(categorias[contador_categoria].categoria, orders[i].pizza_category);
            categorias[contador_categoria].contador = orders[i].quantity;
            contador_categoria++;
        }
    }

    // Construir la salida como una cadena

    char *result = malloc(500);
    if (!result) return "Error de memoria";

    result[0] = "\0"; // Inicializar la cadena vacía

    for (int i = 0; i < contador_categoria; i++) {
        char line[100];
        snprintf(line, siezof(line), "%s: %d\n", categorias[i].categoria, categorias[i].contador);
        strcat(result, line);

    }

    return result;
}

