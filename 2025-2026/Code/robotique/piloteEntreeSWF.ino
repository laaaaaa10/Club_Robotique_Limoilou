//piloteEntreeSWF:
//Historique: 
// 2025-11-26, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSWF.h"

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
unsigned char piloteEntreeSWF_lit(void)
{
  return CrcLib::GetDigitalInput(PILOTEENTREESWF_BROCHE);
}

void piloteEntreeSWF_initialise(void)
{
#ifdef PILOTEENTREESWF_MODE_FLOTTANT_AVEC_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWF_BROCHE, INPUT_PULLUP);
#endif

#ifdef PILOTEENTREESWF_MODE_FLOTTANT_SANS_PULL_UP
  CrcLib::SetDigitalPinMode(PILOTEENTREESWF_BROCHE, INPUT);
#endif
}
