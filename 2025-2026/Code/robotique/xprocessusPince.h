#ifndef PROCESSUSPINCE_H
#define PROCESSUSPINCE_H

//MODULE: processusPince
//DESCRIPTION: implemente la gestion d'un moteur commande par un variateur VEXPRO. Deux boutons
//du CRCConnect sont utilises pour selectionner le sens de rotation du moteur. Les vitesses
//de rotation sont determinees par les definitions
//PROCESSUS

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSPINCE_BOUTON_FERMER  SERVICEMANETTE_BOUTON_BACK
//#define PROCESSUSPINCE_BOUTON_OUVRIR  SERVICEMANETTE_BOUTON_START
//#define PROCESSUSPINCE_VALEUR_POUR_FERMER 127
//#define PROCESSUSPINCE_VALEUR_POUR_OUVRIR -128
//#define PROCESSUSPINCE_VALEUR_POUR_ENTROUVRIR -50
//#define PROCESSUSPINCE_TEMPS_MAXIMUM_POUR_FERMER_EN_SECONDES        3
//#define PROCESSUSPINCE_TEMPS_MAXIMUM_POUR_OUVRIR_EN_SECONDES        3
//#define PROCESSUSPINCE_TEMPS_POUR_ENTROUVRIR_EN_MS                  500

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSPINCE_PHASE 0
//#define PROCESSUSPINCE_TEMPS_DE_DEPART_EN_SECONDES 2


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSPINCE_MODULE_EN_FONCTION     0
#define PROCESSUSPINCE_MODULE_PAS_EN_FONCTION 1
#define PROCESSUSPINCE_MODULE_EN_MODE_MANUEL  2
#define PROCESSUSPINCE_PAS_D_ERREUR           0
#define PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS 1
#define PROCESSUSPINCE_ERREUR_DE_FERMETURE    2
#define PROCESSUSPINCE_ERREUR_D_OUVERTURE     4

#define PROCESSUSPINCE_REQUETE_ACTIVE         1
#define PROCESSUSPINCE_REQUETE_TRAITEE        0
#define PROCESSUSPINCE_COMMANDE_FERMER        0
#define PROCESSUSPINCE_COMMANDE_OUVRIR        1
#define PROCESSUSPINCE_COMMANDE_ENTROUVRIR    2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char statut;
  unsigned char requete;
  unsigned char commande;
} PROCESSUSPINCE;


//Fonctions publiques:
void processusPince_initialise(void);

//Variables publiques:
extern PROCESSUSPINCE processusPince;


#endif
