#ifndef PILOTESORTIET1_H
#define PILOTESORTIET1_H

//MODULE: piloteSortieT1
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull"
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTESORTIET1_BROCHE CRC_DIG_2
//#define PILOTESORTIET1_ETAT_INITIAL_A_UN
//#define PILOTESORTIET1_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteSortieT1_metAUn(void);
void piloteSortieT1_metAZero(void);
void piloteSortieT1_metA(unsigned char Niveau);
void piloteSortieT1_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
