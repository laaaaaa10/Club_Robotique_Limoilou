#ifndef INTERFACEVEXBRAS_H
#define INTERFACEVEXBRAS_H

//MODULE: interfaceVEXBras
//DESCRIPTION: pour commander la vitesse et le sens de rotation d'un moteur
//a l'aide d'un variateur de vitesse VEXPRO.
//Les rapports cycliques utilises pour la commande implique de signaux
//qui se doivent d'etre a un pendant un temps qui va de 
//INTERFACEVEXBRAS_DUREE_MINIMALE_EN_US et INTERFACEVEXBRAS_DUREE_MINIMALE_EN_US
//INTERFACEVEXBRAS_VALEUR_INITIALE_EN_US sert a determine le signal qui est
//produit par defaut suite a l'initialisation du module.
//INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_REQUISE et
//INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_PAS_REQUISE servent a associer un
//sens de rotation aux valeurs de commande positives. Une seule de ces
//deux definitions doit etre definie dans main.h. Le choix de la definition
//depend des besoins et de la connexion entre le VEXPRO et le moteur qu'il commande.
//La fonction interfaceVEXBras_metA(char Valeur) permet de selectionner le rapport cyclique du signal
//PWM. Valeur doit se situer entre -128 et 127 inclusivement.
// 2025-12-01, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEVEXBRAS_BROCHE CRC_PWM_1
//#define INTERFACEVEXBRAS_DUREE_MINIMALE_EN_US 1000
//#define INTERFACEVEXBRAS_DUREE_MAXIMALE_EN_US 2000
//#define INTERFACEVEXBRAS_VALEUR_INITIALE 0
//#define INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_REQUISE
//#define INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_PAS_REQUISE

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void interfaceVEXBras_metALArret(void);
void interfaceVEXBras_metA(char Valeur);
void interfaceVEXBras_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
