//piloteSortieT1:
//Historique: 
// 2025-11-23, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteSortieT1.h"

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
void piloteSortieT1_metAUn(void)
{
  CrcLib::SetDigitalOutput(PILOTESORTIET1_BROCHE, HIGH);
}

void piloteSortieT1_metAZero(void)
{
  CrcLib::SetDigitalOutput(PILOTESORTIET1_BROCHE, LOW);
}

void piloteSortieT1_metA(unsigned char Niveau)
{
  CrcLib::SetDigitalOutput(PILOTESORTIET1_BROCHE, Niveau);
}

void piloteSortieT1_initialise(void)
{
  CrcLib::SetDigitalPinMode(PILOTESORTIET1_BROCHE,OUTPUT);

#ifdef PILOTESORTIET1_ETAT_INITIAL_A_UN
	CrcLib::SetDigitalOutput(PILOTESORTIET1_BROCHE,HIGH);
#endif

#ifdef PILOTESORTIET1_ETAT_INITIAL_A_ZERO
	CrcLib::SetDigitalOutput(PILOTESORTIET1_BROCHE,LOW);
#endif
}
