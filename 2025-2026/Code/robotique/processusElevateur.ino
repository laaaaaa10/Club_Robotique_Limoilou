//processusElevateur:
//Historique: 
// 2025-11-30, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceEntreeSWB.h"
#include "xinterfaceEntreeSWH.h"
#include "xinterfaceVEXElevateur.h"
#include "xserviceBaseDeTemps.h"
#include "xserviceManette.h"
#include "xprocessusElevateur.h"

//Definitions privees
#define PROCESSUSELEVATEUR_COMPTE_MAXIMUM_DE_DEPART (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSELEVATEUR_TEMPS_DE_DEPART_EN_SECONDES)
#define PROCESSUSELEVATEUR_COMPTE_MAXIMUM_POUR_DESCENDRE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSELEVATEUR_TEMPS_MAXIMUM_POUR_DESCENDRE_EN_SECONDES)
#define PROCESSUSELEVATEUR_COMPTE_MAXIMUM_POUR_MONTER (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSELEVATEUR_TEMPS_MAXIMUM_POUR_MONTER_EN_SECONDES)
#define PROCESSUSELEVATEUR_COMPTE_POUR_REMONTER (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSELEVATEUR_TEMPS_POUR_REMONTER_EN_MS /1000)
   
 
//Declarations de fonctions privees:
char processusElevateur_detecteUneErreurDInterrupteurs(void);
void processusElevateur_attendQueLesLecturesDeSWBSoientValides(void);
void processusElevateur_attendQueLesLecturesDeSWHSoientValides(void);
void processusElevateur_attendUnPeu(void);
void processusElevateur_attendDEtreEnHaut(void);
void processusElevateur_gereLesCommandes(void);
void processusElevateur_gereEnModeManuel(void);

//Definitions de variables privees:
unsigned int processusElevateur_compteur;

//Definitions de fonctions privees:
char processusElevateur_detecteUneErreurDInterrupteurs(void)
{
  if (interfaceEntreeSWB.etatDeLEntree == INTERFACEENTREESWB_ACTIVE)  
  {
    if (interfaceEntreeSWH.etatDeLEntree = INTERFACEENTREESWH_ACTIVE)
    {
      processusElevateur.statut |= PROCESSUSELEVATEUR_ERREUR_D_INTERRUPTEURS;      
      return PROCESSUSELEVATEUR_ERREUR_D_INTERRUPTEURS;
    }
  }
  return PROCESSUSELEVATEUR_PAS_D_ERREUR;
}

void processusElevateur_attendQueLesLecturesDeSWBSoientValides(void)
{
  if (interfaceEntreeSWB.etatDuModule != INTERFACEENTREESWB_MODULE_EN_FONCTION)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_attendQueLesLecturesDeSWHSoientValides;
}

void processusElevateur_attendQueLesLecturesDeSWHSoientValides(void)
{
  if (interfaceEntreeSWH.etatDuModule != INTERFACEENTREESWH_MODULE_EN_FONCTION)
  {
    return;
  }
  processusElevateur_compteur = 0;
  processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_EN_FONCTION;
  serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_attendUnPeu;
}

void processusElevateur_attendUnPeu(void)
{
  processusElevateur_compteur++;
  if (processusElevateur_compteur < PROCESSUSELEVATEUR_COMPTE_MAXIMUM_DE_DEPART)
  {
    return;
  }
  if (processusElevateur_detecteUneErreurDInterrupteurs() == PROCESSUSELEVATEUR_ERREUR_D_INTERRUPTEURS)
  {
    serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWH.etatDeLEntree == INTERFACEENTREESWH_INACTIVE)
  {
    processusElevateur_compteur = 0;
    interfaceVEXElevateur_metA(PROCESSUSELEVATEUR_VALEUR_POUR_MONTER);
    serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_attendDEtreEnHaut;
    return;    
  }
  serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_gereLesCommandes;
}

void processusElevateur_attendDEtreEnHaut(void)
{
  if (processusElevateur_detecteUneErreurDInterrupteurs() == PROCESSUSELEVATEUR_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXElevateur_metALArret();
    serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_gereEnModeManuel;
    return;
  }  
  processusElevateur_compteur++;
  if (processusElevateur_compteur > PROCESSUSELEVATEUR_COMPTE_MAXIMUM_POUR_MONTER)
  {
    interfaceVEXElevateur_metALArret();
    processusElevateur.statut |= PROCESSUSELEVATEUR_ERREUR_DE_MONTEE;
    serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWH.etatDeLEntree == INTERFACEENTREESWH_ACTIVE)
  {
    serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_gereLesCommandes;
  }
}

void processusElevateur_gereLesCommandes(void)
{
char boutonMonter;
char boutonDescendre;  
  if (serviceManette.etatDuModule != SERVICEMANETTE_MODULE_EN_FONCTION)
  {
    interfaceVEXElevateur_metALArret();
    processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_EN_FONCTION;  
  boutonMonter = serviceManette.valeurLue[PROCESSUSELEVATEUR_BOUTON_MONTER];
  boutonDescendre = serviceManette.valeurLue[PROCESSUSELEVATEUR_BOUTON_DESCENDRE];
  if (boutonMonter == boutonDescendre)
  {
    interfaceVEXElevateur_metALArret();
    return;
  }
  if (boutonMonter == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    if (interfaceEntreeSWH.etatDeLEntree == INTERFACEENTREESWH_ACTIVE)
    {
      interfaceVEXElevateur_metALArret();
      return;
    }
    interfaceVEXElevateur_metA(PROCESSUSELEVATEUR_VALEUR_POUR_MONTER);
    return;
  }
  if (interfaceEntreeSWB.etatDeLEntree == INTERFACEENTREESWB_ACTIVE)
  {    
    interfaceVEXElevateur_metALArret();
    return;
  }
  interfaceVEXElevateur_metA(PROCESSUSELEVATEUR_VALEUR_POUR_DESCENDRE);
}

void processusElevateur_gereEnModeManuel(void)
{
char boutonMonter;
char boutonDescendre;  
  if (serviceManette.etatDuModule != SERVICEMANETTE_MODULE_EN_FONCTION)
  {
    interfaceVEXElevateur_metALArret();
    processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_EN_FONCTION;  
  boutonMonter = serviceManette.valeurLue[PROCESSUSELEVATEUR_BOUTON_MONTER];
  boutonDescendre = serviceManette.valeurLue[PROCESSUSELEVATEUR_BOUTON_DESCENDRE];
  if (boutonMonter == boutonDescendre)
  {
    interfaceVEXElevateur_metALArret();
    return;
  }
  if (boutonMonter == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    interfaceVEXElevateur_metA(PROCESSUSELEVATEUR_VALEUR_POUR_MONTER);
    return;
  }
  interfaceVEXElevateur_metA(PROCESSUSELEVATEUR_VALEUR_POUR_DESCENDRE);
}

//Definitions de variables publiques:
PROCESSUSELEVATEUR processusElevateur;

//Definitions de fonctions publiques:
void processusElevateur_initialise(void)
{
  processusElevateur.statut = PROCESSUSELEVATEUR_PAS_D_ERREUR;
  processusElevateur.etatDuModule = PROCESSUSELEVATEUR_MODULE_PAS_EN_FONCTION;  
  interfaceVEXElevateur_metALArret();
  serviceBaseDeTemps_execute[PROCESSUSELEVATEUR_PHASE] = processusElevateur_attendQueLesLecturesDeSWBSoientValides;
}
