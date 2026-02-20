#ifndef INTERFACEVEXPINCE_H
#define INTERFACEVEXPINCE_H

//MODULE: interfaceVEXPince
//DESCRIPTION: pour commander la vitesse et le sens de rotation d'un moteur
//a l'aide d'un variateur de vitesse VEXPRO.
//Les rapports cycliques utilises pour la commande implique de signaux
//qui se doivent d'etre a un pendant un temps qui va de 
//INTERFACEVEXPINCE_DUREE_MINIMALE_EN_US et INTERFACEVEXPINCE_DUREE_MINIMALE_EN_US
//INTERFACEVEXPINCE_VALEUR_INITIALE_EN_US sert a determine le signal qui est
//produit par defaut suite a l'initialisation du module.
//INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_REQUISE et
//INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_PAS_REQUISE servent a associer un
//sens de rotation aux valeurs de commande positives. Une seule de ces
//deux definitions doit etre definie dans main.h. Le choix de la definition
//depend des besoins et de la connexion entre le VEXPRO et le moteur qu'il commande.
//La fonction interfaceVEXPince_metA(char Valeur) permet de selectionner le rapport cyclique du signal
//PWM. Valeur doit se situer entre -128 et 127 inclusivement.
// 2025-11-24, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEVEXPINCE_BROCHE CRC_PWM_1
//#define INTERFACEVEXPINCE_DUREE_MINIMALE_EN_US 1000
//#define INTERFACEVEXPINCE_DUREE_MAXIMALE_EN_US 2000
//#define INTERFACEVEXPINCE_VALEUR_INITIALE 0
//#define INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_REQUISE
//#define INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_PAS_REQUISE

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void interfaceVEXPince_metALArret(void);
void interfaceVEXPince_metA(char Valeur);
void interfaceVEXPince_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
