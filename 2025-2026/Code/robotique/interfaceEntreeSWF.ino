//Historique: 
// 2025-11-26, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWF.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWF.h"


//Definitions privees
#define INTERFACEENTREESWF_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWF_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWF_COMPTE_INITIAL (\
  INTERFACEENTREESWF_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWF_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWF_compteurAvantLecture;
unsigned int interfaceEntreeSWF_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWF_gere(void)
{
  interfaceEntreeSWF_compteurAvantLecture++;
  if (interfaceEntreeSWF_compteurAvantLecture < INTERFACEENTREESWF_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWF_compteurAvantLecture = 0;
  if (piloteEntreeSWF_lit() == INTERFACEENTREESWF_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWF_compteurAntiRebond == INTERFACEENTREESWF_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWF_compteurAntiRebond++;
    if (interfaceEntreeSWF_compteurAntiRebond < INTERFACEENTREESWF_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWF.etatDuModule = INTERFACEENTREESWF_MODULE_EN_FONCTION;
    interfaceEntreeSWF.etatDeLEntree = INTERFACEENTREESWF_ACTIVE;
    interfaceEntreeSWF.information = INTERFACEENTREESWF_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWF_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWF_compteurAntiRebond--;
  if (interfaceEntreeSWF_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWF.etatDuModule = INTERFACEENTREESWF_MODULE_EN_FONCTION;  
  interfaceEntreeSWF.etatDeLEntree = INTERFACEENTREESWF_INACTIVE;
  interfaceEntreeSWF.information = INTERFACEENTREESWF_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWF interfaceEntreeSWF;

//Definitions de fonctions publiques:
void interfaceEntreeSWF_initialise(void)
{
  interfaceEntreeSWF.etatDuModule = INTERFACEENTREESWF_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWF.information = INTERFACEENTREESWF_INFORMATION_TRAITEE;
  interfaceEntreeSWF.etatDeLEntree = INTERFACEENTREESWF_PAS_EN_FONCTION;
  interfaceEntreeSWF_compteurAvantLecture = 0;
  interfaceEntreeSWF_compteurAntiRebond = INTERFACEENTREESWF_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWF_PHASE] = interfaceEntreeSWF_gere;
}
