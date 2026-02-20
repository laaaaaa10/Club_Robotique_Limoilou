//processusTemoin:
//Historique: 
// 2025-11-23, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceSortieT1.h"
#include "xserviceBaseDeTemps.h"
#include "xserviceManette.h"
#include "xprocessusTemoin.h"

//Definitions privees
//pas de definitions privees
   
//Declarations de fonctions privees:
  void processusTemoin_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void processusTemoin_gere(void)
{
  if (serviceManette.etatDuModule != INTERFACEENTREESW1_MODULE_EN_FONCTION)
  {
    interfaceSortieT1_eteint();
    processusTemoin.etatDuModule = PROCESSUSTEMOIN_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusTemoin.etatDuModule = PROCESSUSTEMOIN_MODULE_EN_FONCTION;
  if (serviceManette.valeurLue[PROCESSUSTEMOIN_BOUTON_TEMOIN] == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    interfaceSortieT1_allume();
    return;
  }
  interfaceSortieT1_eteint(); 
}

//Definitions de variables publiques:
PROCESSUSTEMOIN processusTemoin;

//Definitions de fonctions publiques:
void processusTemoin_initialise(void)
{
  processusTemoin.etatDuModule = PROCESSUSTEMOIN_MODULE_PAS_EN_FONCTION;  
  interfaceSortieT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSTEMOIN_PHASE] = processusTemoin_gere;
}
