//Historique: 
// 2025-11-30, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWB.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWB.h"


//Definitions privees
#define INTERFACEENTREESWB_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWB_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWB_COMPTE_INITIAL (\
  INTERFACEENTREESWB_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWB_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWB_compteurAvantLecture;
unsigned int interfaceEntreeSWB_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWB_gere(void)
{
  interfaceEntreeSWB_compteurAvantLecture++;
  if (interfaceEntreeSWB_compteurAvantLecture < INTERFACEENTREESWB_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWB_compteurAvantLecture = 0;
  if (piloteEntreeSWB_lit() == INTERFACEENTREESWB_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWB_compteurAntiRebond == INTERFACEENTREESWB_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWB_compteurAntiRebond++;
    if (interfaceEntreeSWB_compteurAntiRebond < INTERFACEENTREESWB_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWB.etatDeLEntree == INTERFACEENTREESWB_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWB.etatDuModule = INTERFACEENTREESWB_MODULE_EN_FONCTION;
    interfaceEntreeSWB.etatDeLEntree = INTERFACEENTREESWB_ACTIVE;
    interfaceEntreeSWB.information = INTERFACEENTREESWB_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWB_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWB_compteurAntiRebond--;
  if (interfaceEntreeSWB_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWB.etatDeLEntree == INTERFACEENTREESWB_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWB.etatDuModule = INTERFACEENTREESWB_MODULE_EN_FONCTION;  
  interfaceEntreeSWB.etatDeLEntree = INTERFACEENTREESWB_INACTIVE;
  interfaceEntreeSWB.information = INTERFACEENTREESWB_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWB interfaceEntreeSWB;

//Definitions de fonctions publiques:
void interfaceEntreeSWB_initialise(void)
{
  interfaceEntreeSWB.etatDuModule = INTERFACEENTREESWB_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWB.information = INTERFACEENTREESWB_INFORMATION_TRAITEE;
  interfaceEntreeSWB.etatDeLEntree = INTERFACEENTREESWB_PAS_EN_FONCTION;
  interfaceEntreeSWB_compteurAvantLecture = 0;
  interfaceEntreeSWB_compteurAntiRebond = INTERFACEENTREESWB_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWB_PHASE] = interfaceEntreeSWB_gere;
}
