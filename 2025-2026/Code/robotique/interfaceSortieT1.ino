//interfaceSortieT1:
//Historique: 
// 2025-11-23, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteSortieT1.h"
#include "xinterfaceSortieT1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceSortieT1_allume(void)
{
  piloteSortieT1_metA(INTERFACESORTIET1_VALEUR_POUR_ALLUMER);
}

void interfaceSortieT1_eteint(void)
{
  piloteSortieT1_metA(INTERFACESORTIET1_VALEUR_POUR_ETEINDRE);
}

void interfaceSortieT1_initialise(void)
{
  piloteSortieT1_metA(INTERFACESORTIET1_VALEUR_POUR_ETEINDRE);
}
