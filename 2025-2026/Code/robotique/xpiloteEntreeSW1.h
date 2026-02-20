#ifndef PILOTEENTREESW1_H
#define PILOTEENTREESW1_H

//MODULE: piloteEntreeSW1
//DESCRIPTION: pour permettre la lecture d'une entree numérique dans l'environnement CrcLib
//ENVIRONNEMENT Arduino et CrcLib
// 2025-11-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREESW1_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEENTREESW1_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEENTREESW1_BROCHE CRC_DIG_1

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteEntreeSW1_lit(void);
void piloteEntreeSW1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
