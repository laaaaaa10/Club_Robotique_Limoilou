//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntreeSW1.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSW1.h"


//Definitions privees
#define INTERFACEENTREESW1_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREESW1_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREESW1_COMPTE_INITIAL (\
  INTERFACEENTREESW1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntreeSW1_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntreeSW1_compteurAvantLecture;
unsigned int interfaceEntreeSW1_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntreeSW1_gere(void)
{
  interfaceEntreeSW1_compteurAvantLecture++;
  if (interfaceEntreeSW1_compteurAvantLecture < INTERFACEENTREESW1_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntreeSW1_compteurAvantLecture = 0;
  if (piloteEntreeSW1_lit() == INTERFACEENTREESW1_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntreeSW1_compteurAntiRebond == INTERFACEENTREESW1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntreeSW1_compteurAntiRebond++;
    if (interfaceEntreeSW1_compteurAntiRebond < INTERFACEENTREESW1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntreeSW1.etatDeLEntree == INTERFACEENTREESW1_ACTIVE)
    {
      return;    
    }
    interfaceEntreeSW1.etatDuModule = INTERFACEENTREESW1_MODULE_EN_FONCTION;
    interfaceEntreeSW1.etatDeLEntree = INTERFACEENTREESW1_ACTIVE;
    interfaceEntreeSW1.information = INTERFACEENTREESW1_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntreeSW1_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntreeSW1_compteurAntiRebond--;
  if (interfaceEntreeSW1_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntreeSW1.etatDeLEntree == INTERFACEENTREESW1_INACTIVE)
  {
    return;
  }
  interfaceEntreeSW1.etatDuModule = INTERFACEENTREESW1_MODULE_EN_FONCTION;  
  interfaceEntreeSW1.etatDeLEntree = INTERFACEENTREESW1_INACTIVE;
  interfaceEntreeSW1.information = INTERFACEENTREESW1_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREESW1 interfaceEntreeSW1;

//Definitions de fonctions publiques:
void interfaceEntreeSW1_initialise(void)
{
  interfaceEntreeSW1.etatDuModule = INTERFACEENTREESW1_MODULE_PAS_EN_FONCTION;
  interfaceEntreeSW1.information = INTERFACEENTREESW1_INFORMATION_TRAITEE;
  interfaceEntreeSW1.etatDeLEntree = INTERFACEENTREESW1_PAS_EN_FONCTION;
	interfaceEntreeSW1_compteurAvantLecture = 0;
  interfaceEntreeSW1_compteurAntiRebond = INTERFACEENTREESW1_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREESW1_PHASE] = interfaceEntreeSW1_gere;
}
