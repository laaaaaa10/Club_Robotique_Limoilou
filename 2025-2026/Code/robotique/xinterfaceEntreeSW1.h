#ifndef INTERFACEENTREESW1_H
#define INTERFACEENTREESW1_H

//MODULE: interfaceEntreeSW1
//DESCRIPTION: pour s'interfacer avec un interrupteur SW1 qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESW1_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESW1_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESW1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-11-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESW1_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESW1_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESW1_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESW1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESW1_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESW1_MODULE_EN_FONCTION 0
#define INTERFACEENTREESW1_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESW1_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESW1_INFORMATION_TRAITEE 0
#define INTERFACEENTREESW1_INACTIVE 0
#define INTERFACEENTREESW1_ACTIVE  1
#define INTERFACEENTREESW1_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESW1;

//Fonctions publiques:
void interfaceEntreeSW1_initialise(void);

//Variables publiques:
extern INTERFACEENTREESW1 interfaceEntreeSW1;

#endif
