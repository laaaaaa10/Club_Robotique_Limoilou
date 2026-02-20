//piloteSortieDEL:
//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteSortieDEL.h"

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
void piloteSortieDEL_metAUn(void)
{
  CrcLib::SetDigitalOutput(PILOTESORTIEDEL_BROCHE, HIGH);
}

void piloteSortieDEL_metAZero(void)
{
  CrcLib::SetDigitalOutput(PILOTESORTIEDEL_BROCHE, LOW);
}

void piloteSortieDEL_metA(unsigned char Niveau)
{
  CrcLib::SetDigitalOutput(PILOTESORTIEDEL_BROCHE, Niveau);
}

void piloteSortieDEL_initialise(void)
{
  CrcLib::SetDigitalPinMode(PILOTESORTIEDEL_BROCHE,OUTPUT);

#ifdef PILOTESORTIEDEL_ETAT_INITIAL_A_UN
	CrcLib::SetDigitalOutput(PILOTESORTIEDEL_BROCHE,HIGH);
#endif

#ifdef PILOTESORTIEDEL_ETAT_INITIAL_A_ZERO
	CrcLib::SetDigitalOutput(PILOTESORTIEDEL_BROCHE,LOW);
#endif
}
