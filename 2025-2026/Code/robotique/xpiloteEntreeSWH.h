#ifndef PILOTEENTREESWH_H
#define PILOTEENTREESWH_H

//MODULE: piloteEntreeSWH
//DESCRIPTION: pour permettre la lecture d'une entree numérique dans l'environnement CrcLib
//ENVIRONNEMENT Arduino et CrcLib
// 2025-11-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREESWH_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEENTREESWH_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEENTREESWH_BROCHE CRC_DIG_1

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteEntreeSWH_lit(void);
void piloteEntreeSWH_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
