//Historique: 
// 2025-11-23, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceCRCConnect.h"
#include "xserviceManette.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
void serviceManette_invalideLesValeursLues(void);
void serviceManette_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void serviceManette_invalideLesValeursLues(void)
{
unsigned char indice;
  for (indice = 0; indice < SERVICEMANETTE_NOMBRE_DE_VALEURS; indice++)
  {
    serviceManette.valeurLue[indice] = SERVICEMANETTE_VALEUR_INVALIDE;
  }
}

void serviceManette_gere(void)
{
unsigned char indice;
  if (interfaceCRCConnect.etatDuModule == INTERFACECRCCONNECT_COMMUNICATION_PAS_ETABLIE)
  {
    serviceManette_invalideLesValeursLues();
    serviceManette.etatDuModule = SERVICEMANETTE_MODULE_PAS_EN_FONCTION;
    return;
  }
  if (interfaceCRCConnect.information == INTERFACECRCCONNECT_INFORMATION_TRAITEE)
  {
    return;
  }
  for (indice = 0; indice < INTERFACECRCCONNECT_NOMBRE_DE_VALEURS; indice++)
  {
    serviceManette.valeurLue[indice] = interfaceCRCConnect.valeurLue[indice];
  }
  serviceManette.etatDuModule = SERVICEMANETTE_MODULE_EN_FONCTION;
  interfaceCRCConnect.information = INTERFACECRCCONNECT_INFORMATION_TRAITEE;
}

//Definitions de variables publiques:
SERVICEMANETTE serviceManette;

//Definitions de fonctions publiques:
void serviceManette_initialise(void)
{
  serviceManette_invalideLesValeursLues();
  serviceManette.etatDuModule = SERVICEMANETTE_MODULE_PAS_EN_FONCTION;  
  serviceBaseDeTemps_execute[SERVICEMANETTE_PHASE] = serviceManette_gere;
}
