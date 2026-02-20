#ifndef PILOTEENTREEANA_H
#define PILOTEENTREEANA_H

//MODULE: piloteEntreeANA
//DESCRIPTION: pour permettre la lecture d'une entree analogue dans l'environnement CrcLib
//ENVIRONNEMENT Arduino et CrcLib

// 2025-11-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREEANA_BROCHE CRC_ANA_1

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned int piloteEntreeANA_lit(void);
void piloteEntreeANA_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
