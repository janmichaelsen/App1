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

