#ifndef PROCESSUSELEVATEUR_H
#define PROCESSUSELEVATEUR_H

//MODULE: processusElevateur
//DESCRIPTION: implemente la gestion d'un moteur commande par un variateur VEXPRO. Deux boutons
//du CRCConnect sont utilises pour selectionner le sens de rotation du moteur. Les vitesses
//de rotation sont determinees par les definitions
//PROCESSUS

//HISTORIQUE:
// 2025-11-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSELEVATEUR_BOUTON_DESCENDRE SERVICEMANETTE_BOUTON_GAUCHE
//#define PROCESSUSELEVATEUR_BOUTON_MONTER SERVICEMANETTE_BOUTON_DROIT
//#define PROCESSUSELEVATEUR_VALEUR_POUR_DESCENDRE 127
//#define PROCESSUSELEVATEUR_VALEUR_POUR_MONTER -128
//#define PROCESSUSELEVATEUR_VALEUR_POUR_REMONTER -25 
//#define PROCESSUSELEVATEUR_TEMPS_MAXIMUM_POUR_DESCENDRE_EN_SECONDES 10
//#define PROCESSUSELEVATEUR_TEMPS_MAXIMUM_POUR_MONTER_EN_SECONDES 10
//#define PROCESSUSELEVATEUR_TEMPS_POUR_REMONTER_EN_MS  1000

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSELEVATEUR_PHASE 0
//#define PROCESSUSELEVATEUR_TEMPS_DE_DEPART_EN_SECONDES 2


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSELEVATEUR_MODULE_EN_FONCTION     0
#define PROCESSUSELEVATEUR_MODULE_PAS_EN_FONCTION 1
#define PROCESSUSELEVATEUR_PAS_D_ERREUR           0
#define PROCESSUSELEVATEUR_ERREUR_D_INTERRUPTEURS 1
#define PROCESSUSELEVATEUR_ERREUR_DE_DESCENTE     2
#define PROCESSUSELEVATEUR_ERREUR_DE_MONTEE       4

#define PROCESSUSELEVATEUR_REQUETE_ACTIVE         1
#define PROCESSUSELEVATEUR_REQUETE_TRAITEE        0
#define PROCESSUSELEVATEUR_COMMANDE_DESCEND       0
#define PROCESSUSELEVATEUR_COMMANDE_MONTE         1
#define PROCESSUSELEVATEUR_COMMANDE_REMONTE       2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char statut;
  unsigned char requete;
  unsigned char commande;
} PROCESSUSELEVATEUR;


//Fonctions publiques:
void processusElevateur_initialise(void);

//Variables publiques:
extern PROCESSUSELEVATEUR processusElevateur;

#endif
