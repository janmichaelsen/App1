#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app1.h"  // Todas las declaraciones ya están aquí

typedef char* (*metric_func)(int*, struct order*);

struct {
    const char *name;
    metric_func func;
} metrics[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"dmsp", dmsp},
    {"dlsp", dlsp},
    {"apo", apo},
    {"apd", apd},
    {"ims", ims},
    {"hp", hp},
    {NULL, NULL}  // Marcador de fin
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo.csv> <metrica1> [metrica2...]\n", argv[0]);
        return 1;
    }

    struct order *orders = NULL;
    int order_count = read_csv(argv[1], &orders);
    if (order_count <= 0) {
        fprintf(stderr, "Error: No se pudieron leer órdenes del archivo\n");
        return 1;
    }

    // Procesar cada métrica solicitada
    for (int i = 2; i < argc; i++) {
        int found = 0;
        for (int j = 0; metrics[j].name != NULL; j++) {
            if (strcmp(argv[i], metrics[j].name) == 0) {
                char *result = metrics[j].func(&order_count, orders);
                if (result) {
                    // Salida especial para hp
                    if (strcmp(metrics[j].name, "hp") == 0) {
                        printf("Cantidad de pizzas por categoría:\n%s", result);
                    } else {
                        printf("%s: %s\n", metrics[j].name, result);
                    }

                    found = 1;
                    free(result);  // Ahora todas las funciones retornan malloc
                }
                break;
            }
        }

        if (!found) {
            fprintf(stderr, "Advertencia: Métrica '%s' no reconocida\n", argv[i]);
        }
    }

    free_orders(orders);
    return 0;
}
