#ifndef INTERFACEENTREESWV_H
#define INTERFACEENTREESWV_H

//MODULE: interfaceEntreeSWV
//DESCRIPTION: pour s'interfacer avec un interrupteur SWV qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESWV_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESWV_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESWV_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-12-01, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWV_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESWV_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESWV_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESWV_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWV_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESWV_MODULE_EN_FONCTION 0
#define INTERFACEENTREESWV_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESWV_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESWV_INFORMATION_TRAITEE 0
#define INTERFACEENTREESWV_INACTIVE 0
#define INTERFACEENTREESWV_ACTIVE  1
#define INTERFACEENTREESWV_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESWV;

//Fonctions publiques:
void interfaceEntreeSWV_initialise(void);

//Variables publiques:
extern INTERFACEENTREESWV interfaceEntreeSWV;

#endif
