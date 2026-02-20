//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWI.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWI.h"


//Definitions privees
#define INTERFACEENTREESWI_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWI_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWI_COMPTE_INITIAL (\
  INTERFACEENTREESWI_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWI_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWI_compteurAvantLecture;
unsigned int interfaceEntreeSWI_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWI_gere(void)
{
  interfaceEntreeSWI_compteurAvantLecture++;
  if (interfaceEntreeSWI_compteurAvantLecture < INTERFACEENTREESWI_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWI_compteurAvantLecture = 0;
  if (piloteEntreeSWI_lit() == INTERFACEENTREESWI_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWI_compteurAntiRebond == INTERFACEENTREESWI_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWI_compteurAntiRebond++;
    if (interfaceEntreeSWI_compteurAntiRebond < INTERFACEENTREESWI_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWI.etatDeLEntree == INTERFACEENTREESWI_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWI.etatDuModule = INTERFACEENTREESWI_MODULE_EN_FONCTION;
    interfaceEntreeSWI.etatDeLEntree = INTERFACEENTREESWI_ACTIVE;
    interfaceEntreeSWI.information = INTERFACEENTREESWI_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWI_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWI_compteurAntiRebond--;
  if (interfaceEntreeSWI_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWI.etatDeLEntree == INTERFACEENTREESWI_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWI.etatDuModule = INTERFACEENTREESWI_MODULE_EN_FONCTION;  
  interfaceEntreeSWI.etatDeLEntree = INTERFACEENTREESWI_INACTIVE;
  interfaceEntreeSWI.information = INTERFACEENTREESWI_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWI interfaceEntreeSWI;

//Definitions de fonctions publiques:
void interfaceEntreeSWI_initialise(void)
{
  interfaceEntreeSWI.etatDuModule = INTERFACEENTREESWI_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWI.information = INTERFACEENTREESWI_INFORMATION_TRAITEE;
  interfaceEntreeSWI.etatDeLEntree = INTERFACEENTREESWI_PAS_EN_FONCTION;
  interfaceEntreeSWI_compteurAvantLecture = 0;
  interfaceEntreeSWI_compteurAntiRebond = INTERFACEENTREESWI_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWI_PHASE] = interfaceEntreeSWI_gere;
}
