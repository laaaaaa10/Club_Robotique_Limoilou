//interfaceDEL:
//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteSortieDEL.h"
#include "xinterfaceSortieDEL.h"

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
void interfaceSortieDEL_allume(void)
{
  piloteSortieDEL_metA(INTERFACESORTIEDEL_VALEUR_POUR_ALLUMER);
}

void interfaceSortieDEL_eteint(void)
{
  piloteSortieDEL_metA(INTERFACESORTIEDEL_VALEUR_POUR_ETEINDRE);
}

void interfaceSortieDEL_initialise(void)
{
  piloteSortieDEL_metA(INTERFACESORTIEDEL_VALEUR_POUR_ETEINDRE);
}
