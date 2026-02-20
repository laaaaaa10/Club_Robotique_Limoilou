//interfaceVEXPince:
//Historique: 
// 2025-11-24, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xinterfaceVEXPince.h"

#ifdef INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_REQUISE
  #ifdef INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_PAS_REQUISE)
    #error "INTERFACEVEXPINCE: utiliser une seule definition"
  #endif
#endif

//Definitions privees
#define INTERFACEVEXPINCE_INVERSE 1
#define INTERFACEVEXPINCE_PAS_INVERSE 0
#define INTERFACEVEXPINCE_VALEUR_POUR_ARRET 0

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceVEXPince_metALArret(void)
{
  CrcLib::SetPwmOutput(INTERFACEVEXPINCE_BROCHE, INTERFACEVEXPINCE_VALEUR_POUR_ARRET);
}

void interfaceVEXPince_metA(char Valeur)
{
  CrcLib::SetPwmOutput(INTERFACEVEXPINCE_BROCHE, Valeur);
}

void interfaceVEXPince_initialise(void)
{
#ifdef INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXPINCE_BROCHE,
      INTERFACEVEXPINCE_DUREE_MINIMALE_EN_US, INTERFACEVEXPINCE_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXPINCE_INVERSE);
#endif
#ifdef INTERFACEVEXPINCE_INVERSION_DE_COMMANDE_PAS_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXPINCE_BROCHE,
      INTERFACEVEXPINCE_DUREE_MINIMALE_EN_US, INTERFACEVEXPINCE_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXPINCE_PAS_INVERSE);
#endif
  CrcLib::SetPwmOutput(INTERFACEVEXPINCE_BROCHE, INTERFACEVEXPINCE_VALEUR_INITIALE);
}
