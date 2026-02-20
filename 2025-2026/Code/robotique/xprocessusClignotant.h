#ifndef PROCESSUSCLIGNOTANT_H
#define PROCESSUSCLIGNOTANT_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'une DEL qui clignote lorsque l'interrupteur SW1 est active.

//HISTORIQUE:
// 2025-11-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS  500
//#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS  500
//#define PROCESSUSCLIGNOTANT_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSCLIGNOTANT_MODULE_EN_FONCTION 0
#define PROCESSUSCLIGNOTANT_MODULE_PAS_EN_FONCTION 1

typedef struct
{
  unsigned char etatDuModule;  
} PROCESSUSCLIGNOTANT;


//Fonctions publiques:
void processusClignotant_initialise(void);

//Variables publiques:
extern PROCESSUSCLIGNOTANT processusClignotant;

#endif
