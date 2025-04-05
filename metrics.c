#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "app1.h"

#define MAX_ENTRIES 100
#define MAX_STRING 100

char* duplicate_string(const char* str) {
    char* result = malloc(strlen(str) + 1);
    if (result) strcpy(result, str);
    return result;
}

char* pms(int *size, struct order *orders) {
    struct pizza_ventas {
        char nombre[MAX_STRING];
        int cantidad;
    } pizzas[MAX_ENTRIES];

    int num_pizzas = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < num_pizzas; j++) {
            if (strcmp(pizzas[j].nombre, orders[i].pizza_name) == 0) {
                pizzas[j].cantidad += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada && num_pizzas < MAX_ENTRIES) {
            strcpy(pizzas[num_pizzas].nombre, orders[i].pizza_name);
            pizzas[num_pizzas].cantidad = orders[i].quantity;
            num_pizzas++;
        }
    }

    if (num_pizzas == 0) return duplicate_string("No hay datos");

    int max_ventas = pizzas[0].cantidad;
    char *mas_vendida = pizzas[0].nombre;

    for (int i = 1; i < num_pizzas; i++) {
        if (pizzas[i].cantidad > max_ventas) {
            max_ventas = pizzas[i].cantidad;
            mas_vendida = pizzas[i].nombre;
        }
    }

    return duplicate_string(mas_vendida);
}

char* pls(int *size, struct order *orders) {
    struct pizza_ventas {
        char nombre[MAX_STRING];
        int cantidad;
    } pizzas[MAX_ENTRIES];

    int num_pizzas = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < num_pizzas; j++) {
            if (strcmp(pizzas[j].nombre, orders[i].pizza_name) == 0) {
                pizzas[j].cantidad += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada && num_pizzas < MAX_ENTRIES) {
            strcpy(pizzas[num_pizzas].nombre, orders[i].pizza_name);
            pizzas[num_pizzas].cantidad = orders[i].quantity;
            num_pizzas++;
        }
    }

    if (num_pizzas == 0) return duplicate_string("No hay datos");

    int min_ventas = pizzas[0].cantidad;
    char *menos_vendida = pizzas[0].nombre;

    for (int i = 1; i < num_pizzas; i++) {
        if (pizzas[i].cantidad < min_ventas) {
            min_ventas = pizzas[i].cantidad;
            menos_vendida = pizzas[i].nombre;
        }
    }

    return duplicate_string(menos_vendida);
}

char* dms(int *size, struct order *orders) {
    struct venta_fecha {
        char fecha[11];
        double total;
    } ventas[MAX_ENTRIES];

    int num_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < num_fechas; j++) {
            if (strcmp(ventas[j].fecha, orders[i].order_date) == 0) {
                ventas[j].total += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada && num_fechas < MAX_ENTRIES) {
            strcpy(ventas[num_fechas].fecha, orders[i].order_date);
            ventas[num_fechas].total = orders[i].total_price;
            num_fechas++;
        }
    }

    if (num_fechas == 0) return duplicate_string("No hay datos");

    int max_idx = 0;
    for (int i = 1; i < num_fechas; i++) {
        if (ventas[i].total > ventas[max_idx].total) {
            max_idx = i;
        }
    }

    char *result = malloc(60);
    snprintf(result, 60, "%s: %.2f", ventas[max_idx].fecha, ventas[max_idx].total);
    return result;
}

char* dls(int *size, struct order *orders) {
    struct venta_fecha {
        char fecha[11];
        double total;
    } ventas[MAX_ENTRIES];

    int num_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < num_fechas; j++) {
            if (strcmp(ventas[j].fecha, orders[i].order_date) == 0) {
                ventas[j].total += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada && num_fechas < MAX_ENTRIES) {
            strcpy(ventas[num_fechas].fecha, orders[i].order_date);
            ventas[num_fechas].total = orders[i].total_price;
            num_fechas++;
        }
    }

    if (num_fechas == 0) return duplicate_string("No hay datos");

    int min_idx = 0;
    for (int i = 1; i < num_fechas; i++) {
        if (ventas[i].total < ventas[min_idx].total) {
            min_idx = i;
        }
    }

    char *result = malloc(60);
    snprintf(result, 60, "%s: %.2f", ventas[min_idx].fecha, ventas[min_idx].total);
    return result;
}

char* apo(int *size, struct order *orders) {
    int total_pizzas = 0;
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
    }

    double promedio = (double)total_pizzas / *size;
    char *result = malloc(20);
    snprintf(result, 20, "%.2f", promedio);
    return result;
}

char* apd(int *size, struct order *orders) {
    char fechas[MAX_ENTRIES][11];
    int dias_unicos = 0;
    int total_pizzas = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        int nueva = 1;
        for (int j = 0; j < dias_unicos; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                nueva = 0;
                break;
            }
        }
        if (nueva) {
            strcpy(fechas[dias_unicos++], orders[i].order_date);
        }
    }

    double promedio = (double)total_pizzas / dias_unicos;
    char *result = malloc(20);
    snprintf(result, 20, "%.2f", promedio);
    return result;
}

char* ims(int *size, struct order *orders) {
    struct ingrediente {
        char nombre[MAX_STRING];
        int cantidad;
    } ingr[MAX_ENTRIES];

    int count = 0;

    for (int i = 0; i < *size; i++) {
        char temp[300];
        strcpy(temp, orders[i].pizza_ingredients);

        char *token = strtok(temp, ",");
        while (token) {
            while (*token == ' ') token++; // Trim espacio izquierdo
            int encontrado = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(ingr[j].nombre, token) == 0) {
                    ingr[j].cantidad += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado && count < MAX_ENTRIES) {
                strcpy(ingr[count].nombre, token);
                ingr[count].cantidad = orders[i].quantity;
                count++;
            }
            token = strtok(NULL, ",");
        }
    }

    int max_idx = 0;
    for (int i = 1; i < count; i++) {
        if (ingr[i].cantidad > ingr[max_idx].cantidad) {
            max_idx = i;
        }
    }

    return duplicate_string(ingr[max_idx].nombre);
}

char* hp(int *size, struct order *orders) {
    struct cat_ventas {
        char nombre[30];
        int cantidad;
    } cats[10];
    int count = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(cats[j].nombre, orders[i].pizza_category) == 0) {
                cats[j].cantidad += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count < 10) {
            strcpy(cats[count].nombre, orders[i].pizza_category);
            cats[count].cantidad = orders[i].quantity;
            count++;
        }
    }

    char *result = malloc(500);
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        char linea[60];
        snprintf(linea, 60, "%s: %d\n", cats[i].nombre, cats[i].cantidad);
        strcat(result, linea);
    }

    return result;
}

