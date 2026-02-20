//Historique: 
// 2025-11-30, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWH.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWH.h"


//Definitions privees
#define INTERFACEENTREESWH_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWH_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWH_COMPTE_INITIAL (\
  INTERFACEENTREESWH_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWH_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWH_compteurAvantLecture;
unsigned int interfaceEntreeSWH_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWH_gere(void)
{
  interfaceEntreeSWH_compteurAvantLecture++;
  if (interfaceEntreeSWH_compteurAvantLecture < INTERFACEENTREESWH_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWH_compteurAvantLecture = 0;
  if (piloteEntreeSWH_lit() == INTERFACEENTREESWH_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWH_compteurAntiRebond == INTERFACEENTREESWH_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWH_compteurAntiRebond++;
    if (interfaceEntreeSWH_compteurAntiRebond < INTERFACEENTREESWH_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWH.etatDeLEntree == INTERFACEENTREESWH_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWH.etatDuModule = INTERFACEENTREESWH_MODULE_EN_FONCTION;
    interfaceEntreeSWH.etatDeLEntree = INTERFACEENTREESWH_ACTIVE;
    interfaceEntreeSWH.information = INTERFACEENTREESWH_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWH_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWH_compteurAntiRebond--;
  if (interfaceEntreeSWH_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWH.etatDeLEntree == INTERFACEENTREESWH_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWH.etatDuModule = INTERFACEENTREESWH_MODULE_EN_FONCTION;  
  interfaceEntreeSWH.etatDeLEntree = INTERFACEENTREESWH_INACTIVE;
  interfaceEntreeSWH.information = INTERFACEENTREESWH_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWH interfaceEntreeSWH;

//Definitions de fonctions publiques:
void interfaceEntreeSWH_initialise(void)
{
  interfaceEntreeSWH.etatDuModule = INTERFACEENTREESWH_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWH.information = INTERFACEENTREESWH_INFORMATION_TRAITEE;
  interfaceEntreeSWH.etatDeLEntree = INTERFACEENTREESWH_PAS_EN_FONCTION;
  interfaceEntreeSWH_compteurAvantLecture = 0;
  interfaceEntreeSWH_compteurAntiRebond = INTERFACEENTREESWH_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWH_PHASE] = interfaceEntreeSWH_gere;
}
