//
// Created by clovis on 3/6/24.
//

#ifndef ROBOT2024_COCHES_H
#define ROBOT2024_COCHES_H

#include "main.h"

#define AIMANT_PIN CRC_DIG_1

void initElevateur();
extern void (*actionElevateur)();

extern int8_t elevateurSpeed;
extern bool aimantAligne;
extern int8_t elevateurDirectionCommandee;

#endif //ROBOT2024_COCHES_H
