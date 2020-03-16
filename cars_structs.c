// Implementation for cars.h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cars.h"

int main(void) {
    FILE *cars_out;
    size_t bytes_out;
    car cars_list[5];
    char models[5][15] = {"Huracan", "VAZ-2107", "DS", "Wagoneer", "Canyonero"};
    char makes[5][15] = {"Lamborghini", "Lada", "Citroen", "Jeep", "Groening Motors"};
    int years[5] = {2019, 1989, 1972, 1977, 1987};
    char transmissions[5][10] = {"Manual", "Manual", "Automatic", "Manual", "Automatic"};
    char colors[5][10] = {"Azure", "Red", "Brown", "Hunter", "Muave"};
    double mileages[5] = {30, 355200, 16500, 200000, 35000};


    cars_out = fopen("cars.dat", "w");
    for (int iloopvar = 0; iloopvar < 5; iloopvar++) {
        strcpy(cars_list[iloopvar].model, models[iloopvar]);
        strcpy(cars_list[iloopvar].manufacturer, makes[iloopvar]);
        strcpy(cars_list[iloopvar].transmission, transmissions[iloopvar]);
        strcpy(cars_list[iloopvar].color, colors[iloopvar]);
        cars_list[iloopvar].year = years[iloopvar];
        cars_list[iloopvar].mileage = mileages[iloopvar];

        bytes_out = fwrite(&cars_list[iloopvar], sizeof(car), 1, cars_out);
    }

    fclose(cars_out);

    return 0;
}