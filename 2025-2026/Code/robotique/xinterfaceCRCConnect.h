#ifndef INTERFACECRCCONNECT_H
#define INTERFACECRCCONNECT_H

//MODULE: interfaceCRCConnect
//DESCRIPTION: pour s'interfacer avec une manette CRCConnect a l'aide de la librairie CrcLib
//L'etat des entrees de la manette est lu periodiquement dans la boucle Loop et un
//semaphore est utilise pour permettre la synchronisation avec les operations qui sont synchronisees
//avec la base de temps
//Les valeurs contenues dans la structure interfaceCRCConnect ne peuvent etre utilisees quand
//etatDuModule indique que le module n'est pas en fonction. Le module n'est pas en fonction 
//quand une erreur de communication est detectee.
//Les valeurs peuvent etre utilisees quand information indique qu'il y a des informations disponibles
//et que etatDuModule indique que le module est en fonction.
//Les valeurs sont mises a jour quand information indique qu'elles ont ete traitees et que le
//module est en fonction.

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACECRCCONNECT_PHASE_DANS_LOOP 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACECRCCONNECT_MODULE_EN_FONCTION 1
#define INTERFACECRCCONNECT_MODULE_PAS_EN_FONCTION 0
#define INTERFACECRCCONNECT_INFORMATION_DISPONIBLE 1
#define INTERFACECRCCONNECT_INFORMATION_TRAITEE 0
#define INTERFACECRCCONNECT_VALEUR_ACTIVE  1   
#define INTERFACECRCCONNECT_VALEUR_INACTIVE 0
#define INTERFACECRCCONNECT_VALEUR_INVALIDE 2

#define INTERFACECRCCONNECT_NOMBRE_DE_VALEURS        21
#define INTERFACECRCCONNECT_BOUTON_BACK              0
#define INTERFACECRCCONNECT_BOUTON_START             1
#define INTERFACECRCCONNECT_BOUTON_GAUCHE            2
#define INTERFACECRCCONNECT_BOUTON_DROIT             3
#define INTERFACECRCCONNECT_BOUTON_JOYSTICK_GAUCHE   4
#define INTERFACECRCCONNECT_BOUTON_JOYSTICK_DROIT    5
#define INTERFACECRCCONNECT_BOUTON_LOGO              6
#define INTERFACECRCCONNECT_FLECHE_DROITE            7
#define INTERFACECRCCONNECT_FLECHE_HAUTE             8
#define INTERFACECRCCONNECT_FLECHE_GAUCHE            9
#define INTERFACECRCCONNECT_FLECHE_BASSE             10
#define INTERFACECRCCONNECT_BOUTON_B                 11
#define INTERFACECRCCONNECT_BOUTON_Y                 12
#define INTERFACECRCCONNECT_BOUTON_X                 13
#define INTERFACECRCCONNECT_BOUTON_A                 14
#define INTERFACECRCCONNECT_JOYSTICK_GAUCHE_X        15
#define INTERFACECRCCONNECT_JOYSTICK_GAUCHE_Y        16
#define INTERFACECRCCONNECT_JOYSTICK_DROIT_X         17
#define INTERFACECRCCONNECT_JOYSTICK_DROIT_Y         18
#define INTERFACECRCCONNECT_GACHETTE_GAUCHE          19
#define INTERFACECRCCONNECT_GACHETTE_DROITE          20

typedef struct
{
  char valeurLue[INTERFACECRCCONNECT_NOMBRE_DE_VALEURS];
  unsigned char etatDuModule;
  unsigned char information;
} INTERFACECRCCONNECT;

//Fonctions publiques:
void interfaceCRCConnect_initialise(void);

//Variables publiques:
extern INTERFACECRCCONNECT interfaceCRCConnect;

#endif
