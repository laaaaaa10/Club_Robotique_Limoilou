//processusPince:
//Historique: 
// 2025-11-28, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceEntreeSWF.h"
#include "xinterfaceEntreeSWO.h"
#include "xinterfaceVEXPince.h"
#include "xserviceBaseDeTemps.h"
#include "xserviceManette.h"
#include "xprocessusPince.h"

//Definitions privees
#define PROCESSUSPINCE_COMPTE_MAXIMUM_DE_DEPART (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSPINCE_TEMPS_DE_DEPART_EN_SECONDES)
#define PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_FERMER (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSPINCE_TEMPS_MAXIMUM_POUR_FERMER_EN_SECONDES)
#define PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_OUVRIR (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSPINCE_TEMPS_MAXIMUM_POUR_OUVRIR_EN_SECONDES)
#define PROCESSUSPINCE_COMPTE_POUR_ENTROUVRIR (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSPINCE_TEMPS_POUR_ENTROUVRIR_EN_MS /1000)
 
//Declarations de fonctions privees:
char processusPince_detecteUneErreurDInterrupteurs(void);
void processusPince_attendQueLesLecturesDeSWOSoientValides(void);
void processusPince_attendQueLesLecturesDeSWFSoientValides(void);
void processusPince_attendUnPeu(void);
void processusPince_attendLaFermetureInitiale(void);
void processusPince_attendLOuvertureComplete(void);
void processusPince_attendLaFermetureComplete(void);
void processusPince_attendDEtreFerme(void);
void processusPince_attendDEtreEntrouvert(void);
void processusPince_gereLesCommandes(void);
void processusPince_gereEnModeManuel(void);

//Definitions de variables privees:
unsigned int processusPince_compteur;

//Definitions de fonctions privees:
char processusPince_detecteUneErreurDInterrupteurs(void)
{
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)  
  {
    if (interfaceEntreeSWO.etatDeLEntree = INTERFACEENTREESWO_ACTIVE)
    {
      processusPince.statut |= PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS;      
      return PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS;
    }
  }
  return PROCESSUSPINCE_PAS_D_ERREUR;
}

void processusPince_attendQueLesLecturesDeSWOSoientValides(void)
{
  if (interfaceEntreeSWO.etatDuModule != INTERFACEENTREESWO_MODULE_EN_FONCTION)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendQueLesLecturesDeSWFSoientValides;
}

void processusPince_attendQueLesLecturesDeSWFSoientValides(void)
{
  if (interfaceEntreeSWF.etatDuModule != INTERFACEENTREESWF_MODULE_EN_FONCTION)
  {
    return;
  }
  processusPince_compteur = 0;
  processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_FONCTION;
  serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendUnPeu;
}

void processusPince_attendUnPeu(void)
{
  processusPince_compteur++;
  if (processusPince_compteur < PROCESSUSPINCE_COMPTE_MAXIMUM_DE_DEPART)
  {
    return;
  }
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  processusPince_compteur = 0;
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
  {
    interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_OUVRIR);
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLOuvertureComplete;
    return;    
  }
  interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
  serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLaFermetureInitiale;
}

void processusPince_attendLaFermetureInitiale(void)
{
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXPince_metALArret();
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }  
  processusPince_compteur++;
  if (processusPince_compteur > PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_FERMER)
  {
    interfaceVEXPince_metALArret();
    processusPince.statut |= PROCESSUSPINCE_ERREUR_DE_FERMETURE;
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
  {
    interfaceVEXPince_metALArret();
    processusPince_compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLOuvertureComplete;      
  }
}

void processusPince_attendLOuvertureComplete(void)
{
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }  
  processusPince_compteur++;
  if (processusPince_compteur > PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_OUVRIR)
  {
    interfaceVEXPince_metALArret();
    processusPince.statut |= PROCESSUSPINCE_ERREUR_D_OUVERTURE;
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;    
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWO.etatDeLEntree == INTERFACEENTREESWO_ACTIVE)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereLesCommandes;  
  }
}

void processusPince_attendLaFermetureComplete(void)
{
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
        processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }  
  processusPince_compteur++;
  if (processusPince_compteur > PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_FERMER)
  {
    interfaceVEXPince_metALArret();
    processusPince.statut |= PROCESSUSPINCE_ERREUR_DE_FERMETURE;
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;    
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereLesCommandes;  
  }  
}

void processusPince_attendDEtreFerme(void)
{
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  processusPince_compteur++;
  if (processusPince_compteur > PROCESSUSPINCE_COMPTE_MAXIMUM_POUR_FERMER)
  {
    interfaceVEXPince_metALArret();
    processusPince.statut |= PROCESSUSPINCE_ERREUR_DE_FERMETURE;
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
  {
    processusPince_compteur = 0;
    interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_ENTROUVRIR);
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendDEtreEntrouvert;  
  }
}

void processusPince_attendDEtreEntrouvert(void)
{
  processusPince_compteur++;
  if (processusPince_compteur > PROCESSUSPINCE_COMPTE_POUR_ENTROUVRIR)
  {
    interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLaFermetureComplete;
    return;
  }
}

void processusPince_gereLesCommandes(void)
{
char boutonOuverture;
char boutonFermeture;  
  if (serviceManette.etatDuModule != SERVICEMANETTE_MODULE_EN_FONCTION)
  {
    interfaceVEXPince_metALArret();
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_FONCTION;  
  if (processusPince_detecteUneErreurDInterrupteurs() == PROCESSUSPINCE_ERREUR_D_INTERRUPTEURS)
  {
    interfaceVEXPince_metALArret();
    processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;    
    serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_gereEnModeManuel;
    return;
  }
  if (processusPince.requete == PROCESSUSPINCE_REQUETE_ACTIVE)
  {
    processusPince_compteur = 0;
    if (processusPince.commande == PROCESSUSPINCE_COMMANDE_OUVRIR)
    {
      if (interfaceEntreeSWO.etatDeLEntree == INTERFACEENTREESWO_ACTIVE)
      {
        processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
        return;
      }
      interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_OUVRIR);
      serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLOuvertureComplete;
      return;
    }
    if (processusPince.commande == PROCESSUSPINCE_COMMANDE_FERMER)
    {
      if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
      {
        processusPince.requete = PROCESSUSPINCE_REQUETE_TRAITEE;
        return;
      }
      interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
      serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendLaFermetureComplete;
      return;
    }
    if (processusPince.commande == PROCESSUSPINCE_COMMANDE_ENTROUVRIR)
    {
      if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_ACTIVE)
      {
        interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_ENTROUVRIR);
        serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendDEtreEntrouvert;
        return;
      }
      interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
      serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendDEtreFerme;
      return;
    }
  }
  boutonFermeture = serviceManette.valeurLue[PROCESSUSPINCE_BOUTON_FERMER];
  boutonOuverture = serviceManette.valeurLue[PROCESSUSPINCE_BOUTON_OUVRIR];
  if (boutonFermeture == boutonOuverture)
  {
    interfaceVEXPince_metALArret();
    return;
  }
  if (boutonFermeture == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    if (interfaceEntreeSWF.etatDeLEntree == INTERFACEENTREESWF_INACTIVE)
    {
      interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
    }
    return;
  }
  if (interfaceEntreeSWO.etatDeLEntree == INTERFACEENTREESWO_INACTIVE)
  {    
    interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_OUVRIR);
  }
}

void processusPince_gereEnModeManuel(void)
{
char boutonOuverture;
char boutonFermeture;  
  if (serviceManette.etatDuModule != SERVICEMANETTE_MODULE_EN_FONCTION)
  {
    interfaceVEXPince_metALArret();
    processusPince.etatDuModule = PROCESSUSPINCE_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusPince.etatDuModule = PROCESSUSPINCE_MODULE_EN_MODE_MANUEL;
  boutonFermeture = serviceManette.valeurLue[PROCESSUSPINCE_BOUTON_FERMER];
  boutonOuverture = serviceManette.valeurLue[PROCESSUSPINCE_BOUTON_OUVRIR];
  if (boutonFermeture == boutonOuverture)
  {
    interfaceVEXPince_metALArret();
    return;
  }
  if (boutonFermeture == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_FERMER);
    return;
  }
  interfaceVEXPince_metA(PROCESSUSPINCE_VALEUR_POUR_OUVRIR);
}


//Definitions de variables publiques:
PROCESSUSPINCE processusPince;

//Definitions de fonctions publiques:
void processusPince_initialise(void)
{
  processusPince.statut = PROCESSUSPINCE_PAS_D_ERREUR;
  processusPince.etatDuModule = PROCESSUSPINCE_MODULE_PAS_EN_FONCTION;  
  interfaceVEXPince_metALArret();
  serviceBaseDeTemps_execute[PROCESSUSPINCE_PHASE] = processusPince_attendQueLesLecturesDeSWOSoientValides;
}
