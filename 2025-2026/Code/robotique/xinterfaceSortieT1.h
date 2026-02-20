#ifndef INTERFACESORTIET1_H
#define INTERFACESORTIET1_H

//MODULE: interfaceSortieT1
//DESCRIPTION: pour s'interfacer avec une DEL qui est connecte à la sortie numerique SortieDIO 

//HISTORIQUE:
// 2025-11-23, Yves Roy, creation


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACESORTIET1_VALEUR_POUR_ALLUMER  1   
//#define INTERFACESORTIET1_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceSortieT1_allume(void);
void interfaceSortieT1_eteint(void);
void interfaceSortieT1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
