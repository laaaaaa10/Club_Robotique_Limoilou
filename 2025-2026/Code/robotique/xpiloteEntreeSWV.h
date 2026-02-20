#ifndef PILOTEENTREESWV_H
#define PILOTEENTREESWV_H

//MODULE: piloteEntreeSWV
//DESCRIPTION: pour permettre la lecture d'une entree numérique dans l'environnement CrcLib
//ENVIRONNEMENT Arduino et CrcLib
// 2025-12-01, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREESWV_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEENTREESWV_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEENTREESWV_BROCHE CRC_DIG_1

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteEntreeSWV_lit(void);
void piloteEntreeSWV_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
