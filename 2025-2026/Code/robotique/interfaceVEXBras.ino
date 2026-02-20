//interfaceVEXBras:
//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xinterfaceVEXBras.h"

#ifdef INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_REQUISE
  #ifdef INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_PAS_REQUISE)
    #error "INTERFACEVEXBRAS: utiliser une seule definition"
  #endif
#endif

//Definitions privees
#define INTERFACEVEXBRAS_INVERSE 1
#define INTERFACEVEXBRAS_PAS_INVERSE 0
#define INTERFACEVEXBRAS_VALEUR_POUR_ARRET 0

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceVEXBras_metALArret(void)
{
  CrcLib::SetPwmOutput(INTERFACEVEXBRAS_BROCHE, INTERFACEVEXBRAS_VALEUR_POUR_ARRET);
}

void interfaceVEXBras_metA(char Valeur)
{
  CrcLib::SetPwmOutput(INTERFACEVEXBRAS_BROCHE, Valeur);
}

void interfaceVEXBras_initialise(void)
{
#ifdef INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXBRAS_BROCHE,
      INTERFACEVEXBRAS_DUREE_MINIMALE_EN_US, INTERFACEVEXBRAS_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXBRAS_INVERSE);
#endif
#ifdef INTERFACEVEXBRAS_INVERSION_DE_COMMANDE_PAS_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXBRAS_BROCHE,
      INTERFACEVEXBRAS_DUREE_MINIMALE_EN_US, INTERFACEVEXBRAS_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXBRAS_PAS_INVERSE);
#endif
  CrcLib::SetPwmOutput(INTERFACEVEXBRAS_BROCHE, INTERFACEVEXBRAS_VALEUR_INITIALE);
}
