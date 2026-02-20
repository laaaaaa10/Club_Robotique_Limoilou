#ifndef INTERFACEENTREESWO_H
#define INTERFACEENTREESWO_H

//MODULE: interfaceEntreeSWO
//DESCRIPTION: pour s'interfacer avec un interrupteur SWO qui est connectee a l'entree numerique DIO
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREESWO_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREESWO_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREESWO_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2025-11-26, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWO_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREESWO_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREESWO_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREESWO_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREESWO_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEENTREESWO_MODULE_EN_FONCTION 0
#define INTERFACEENTREESWO_MODULE_PAS_EN_FONCTION 1
#define INTERFACEENTREESWO_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREESWO_INFORMATION_TRAITEE 0
#define INTERFACEENTREESWO_INACTIVE 0
#define INTERFACEENTREESWO_ACTIVE  1
#define INTERFACEENTREESWO_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREESWO;

//Fonctions publiques:
void interfaceEntreeSWO_initialise(void);

//Variables publiques:
extern INTERFACEENTREESWO interfaceEntreeSWO;

#endif
