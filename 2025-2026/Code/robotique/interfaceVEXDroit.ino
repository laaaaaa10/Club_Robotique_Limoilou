//interfaceVEXDroit:
//Historique: 
// 2025-11-24, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xinterfaceVEXDroit.h"

#ifdef INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_REQUISE
  #ifdef INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_PAS_REQUISE)
    #error "INTERFACEVEXDROIT: utiliser une seule definition"
  #endif
#endif

//Definitions privees
#define INTERFACEVEXDROIT_INVERSE 1
#define INTERFACEVEXDROIT_PAS_INVERSE 0
#define INTERFACEVEXDROIT_VALEUR_POUR_ARRET 0

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceVEXDroit_metALArret(void)
{
  CrcLib::SetPwmOutput(INTERFACEVEXDROIT_BROCHE, INTERFACEVEXDROIT_VALEUR_POUR_ARRET);
}

void interfaceVEXDroit_metA(char Valeur)
{
  CrcLib::SetPwmOutput(INTERFACEVEXDROIT_BROCHE, Valeur);
}

void interfaceVEXDroit_initialise(void)
{
#ifdef INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXDROIT_BROCHE,
      INTERFACEVEXDROIT_DUREE_MINIMALE_EN_US, INTERFACEVEXDROIT_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXDROIT_INVERSE);
#endif
#ifdef INTERFACEVEXDROIT_INVERSION_DE_COMMANDE_PAS_REQUISE
  CrcLib::InitializePwmOutput(INTERFACEVEXDROIT_BROCHE,
      INTERFACEVEXDROIT_DUREE_MINIMALE_EN_US, INTERFACEVEXDROIT_DUREE_MAXIMALE_EN_US,
      INTERFACEVEXDROIT_PAS_INVERSE);
#endif
  CrcLib::SetPwmOutput(INTERFACEVEXDROIT_BROCHE, INTERFACEVEXDROIT_VALEUR_INITIALE);
}
