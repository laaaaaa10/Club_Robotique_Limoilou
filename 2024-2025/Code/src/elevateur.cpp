//
// Created by clovis on 3/6/24.
//

#include "main.h"
#include "elevateur.h"

void initElevateur();
void initMonteElevateur();
void monteElevateur();
void initDescendElevateur();
void descendElevateur();
void bougePasElevateur();
void (*actionElevateur)() = initElevateur;

int8_t elevateurSpeed = 0;
bool aimantAligne = false;

void initElevateur() {
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    if (!aimantAligne) {
        elevateurSpeed = 50;
    } else {
        elevateurSpeed = 0;
        elevateurDirectionCommandee = 0;
        actionElevateur = bougePasElevateur;
    }
}

void initMonteElevateur() {
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    elevateurSpeed = 50;

    if (!aimantAligne) {
        actionElevateur = monteElevateur;
    }
}

void monteElevateur() {
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    if (aimantAligne) {
        elevateurSpeed = 0;
        elevateurDirectionCommandee = 0;
        actionElevateur = bougePasElevateur;
    } else {
        elevateurSpeed = 50;
    }
}

void initDescendElevateur() {
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    elevateurSpeed = -50;

    if (!aimantAligne) {
        actionElevateur = descendElevateur;
    }
}

void descendElevateur() {
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    if (aimantAligne) {
        elevateurSpeed = 0;
        elevateurDirectionCommandee = 0;
        actionElevateur = bougePasElevateur;
    } else {
        elevateurSpeed = -50;
    }
}

void bougePasElevateur() {
    Serial.write("b\n");
    aimantAligne = !CrcLib::GetDigitalInput(AIMANT_PIN);
    elevateurSpeed = 0;

    if (elevateurDirectionCommandee == 1) {
        actionElevateur = initMonteElevateur;
    } else if (elevateurDirectionCommandee == -1) {
        actionElevateur = initDescendElevateur;
    }
}