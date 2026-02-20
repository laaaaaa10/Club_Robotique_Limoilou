//piloteEntreeANA:
//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeANA.h"

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
unsigned int piloteEntreeANA_lit(void)
{
  return analogRead(PILOTEENTREEANA_BROCHE);
}

void piloteEntreeANA_initialise(void)
{
//  analogReadResolution(12);
//  analogSetWidth(12);
//  analogSetCycles(8); //ne marche plus avec la mise a jour?
//  analogSetSamples(1);
//  analogSetClockDiv(1);
//  analogSetPinAttenuation(PILOTEENTREEANA_BROCHE, ADC_11db);  
}
