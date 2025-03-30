#ifndef APP1_H // Include guards - Evita inclusiones múltiples (Mencionar que la IA recomendó esto y nos lo explicó)
#define APP1_H


// Estructura para representar una orden

struct order {
    int pizza_id;
    int order_id;
    char pizza_name[100];
    int quantity;
    char order_date[11];
    char order_time[9];
    double unit_price;
    double total_price;
    char pizza_size;
    char pizza_category[20];
    char pizza_ingredients[200];
    char pizza_name[100];

};

// Declaración de las funciones para obtener las métricas

char* pms(int *size, struct order *orders); // Pizza más vendida
char* pls(int *size, struct order *orders); // Piza menos vendida
char* dms(int *size, struct order *orders); // Fecha con más ventas por dinero
char* dls(int *size, struct order *orders); // Fecha con menos ventas por dinero
char* dmsp(int *size, struct order *orders); // Fecha con más ventas por cantidad de pizzas
char* dlsp(int *size, struct order *orders); // Fecha con menos ventas por cantidad de pizzas
char* apo(int *size, struct order *orders); // Promedio de pizzas por orden
char* apd(int *size, struct order *orders); // Promedio de pizzas por día
char* ims(int *size, struct order *orders); // Ingrediente más vendido
char* hp(int *size, struct order *orders); // Cantidad de pizzas por categoría


// Funciones auxiliares (para leer el archivo csv)

int read_csv(const char *filename, struct order **orders);
void free_orders(struct order *orders);

#endif