#ifndef SERVICEMANETTE_H
#define SERVICEMANETTE_H

//MODULE: serviceManette
//DESCRIPTION: Le service sert a synchronisee la lecture des valeurs produites par la
//manette CRCConnect avec les operations de CrcLib qui se font dans la boucle loop avec
//les operations qui se font en synchronisation avec la base de temps.
//Les valeurs ne peuvent pas etre utilisees lorsque le module n'est pas en fonction
//La synchonisation des lectures des valeurs produite par CrcConnect se fait
//par semaphore. Les valeurs peuvent etre lues quand le module est en fonction.
//Les valeurs produites prennent la valeur SERVICEMANETTE_PAS_EN_FONCTION quand
//etatDuModule indique que le module n'est pas en fonction.

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEMANETTE_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICEMANETTE_MODULE_EN_FONCTION       0
#define SERVICEMANETTE_MODULE_PAS_EN_FONCTION   1
#define SERVICEMANETTE_VALEUR_ACTIVE            1   
#define SERVICEMANETTE_VALEUR_INACTIVE          0
#define SERVICEMANETTE_VALEUR_INVALIDE          2
#define SERVICEMANETTE_NOMBRE_DE_VALEURS        21
#define SERVICEMANETTE_BOUTON_BACK              0
#define SERVICEMANETTE_BOUTON_START             1
#define SERVICEMANETTE_BOUTON_GAUCHE            2
#define SERVICEMANETTE_BOUTON_DROIT             3
#define SERVICEMANETTE_BOUTON_JOYSTICK_GAUCHE   4
#define SERVICEMANETTE_BOUTON_JOYSTICK_DROIT    5
#define SERVICEMANETTE_BOUTON_LOGO              6
#define SERVICEMANETTE_FLECHE_DROITE            7
#define SERVICEMANETTE_FLECHE_HAUTE             8
#define SERVICEMANETTE_FLECHE_GAUCHE            9
#define SERVICEMANETTE_FLECHE_BASSE             10
#define SERVICEMANETTE_BOUTON_B                 11
#define SERVICEMANETTE_BOUTON_Y                 12
#define SERVICEMANETTE_BOUTON_X                 13
#define SERVICEMANETTE_BOUTON_A                 14
#define SERVICEMANETTE_JOYSTICK_GAUCHE_X        15
#define SERVICEMANETTE_JOYSTICK_GAUCHE_Y        16
#define SERVICEMANETTE_JOYSTICK_DROIT_X         17
#define SERVICEMANETTE_JOYSTICK_DROIT_Y         18
#define SERVICEMANETTE_GACHETTE_GAUCHE          19
#define SERVICEMANETTE_GACHETTE_DROITE          20

typedef struct
{
  char valeurLue[SERVICEMANETTE_NOMBRE_DE_VALEURS];
  unsigned char etatDuModule;    
  
} SERVICEMANETTE;

//Fonctions publiques:
void serviceManette_initialise(void);

//Variables publiques:
extern SERVICEMANETTE serviceManette;

#endif
