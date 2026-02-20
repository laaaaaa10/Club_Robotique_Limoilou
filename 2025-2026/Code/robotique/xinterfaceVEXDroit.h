#ifndef INTERFACEVEXDROIT_H
#define INTERFACEVEXDROIT_H

//MODULE: interfaceVEXDroit
//DESCRIPTION: pour commander la vitesse et le sens de rotation d'un moteur
//a l'aide d'un variateur de vitesse VEXPRO.
//Les rapports cycliques utilises pour la commande implique de signaux
//qui se doivent d'etre a un pendant un temps qui va de 
//INTERFACEVEXDROIT_DUREE_MINIMALE_EN_US et INTERFACEVEXDROIT_DUREE_MINIMALE_EN_US
//INTERFACEVEXDROIT_VALEUR_INITIALE_EN_US sert a determine le signal qui est
//produit par defaut suite a l'initialisation du module.
//INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_REQUISE et
//INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_PAS_REQUISE servent a associer un
//sens de rotation aux valeurs de commande positives. Une seule de ces
//deux definitions doit etre definie dans main.h. Le choix de la definition
//depend des besoins et de la connexion entre le VEXPRO et le moteur qu'il commande.
//La fonction interfaceVEXDroit_metA(char Valeur) permet de selectionner le rapport cyclique du signal
//PWM. Valeur doit se situer entre -128 et 127 inclusivement.
// 2025-11-24, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEVEXDROIT_BROCHE CRC_PWM_1
//#define INTERFACEVEXDROIT_DUREE_MINIMALE_EN_US 1000
//#define INTERFACEVEXDROIT_DUREE_MAXIMALE_EN_US 2000
//#define INTERFACEVEXDROIT_VALEUR_INITIALE 0
//#define INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_REQUISE
//#define INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_PAS_REQUISE

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void interfaceVEXDroit_metALArret(void);
void interfaceVEXDroit_metA(char Valeur);
void interfaceVEXDroit_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
