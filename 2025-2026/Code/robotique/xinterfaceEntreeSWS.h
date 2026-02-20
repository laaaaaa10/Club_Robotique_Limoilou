#ifndef INTERFACEENTREESWS_H
#define INTERFACEENTREESWS_H

//MODULE: interfaceEntreeSWS
//DESCRIPTION: pour s'interfacer avec un interrupteur SWS qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESWS_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESWS_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESWS_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-12-01, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWS_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESWS_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESWS_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESWS_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWS_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESWS_MODULE_EN_FONCTION 0
#define INTERFACEENTREESWS_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESWS_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESWS_INFORMATION_TRAITEE 0
#define INTERFACEENTREESWS_INACTIVE 0
#define INTERFACEENTREESWS_ACTIVE  1
#define INTERFACEENTREESWS_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESWS;

//Fonctions publiques:
void interfaceEntreeSWS_initialise(void);

//Variables publiques:
extern INTERFACEENTREESWS interfaceEntreeSWS;

#endif
