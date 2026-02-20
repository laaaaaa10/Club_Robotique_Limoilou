//piloteEntreeSWS:
//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSWS.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteEntreeSWS_lit(void)
{
  return CrcLib::GetDigitalInput(PILOTEENTREESWS_BROCHE);
}

void piloteEntreeSWS_initialise(void)
{
#ifdef PILOTEENTREESWS_MODE_FLOTTANT_AVEC_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWS_BROCHE, INPUT_PULLUP);
#endif

#ifdef PILOTEENTREESWS_MODE_FLOTTANT_SANS_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWS_BROCHE, INPUT);
#endif
}
