//robotique: programme de depart pour faire operer un CRC Arduino Mega2560 en mode cooperatif
//Historique:
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xpiloteEntreeSW1.h"
#include "xpiloteEntreeSWF.h"
#include "xpiloteEntreeSWO.h"
#include "xpiloteEntreeSWB.h"
#include "xpiloteEntreeSWH.h"
#include "xpiloteEntreeSWS.h"
#include "xpiloteEntreeSWV.h"
#include "xpiloteEntreeSWI.h"
#include "xpiloteSortieDEL.h"
#include "xpiloteSortieT1.h"
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntreeSW1.h"
#include "xinterfaceEntreeSWF.h"
#include "xinterfaceEntreeSWO.h"
#include "xinterfaceEntreeSWB.h"
#include "xinterfaceEntreeSWH.h"
#include "xinterfaceEntreeSWS.h"
#include "xinterfaceEntreeSWV.h"
#include "xinterfaceEntreeSWI.h"
#include "xinterfaceSortieDEL.h"
#include "xinterfaceSortieT1.h"
#include "xinterfaceVEXPince.h"
#include "xinterfaceVEXBras.h"
#include "xinterfaceVEXElevateur.h"
#include "xinterfaceVEXGauche.h"
#include "xinterfaceVEXDroit.h"
#include "xinterfaceCRCConnect.h"
#include "xserviceManette.h"
#include "xprocessusClignotant.h"
#include "xprocessusTemoin.h"
#include "xprocessusPince.h"
#include "xprocessusBras.h"
#include "xprocessusElevateur.h"
#include "xprocessusMotorisation.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void main_initialise(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void main_initialise(void)
{
  piloteEntreeSW1_initialise();
  piloteEntreeSWF_initialise();
  piloteEntreeSWO_initialise(); 
  piloteEntreeSWB_initialise();
  piloteEntreeSWH_initialise(); 
  piloteEntreeSWS_initialise(); 
  piloteEntreeSWV_initialise();
  piloteEntreeSWI_initialise(); 
  piloteSortieDEL_initialise();
  piloteSortieT1_initialise();
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  interfaceEntreeSW1_initialise();
  interfaceEntreeSWF_initialise();
  interfaceEntreeSWO_initialise();
  interfaceEntreeSWB_initialise();
  interfaceEntreeSWH_initialise();
  interfaceEntreeSWS_initialise();
  interfaceEntreeSWV_initialise();
  interfaceEntreeSWI_initialise();  
  interfaceSortieDEL_initialise();
  interfaceSortieT1_initialise();
  interfaceVEXPince_initialise();
  interfaceVEXBras_initialise();
  interfaceVEXElevateur_initialise();
  interfaceVEXGauche_initialise();
  interfaceVEXDroit_initialise();
  interfaceCRCConnect_initialise();
  serviceManette_initialise();
  processusClignotant_initialise();
  processusTemoin_initialise();
  processusPince_initialise();
  processusBras_initialise();
  processusElevateur_initialise();
  processusMotorisation_initialise();
}

void setup(void) 
{
  CrcLib::Initialize();  
  Serial.begin(115200);
  main_initialise();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  CrcLib::Update();   
  serviceBaseDeTemps_gereDansLoop();     
  serviceTaskServer_gestion.execute();
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques
