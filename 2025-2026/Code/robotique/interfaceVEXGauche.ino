//interfaceVEXGauche:
//Historique: 
// 2025-11-24, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xinterfaceVEXGauche.h"

#ifdef INTERFACEVEXGAUCHE_INVERSION_DE_COMMANDE_REQUISE
  #ifdef INTERFACEVEXGAUCHE_INVERSION_DE_COMMANDE_PAS_REQUISE)
    #error "INTERFACEVEXGAUCHE: utiliser une seule definition"
  #endif
#endif

//Definitions privees
#define INTERFACEVEXGAUCHE_INVERSE 1
#define INTERFACEVEXGAUCHE_PAS_INVERSE 0
#define INTERFACEVEXGAUCHE_VALEUR_POUR_ARRET 0

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceVEXGauche_metALArret(void)
{
  CrcLib::SetPwmOutput(INTERFACEVEXGAUCHE_BROCHE, INTERFACEVEXGAUCHE_VALEUR_POUR_ARRET);
}

void interfaceVEXGauche_metA(char Valeur)
{
  CrcLib::SetPwmOutput(INTERFACEVEXGAUCHE_BROCHE, Valeur);
}

void interfaceVEXGauche_initialise(void)
{
#ifdef INTERFACEVEXGAUCHE_INVERSION_DE_COMMANDE_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXGAUCHE_BROCHE,
      INTERFACEVEXGAUCHE_DUREE_MINIMALE_EN_US, INTERFACEVEXGAUCHE_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXGAUCHE_INVERSE);
#endif
#ifdef INTERFACEVEXGAUCHE_INVERSION_DE_COMMANDE_PAS_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXGAUCHE_BROCHE,
      INTERFACEVEXGAUCHE_DUREE_MINIMALE_EN_US, INTERFACEVEXGAUCHE_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXGAUCHE_PAS_INVERSE);
#endif
  CrcLib::SetPwmOutput(INTERFACEVEXGAUCHE_BROCHE, INTERFACEVEXGAUCHE_VALEUR_INITIALE);
}
