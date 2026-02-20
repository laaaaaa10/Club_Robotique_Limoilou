//interfaceVEXElevateur:
//Historique: 
// 2025-11-30, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xinterfaceVEXElevateur.h"

#ifdef INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_REQUISE
  #ifdef INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_PAS_REQUISE)
    #error "INTERFACEVEXELEVATEUR: utiliser une seule definition"
  #endif
#endif

//Definitions privees
#define INTERFACEVEXELEVATEUR_INVERSE 1
#define INTERFACEVEXELEVATEUR_PAS_INVERSE 0
#define INTERFACEVEXELEVATEUR_VALEUR_POUR_ARRET 0

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceVEXElevateur_metALArret(void)
{
  CrcLib::SetPwmOutput(INTERFACEVEXELEVATEUR_BROCHE, INTERFACEVEXELEVATEUR_VALEUR_POUR_ARRET);
}

void interfaceVEXElevateur_metA(char Valeur)
{
  CrcLib::SetPwmOutput(INTERFACEVEXELEVATEUR_BROCHE, Valeur);
}

void interfaceVEXElevateur_initialise(void)
{
#ifdef INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXELEVATEUR_BROCHE,
      INTERFACEVEXELEVATEUR_DUREE_MINIMALE_EN_US, INTERFACEVEXELEVATEUR_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXELEVATEUR_INVERSE);
#endif
#ifdef INTERFACEVEXELEVATEUR_INVERSION_DE_COMMANDE_PAS_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXELEVATEUR_BROCHE,
      INTERFACEVEXELEVATEUR_DUREE_MINIMALE_EN_US, INTERFACEVEXELEVATEUR_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXELEVATEUR_PAS_INVERSE);
#endif
  CrcLib::SetPwmOutput(INTERFACEVEXELEVATEUR_BROCHE, INTERFACEVEXELEVATEUR_VALEUR_INITIALE);
}
