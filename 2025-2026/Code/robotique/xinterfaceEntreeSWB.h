#ifndef INTERFACEENTREESWB_H
#define INTERFACEENTREESWB_H

//MODULE: interfaceEntreeSWB
//DESCRIPTION: pour s'interfacer avec un interrupteur SWB qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESWB_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESWB_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESWB_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-11-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWB_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESWB_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESWB_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESWB_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWB_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESWB_MODULE_EN_FONCTION 0
#define INTERFACEENTREESWB_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESWB_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESWB_INFORMATION_TRAITEE 0
#define INTERFACEENTREESWB_INACTIVE 0
#define INTERFACEENTREESWB_ACTIVE  1
#define INTERFACEENTREESWB_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESWB;

//Fonctions publiques:
void interfaceEntreeSWB_initialise(void);

//Variables publiques:
extern INTERFACEENTREESWB interfaceEntreeSWB;

#endif
