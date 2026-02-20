//piloteEntreeSWB:
//Historique: 
// 2025-11-30, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSWB.h"

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
unsigned char piloteEntreeSWB_lit(void)
{
  return CrcLib::GetDigitalInput(PILOTEENTREESWB_BROCHE);
}

void piloteEntreeSWB_initialise(void)
{
#ifdef PILOTEENTREESWB_MODE_FLOTTANT_AVEC_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWB_BROCHE, INPUT_PULLUP);
#endif

#ifdef PILOTEENTREESWB_MODE_FLOTTANT_SANS_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWB_BROCHE, INPUT);
#endif
}
