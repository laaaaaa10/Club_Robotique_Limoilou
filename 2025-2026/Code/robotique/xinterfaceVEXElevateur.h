#ifndef INTERFACEVEXELEVATEUR_H
#define INTERFACEVEXELEVATEUR_H

//MODULE: interfaceVEXElevateur
//DESCRIPTION: pour commander la vitesse et le sens de rotation d'un moteur
//a l'aide d'un variateur de vitesse VEXPRO.
//Les rapports cycliques utilises pour la commande implique de signaux
//qui se doivent d'etre a un pendant un temps qui va de 
//INTERFACEVEXELEVATEUR_DUREE_MINIMALE_EN_US et INTERFACEVEXELEVATEUR_DUREE_MINIMALE_EN_US
//INTERFACEVEXELEVATEUR_VALEUR_INITIALE_EN_US sert a determine le signal qui est
//produit par defaut suite a l'initialisation du module.
//INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_REQUISE et
//INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_PAS_REQUISE servent a associer un
//sens de rotation aux valeurs de commande positives. Une seule de ces
//deux definitions doit etre definie dans main.h. Le choix de la definition
//depend des besoins et de la connexion entre le VEXPRO et le moteur qu'il commande.
//La fonction interfaceVEXElevateur_metA(char Valeur) permet de selectionner le rapport cyclique du signal
//PWM. Valeur doit se situer entre -128 et 127 inclusivement.
// 2025-11-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEVEXELEVATEUR_BROCHE CRC_PWM_1
//#define INTERFACEVEXELEVATEUR_DUREE_MINIMALE_EN_US 1000
//#define INTERFACEVEXELEVATEUR_DUREE_MAXIMALE_EN_US 2000
//#define INTERFACEVEXELEVATEUR_VALEUR_INITIALE 0
//#define INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_REQUISE
//#define INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_PAS_REQUISE

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void interfaceVEXElevateur_metALArret(void);
void interfaceVEXElevateur_metA(char Valeur);
void interfaceVEXElevateur_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
