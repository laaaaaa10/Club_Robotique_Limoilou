#ifndef PILOTEENTREESWF_H
#define PILOTEENTREESWF_H

//MODULE: piloteEntreeSWF
//DESCRIPTION: pour permettre la lecture d'une entree numérique dans l'environnement CrcLib
//ENVIRONNEMENT Arduino et CrcLib
// 2025-11-26, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREESWF_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEENTREESWF_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEENTREESWF_BROCHE CRC_DIG_1

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteEntreeSWF_lit(void);
void piloteEntreeSWF_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
