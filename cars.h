// cars.h header with cars struct def.

#ifndef CARS_H
#define CARS_H

typedef struct car_struct {
    char model[15];
    char manufacturer[15];
    int year;
    char transmission[10];
    char color[10];
    double mileage;
} car;

#endif