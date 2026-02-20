#ifndef PROCESSUSTEMOIN_H
#define PROCESSUSTEMOIN_H

//MODULE: processusTemoin
//DESCRIPTION: implemente la gestion du DEL T1 qui s'allume lorsque le bouton TEMOIN de la manette CrcConnect est appuye

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSTEMOIN_BOUTON_TEMOIN SERVICEMANETTE_BOUTON_B

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSTEMOIN_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSTEMOIN_MODULE_EN_FONCTION 0
#define PROCESSUSTEMOIN_MODULE_PAS_EN_FONCTION 1

typedef struct
{
  unsigned char etatDuModule;  
} PROCESSUSTEMOIN;


//Fonctions publiques:
void processusTemoin_initialise(void);

//Variables publiques:
extern PROCESSUSTEMOIN processusTemoin;

#endif
