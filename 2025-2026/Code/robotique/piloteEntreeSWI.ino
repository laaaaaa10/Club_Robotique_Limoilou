//piloteEntreeSWI:
//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSWI.h"

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
unsigned char piloteEntreeSWI_lit(void)
{
  return CrcLib::GetDigitalInput(PILOTEENTREESWI_BROCHE);
}

void piloteEntreeSWI_initialise(void)
{
#ifdef PILOTEENTREESWI_MODE_FLOTTANT_AVEC_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWI_BROCHE, INPUT_PULLUP);
#endif

#ifdef PILOTEENTREESWI_MODE_FLOTTANT_SANS_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWI_BROCHE, INPUT);
#endif
}
