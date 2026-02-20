#ifndef INTERFACESORTIEDEL_H
#define INTERFACESORTIEDEL_H

//MODULE: interfaceSortieDEL
//DESCRIPTION: pour s'interfacer avec une DEL qui est connecte à la sortie numerique SortieDIO 

//HISTORIQUE:
// 2025-11-19, Yves Roy, creation


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACESORTIEDEL_VALEUR_POUR_ALLUMER  1   
//#define INTERFACESORTIEDEL_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceSortieDEL_allume(void);
void interfaceSortieDEL_eteint(void);
void interfaceSortieDEL_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
