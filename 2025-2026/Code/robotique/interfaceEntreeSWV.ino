//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWV.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWV.h"


//Definitions privees
#define INTERFACEENTREESWV_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWV_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWV_COMPTE_INITIAL (\
  INTERFACEENTREESWV_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWV_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWV_compteurAvantLecture;
unsigned int interfaceEntreeSWV_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWV_gere(void)
{
  interfaceEntreeSWV_compteurAvantLecture++;
  if (interfaceEntreeSWV_compteurAvantLecture < INTERFACEENTREESWV_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWV_compteurAvantLecture = 0;
  if (piloteEntreeSWV_lit() == INTERFACEENTREESWV_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWV_compteurAntiRebond == INTERFACEENTREESWV_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWV_compteurAntiRebond++;
    if (interfaceEntreeSWV_compteurAntiRebond < INTERFACEENTREESWV_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWV.etatDuModule = INTERFACEENTREESWV_MODULE_EN_FONCTION;
    interfaceEntreeSWV.etatDeLEntree = INTERFACEENTREESWV_ACTIVE;
    interfaceEntreeSWV.information = INTERFACEENTREESWV_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWV_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWV_compteurAntiRebond--;
  if (interfaceEntreeSWV_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWV.etatDuModule = INTERFACEENTREESWV_MODULE_EN_FONCTION;  
  interfaceEntreeSWV.etatDeLEntree = INTERFACEENTREESWV_INACTIVE;
  interfaceEntreeSWV.information = INTERFACEENTREESWV_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWV interfaceEntreeSWV;

//Definitions de fonctions publiques:
void interfaceEntreeSWV_initialise(void)
{
  interfaceEntreeSWV.etatDuModule = INTERFACEENTREESWV_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWV.information = INTERFACEENTREESWV_INFORMATION_TRAITEE;
  interfaceEntreeSWV.etatDeLEntree = INTERFACEENTREESWV_PAS_EN_FONCTION;
  interfaceEntreeSWV_compteurAvantLecture = 0;
  interfaceEntreeSWV_compteurAntiRebond = INTERFACEENTREESWV_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWV_PHASE] = interfaceEntreeSWV_gere;
}
