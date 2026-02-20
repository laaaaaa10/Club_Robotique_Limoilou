#ifndef PILOTESORTIEDEL_H
#define PILOTESORTIEDEL_H

//MODULE: piloteSortieDEL
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull"
// 2025-11-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTESORTIEDEL_BROCHE CRC_DIG_2
//#define PILOTESORTIEDEL_ETAT_INITIAL_A_UN
//#define PILOTESORTIEDEL_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteSortieDEL_metAUn(void);
void piloteSortieDEL_metAZero(void);
void piloteSortieDEL_metA(unsigned char Niveau);
void piloteSortieDEL_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
