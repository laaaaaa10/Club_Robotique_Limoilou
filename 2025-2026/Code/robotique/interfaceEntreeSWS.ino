//Historique: 
// 2025-12-01, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWS.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWS.h"


//Definitions privees
#define INTERFACEENTREESWS_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWS_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWS_COMPTE_INITIAL (\
  INTERFACEENTREESWS_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWS_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWS_compteurAvantLecture;
unsigned int interfaceEntreeSWS_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWS_gere(void)
{
  interfaceEntreeSWS_compteurAvantLecture++;
  if (interfaceEntreeSWS_compteurAvantLecture < INTERFACEENTREESWS_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWS_compteurAvantLecture = 0;
  if (piloteEntreeSWS_lit() == INTERFACEENTREESWS_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWS_compteurAntiRebond == INTERFACEENTREESWS_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWS_compteurAntiRebond++;
    if (interfaceEntreeSWS_compteurAntiRebond < INTERFACEENTREESWS_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWS.etatDeLEntree == INTERFACEENTREESWS_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWS.etatDuModule = INTERFACEENTREESWS_MODULE_EN_FONCTION;
    interfaceEntreeSWS.etatDeLEntree = INTERFACEENTREESWS_ACTIVE;
    interfaceEntreeSWS.information = INTERFACEENTREESWS_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWS_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWS_compteurAntiRebond--;
  if (interfaceEntreeSWS_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWS.etatDeLEntree == INTERFACEENTREESWS_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWS.etatDuModule = INTERFACEENTREESWS_MODULE_EN_FONCTION;  
  interfaceEntreeSWS.etatDeLEntree = INTERFACEENTREESWS_INACTIVE;
  interfaceEntreeSWS.information = INTERFACEENTREESWS_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWS interfaceEntreeSWS;

//Definitions de fonctions publiques:
void interfaceEntreeSWS_initialise(void)
{
  interfaceEntreeSWS.etatDuModule = INTERFACEENTREESWS_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWS.information = INTERFACEENTREESWS_INFORMATION_TRAITEE;
  interfaceEntreeSWS.etatDeLEntree = INTERFACEENTREESWS_PAS_EN_FONCTION;
  interfaceEntreeSWS_compteurAvantLecture = 0;
  interfaceEntreeSWS_compteurAntiRebond = INTERFACEENTREESWS_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWS_PHASE] = interfaceEntreeSWS_gere;
}
