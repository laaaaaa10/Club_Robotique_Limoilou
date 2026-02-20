//Historique: 
// 2025-11-26, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSWO.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSWO.h"


//Definitions privees
#define INTERFACEENTREESWO_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESWO_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESWO_COMPTE_INITIAL (\
  INTERFACEENTREESWO_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSWO_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSWO_compteurAvantLecture;
unsigned int interfaceEntreeSWO_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSWO_gere(void)
{
  interfaceEntreeSWO_compteurAvantLecture++;
  if (interfaceEntreeSWO_compteurAvantLecture < INTERFACEENTREESWO_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSWO_compteurAvantLecture = 0;
  if (piloteEntreeSWO_lit() == INTERFACEENTREESWO_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSWO_compteurAntiRebond == INTERFACEENTREESWO_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSWO_compteurAntiRebond++;
    if (interfaceEntreeSWO_compteurAntiRebond < INTERFACEENTREESWO_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSWO.etatDeLEntree == INTERFACEENTREESWO_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSWO.etatDuModule = INTERFACEENTREESWO_MODULE_EN_FONCTION;
    interfaceEntreeSWO.etatDeLEntree = INTERFACEENTREESWO_ACTIVE;
    interfaceEntreeSWO.information = INTERFACEENTREESWO_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSWO_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSWO_compteurAntiRebond--;
  if (interfaceEntreeSWO_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSWO.etatDeLEntree == INTERFACEENTREESWO_INACTIVE)
  {
    return;
  }
  interfaceEntreeSWO.etatDuModule = INTERFACEENTREESWO_MODULE_EN_FONCTION;  
  interfaceEntreeSWO.etatDeLEntree = INTERFACEENTREESWO_INACTIVE;
  interfaceEntreeSWO.information = INTERFACEENTREESWO_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESWO interfaceEntreeSWO;

//Definitions de fonctions publiques:
void interfaceEntreeSWO_initialise(void)
{
  interfaceEntreeSWO.etatDuModule = INTERFACEENTREESWO_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSWO.information = INTERFACEENTREESWO_INFORMATION_TRAITEE;
  interfaceEntreeSWO.etatDeLEntree = INTERFACEENTREESWO_PAS_EN_FONCTION;
  interfaceEntreeSWO_compteurAvantLecture = 0;
  interfaceEntreeSWO_compteurAntiRebond = INTERFACEENTREESWO_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESWO_PHASE] = interfaceEntreeSWO_gere;
}
