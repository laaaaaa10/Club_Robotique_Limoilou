#ifndef INTERFACEENTREESWF_H
#define INTERFACEENTREESWF_H

//MODULE: interfaceEntreeSWF
//DESCRIPTION: pour s'interfacer avec un interrupteur SWF qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESWF_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESWF_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESWF_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-11-26, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWF_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESWF_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESWF_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESWF_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWF_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESWF_MODULE_EN_FONCTION 0
#define INTERFACEENTREESWF_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESWF_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESWF_INFORMATION_TRAITEE 0
#define INTERFACEENTREESWF_INACTIVE 0
#define INTERFACEENTREESWF_ACTIVE  1
#define INTERFACEENTREESWF_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESWF;

//Fonctions publiques:
void interfaceEntreeSWF_initialise(void);

//Variables publiques:
extern INTERFACEENTREESWF interfaceEntreeSWF;

#endif
