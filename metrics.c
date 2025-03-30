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





