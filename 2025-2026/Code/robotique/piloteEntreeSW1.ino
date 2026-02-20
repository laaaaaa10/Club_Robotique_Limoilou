//piloteEntreeSW1:
//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSW1.h"

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
unsigned char piloteEntreeSW1_lit(void)
{
  return CrcLib::GetDigitalInput(PILOTEENTREESW1_BROCHE);
}

void piloteEntreeSW1_initialise(void)
{
#ifdef PILOTEENTREESW1_MODE_FLOTTANT_AVEC_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESW1_BROCHE, INPUT_PULLUP);
#endif

#ifdef PILOTEENTREESW1_MODE_FLOTTANT_SANS_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESW1_BROCHE, INPUT);
#endif
}
