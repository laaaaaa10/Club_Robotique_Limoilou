#ifndef PROCESSUSMOTORISATION_H
#define PROCESSUSMOTORISATION_H

//MODULE: processusMotorisation
//DESCRIPTION: implemente la gestion d'une paire de moteurs commande par deux variateurs VEXPRO. Un des
//joystick du CRCConnect est utilise pour selectionner la vitesse et le sens de rotation des moteurs.
//Le fait d'appuyer sur le joystick pour activer l'interrupteur qu'il renferme reduit la vitesse maximale
//des moteurs pour rendre la conduite plus precise.
//Les valeurs utilisees pour commander les variateurs se situent entre
//PROCESSUSMOTORISATION_VALEUR_MAXIMALE et -PROCESSUSMOTORISATION_VALEUR_MAXIMALE quand l'interrupteur du
//joystick n'est pas active.
//Les valeurs utilisees pour commander les variateurs se situent entre
//PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE et -PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE 
//quand l'interrupteur du joystick est active.
//Les valeurs X et Y produites par le joystick sont consideres comme etant nulle quand elles se situe
//entre PROCESSUSMOTORISATION_SEUIL_DE_DETECTION et -PROCESSUSMOTORISATION_SEUIL_DE_DETECTION.

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSMOTORISATION_JOYSTICK_X  SERVICEMANETTE_JOYSTICK_GAUCHE_X
//#define PROCESSUSMOTORISATION_JOYSTICK_Y  SERVICEMANETTE_JOYSTICK_GAUCHE_Y
//#define PROCESSUSMOTORISATION_BOUTON_JOYSTICK SERVICEMANETTE_BOUTON_JOYSTICK_GAUCHE
//#define PROCESSUSMOTORISATION_VALEUR_MAXIMALE 125
//#define PROCESSUSMOTORISATION_SEUIL_DE_DETECTION 5
//#define PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE 50

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSMOTORISATION_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSMOTORISATION_MODULE_EN_FONCTION 0
#define PROCESSUSMOTORISATION_MODULE_PAS_EN_FONCTION 1

typedef struct
{
  unsigned char etatDuModule;  
} PROCESSUSMOTORISATION;

//Fonctions publiques:
void processusMotorisation_initialise(void);

//Variables publiques:
extern PROCESSUSMOTORISATION processusMotorisation;

#endif
