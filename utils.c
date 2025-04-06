#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app1.h"

#define MAX_LINE 1024

int read_csv(const char *filename, struct order **orders) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir %s\n", filename);
        return -1;
    }

    // Contar líneas (excluyendo cabecera)
    int count = 0;
    char buffer[MAX_LINE];
    fgets(buffer, sizeof(buffer), file); // Saltar cabecera
    while (fgets(buffer, sizeof(buffer), file)) count++;

    // Reservar memoria
    *orders = malloc(count * sizeof(struct order));
    if (!*orders) {
        fclose(file);
        return -1;
    }

    // Volver al inicio
    rewind(file);
    fgets(buffer, sizeof(buffer), file); // Saltar cabecera nuevamente

    // Parsear cada línea
    int index = 0;
    while (fgets(buffer, sizeof(buffer), file) && index < count) {
        char *ptr = buffer;
        struct order *current = &(*orders)[index++];

        // pizza_id
        current->pizza_id = atoi(ptr);
        ptr = strchr(ptr, ',') + 1;

        // order_id
        current->order_id = atoi(ptr);
        ptr = strchr(ptr, ',') + 1;

        // pizza_name_id (ignorado)
        ptr = strchr(ptr, ',') + 1;

        // quantity
        current->quantity = atoi(ptr);
        ptr = strchr(ptr, ',') + 1;

        // order_date (variable tamaño, hasta próxima coma)
        char *end = strchr(ptr, ',');
        size_t date_len = end - ptr;
        strncpy(current->order_date, ptr, date_len);
        current->order_date[date_len] = '\0';
        ptr = end + 1;

        // order_time
        end = strchr(ptr, ',');
        size_t time_len = end - ptr;
        strncpy(current->order_time, ptr, time_len);
        current->order_time[time_len] = '\0';
        ptr = end + 1;

        // unit_price
        current->unit_price = atof(ptr);
        ptr = strchr(ptr, ',') + 1;

        // total_price
        current->total_price = atof(ptr);
        ptr = strchr(ptr, ',') + 1;

        // pizza_size
        current->pizza_size = *ptr;
        ptr = strchr(ptr, ',') + 1;

        // pizza_category
        end = strchr(ptr, ',');
        size_t cat_len = end - ptr;
        strncpy(current->pizza_category, ptr, cat_len);
        current->pizza_category[cat_len] = '\0';
        ptr = end + 1;

        // pizza_ingredients (entre comillas)
        if (*ptr == '"') {
            ptr++;
            end = strchr(ptr, '"');
            size_t ingr_len = end - ptr;
            strncpy(current->pizza_ingredients, ptr, ingr_len);
            current->pizza_ingredients[ingr_len] = '\0';
            ptr = end + 2; // Salta comilla y coma
        } else {
            current->pizza_ingredients[0] = '\0'; // Por si está vacío (no debería)
        }

        // pizza_name
        if (*ptr == '"') ptr++;
        strncpy(current->pizza_name, ptr, strcspn(ptr, "\n\r"));
        current->pizza_name[strcspn(current->pizza_name, "\"\n\r")] = '\0'; // Remover comilla final si hay
    }

    fclose(file);
    return count;
}

void free_orders(struct order *orders) {
    free(orders);
}







