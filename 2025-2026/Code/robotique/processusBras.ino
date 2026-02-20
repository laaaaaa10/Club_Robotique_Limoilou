//processusBras:
//Historique: 
// 2025-12-02, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceEntreeSWS.h"
#include "xinterfaceEntreeSWV.h"
#include "xinterfaceEntreeSWI.h"
#include "xinterfaceVEXBras.h"
#include "xserviceBaseDeTemps.h"
#include "xserviceManette.h"
#include "xprocessusPince.h"
#include "xprocessusBras.h"

//Definitions privees
#define PROCESSUSBRAS_COMPTE_MAXIMUM_DE_DEPART (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_DE_DEPART_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_INFERIEURE_VERS_SUPERIEURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_INFERIEURE_VERS_SUPERIEURE_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_INFERIEURE_VERS_VERTICALE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_INFERIEURE_VERS_VERTICALE_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_VERTICALE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_SUPERIEURE_VERS_VERTICALE_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_INFERIEURE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_SUPERIEURE_VERS_INFERIEURE_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_SUPERIEURE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_VERTICALE_VERS_SUPERIEURE_EN_SECONDES)
#define PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_INFERIEURE (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ*PROCESSUSBRAS_TEMPS_MAXIMUM_POUR_VERTICALE_VERS_INFERIEURE_EN_SECONDES)
 
//Declarations de fonctions privees:
char processusBras_detecteUneErreurDInterrupteurs(void);
char processusBras_detecteUneErreurDeRotation(unsigned int CompteMaximum);
void processusBras_gere(void);
void processusBras_attendQueLesLecturesDeSWSSoientValides(void);
void processusBras_attendQueLesLecturesDeSWVSoientValides(void);
void processusBras_attendQueLesLecturesDeSWISoientValides(void);
void processusBras_attendQueLaPinceSoientEnFonction(void);
void processusBras_attendUnPeu(void);
void processusBras_attendLaPositionVerticaleInitiale(void);
void processusBras_attendLaPositionSuperieureInitiale(void);
void processusBras_attendLaPositionInferieureInitiale(void);
void processusBras_gereLaPositionInferieure(void);
void processusBras_gereLaPositionSuperieure(void);
void processusBras_gereLaPositionVerticale(void);
void processusBras_attendLaPositionInferieure(void);
void processusBras_attendLaPositionSuperieure(void);
void processusBras_attendLaPositionVerticale(void);
void processusBras_attendLaPositionInferieurePourInversion(void);
void processusBras_attendQueLaPinceSoitPrete(void);
void processusBras_attendQueLaPinceSoitEntrouverte(void);
void processusBras_attendQueLaPinceSoitFermee(void);
void processusBras_gereEnModeManuel(void);

//Definitions de variables privees:
unsigned int processusBras_compteur;
unsigned int processusBras_valeurEnCours;
unsigned int processusBras_compteMaximum;
void (*processusBras_execute)(void);

//Definitions de fonctions privees:
char processusBras_detecteUneErreurDInterrupteurs(void)
{
unsigned char compteur;
  compteur = 0;
  if (interfaceEntreeSWS.etatDeLEntree == INTERFACEENTREESWS_ACTIVE)  
  {
    compteur++;
  }
  if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_ACTIVE)
  {
    compteur++;
  }
  if (interfaceEntreeSWI.etatDeLEntree = INTERFACEENTREESWI_ACTIVE)
  {
    compteur++;
  }
  if (compteur > 1)
  {
    processusBras.statut |= PROCESSUSBRAS_ERREUR_D_INTERRUPTEURS;
    return PROCESSUSBRAS_ERREUR_D_INTERRUPTEURS;
  }
  return PROCESSUSBRAS_PAS_D_ERREUR;
}

char processusBras_detecteUneErreurDeRotation(unsigned int CompteMaximum)
{
  processusBras_compteur++;
  if (processusBras_compteur > CompteMaximum)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras.statut |= PROCESSUSBRAS_ERREUR_DE_ROTATION;
    processusBras.etatDuModule = PROCESSUSBRAS_MODULE_EN_MODE_MANUEL;
    processusBras_execute = processusBras_gereEnModeManuel;
    return PROCESSUSBRAS_ERREUR_DE_ROTATION;
  }
  return PROCESSUSBRAS_PAS_D_ERREUR;
}

void processusBras_gere(void)
{
  if (processusBras_detecteUneErreurDInterrupteurs() == PROCESSUSBRAS_ERREUR_D_INTERRUPTEURS)
  {
    processusBras.etatDuModule = PROCESSUSBRAS_MODULE_EN_MODE_MANUEL;
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras_execute = processusBras_gereEnModeManuel;
  }
  if (serviceManette.etatDuModule == SERVICEMANETTE_MODULE_PAS_EN_FONCTION)
  {
    interfaceVEXBras_metALArret();
    return;
  }
  interfaceVEXBras_metA(processusBras_valeurEnCours);
  processusBras_execute();
}

void processusBras_attendQueLesLecturesDeSWSSoientValides(void)
{
  if (interfaceEntreeSWS.etatDuModule != INTERFACEENTREESWS_MODULE_EN_FONCTION)
  {
    return;
  }
  processusBras_execute = processusBras_attendQueLesLecturesDeSWVSoientValides;
}

void processusBras_attendQueLesLecturesDeSWVSoientValides(void)
{
  if (interfaceEntreeSWV.etatDuModule != INTERFACEENTREESWV_MODULE_EN_FONCTION)
  {
    return;
  }
  processusBras_execute = processusBras_attendQueLesLecturesDeSWISoientValides;
}

void processusBras_attendQueLesLecturesDeSWISoientValides(void)
{
  if (interfaceEntreeSWI.etatDuModule != INTERFACEENTREESWI_MODULE_EN_FONCTION)
  {
    return;
  }
  processusBras_execute = processusBras_attendQueLaPinceSoientEnFonction;
}

void processusBras_attendQueLaPinceSoientEnFonction(void)
{
  if (processusPince.etatDuModule != PROCESSUSPINCE_MODULE_EN_FONCTION)
  {
    return;
  }
  processusBras_compteur = 0;
  processusBras.etatDuModule = PROCESSUSBRAS_MODULE_EN_FONCTION;
  processusBras_execute = processusBras_attendUnPeu;
}

void processusBras_attendUnPeu(void)
{
  processusBras_compteur++;
  if (processusBras_compteur < PROCESSUSBRAS_COMPTE_MAXIMUM_DE_DEPART)
  {
    return;
  }
  processusBras_compteur = 0;
  if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_ACTIVE)
  {
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE);
    processusBras_execute = processusBras_attendLaPositionSuperieureInitiale;
    return;
  }
  processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_VERTICALE;
  interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_VERTICALE);
  processusBras_execute = processusBras_attendLaPositionVerticaleInitiale;
}

void processusBras_attendLaPositionVerticaleInitiale(void)
{
  if (processusBras_detecteUneErreurDeRotation(PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_INFERIEURE_VERS_VERTICALE) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_ACTIVE)
  {
    processusBras_compteur = 0;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE);
    processusBras_execute = processusBras_attendLaPositionSuperieureInitiale;
  }
}

void processusBras_attendLaPositionSuperieureInitiale(void)
{
  if (processusBras_detecteUneErreurDeRotation(PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_SUPERIEURE) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWS.etatDeLEntree == INTERFACEENTREESWS_ACTIVE)
  {
    processusBras_compteur = 0;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE);
    processusBras_execute = processusBras_attendLaPositionInferieureInitiale;
  }
}

void processusBras_attendLaPositionInferieureInitiale(void)
{
  if (processusBras_detecteUneErreurDeRotation(PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_INFERIEURE) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWI.etatDeLEntree == INTERFACEENTREESWI_ACTIVE)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras.etatDuModule = PROCESSUSBRAS_MODULE_EN_FONCTION;
    processusBras_execute = processusBras_gereLaPositionInferieure;
  }
}

void processusBras_gereLaPositionInferieure(void)
{
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_VERTICALE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_INFERIEURE_VERS_VERTICALE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_VERTICALE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_VERTICALE);
    processusBras_execute = processusBras_attendLaPositionVerticale;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_SUPERIEURE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_INFERIEURE_VERS_SUPERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_SUPERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_SUPERIEURE);
    processusBras_execute = processusBras_attendLaPositionSuperieure;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INVERSEE])
  {
    processusBras_execute = processusBras_attendQueLaPinceSoitPrete;
  }
}

void processusBras_gereLaPositionSuperieure(void)
{
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_VERTICALE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_VERTICALE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_VERTICALE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_VERTICALE);
    processusBras_execute = processusBras_attendLaPositionVerticale;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INFERIEURE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_INFERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE);
    processusBras_execute = processusBras_attendLaPositionInferieure;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INVERSEE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_SUPERIEURE_VERS_INFERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE);
    processusBras_execute = processusBras_attendLaPositionInferieurePourInversion;
  }
}

void processusBras_gereLaPositionVerticale(void)
{
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_SUPERIEURE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_SUPERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_SUPERIEURE);    
    processusBras_execute = processusBras_attendLaPositionSuperieure;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INFERIEURE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_INFERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_INFERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_INFERIEURE);
    processusBras_execute = processusBras_attendLaPositionInferieure;
    return;
  }
  if (serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INVERSEE])
  {
    processusBras_compteur = 0;
    processusBras_compteMaximum = PROCESSUSBRAS_COMPTE_MAXIMUM_POUR_VERTICALE_VERS_INFERIEURE;
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_INFERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_VERTICALE_VERS_INFERIEURE);
    processusBras_execute = processusBras_attendLaPositionInferieurePourInversion;
  }
}

void processusBras_attendLaPositionInferieure(void)
{
  if (processusBras_detecteUneErreurDeRotation(processusBras_compteMaximum) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWI.etatDeLEntree == INTERFACEENTREESWI_ACTIVE)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras_execute = processusBras_gereLaPositionInferieure;
  }
}

void processusBras_attendLaPositionSuperieure(void)
{
  if (processusBras_detecteUneErreurDeRotation(processusBras_compteMaximum) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWS.etatDeLEntree == INTERFACEENTREESWS_ACTIVE)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras_execute = processusBras_gereLaPositionSuperieure;
  }
}

void processusBras_attendLaPositionVerticale(void)
{
  if (processusBras_detecteUneErreurDeRotation(processusBras_compteMaximum) == PROCESSUSBRAS_ERREUR_DE_ROTATION)
  {
    return;
  }
  if (interfaceEntreeSWV.etatDeLEntree == INTERFACEENTREESWV_ACTIVE)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    processusBras_execute = processusBras_gereLaPositionVerticale;
  }
}

void processusBras_attendLaPositionInferieurePourInversion(void)
{
  if (interfaceEntreeSWI.etatDeLEntree == INTERFACEENTREESWI_ACTIVE)
  {
    processusBras_execute = processusBras_attendQueLaPinceSoitPrete;
    return;
  }
}

void processusBras_attendQueLaPinceSoitPrete(void)
{
  if (processusPince.requete == PROCESSUSPINCE_REQUETE_ACTIVE)
  {
    return;
  }
  processusBras_execute = processusBras_attendQueLaPinceSoitEntrouverte;
}

void processusBras_attendQueLaPinceSoitEntrouverte(void)
{
  if (processusPince.requete == PROCESSUSPINCE_REQUETE_ACTIVE)
  {
    return;
  }
  processusBras_execute = processusBras_attendQueLaPinceSoitFermee;
}

void processusBras_attendQueLaPinceSoitFermee(void)
{
  if (processusPince.requete == PROCESSUSPINCE_REQUETE_ACTIVE)
  {
    return;
  }
  processusBras_execute = processusBras_attendLaPositionSuperieure;
}

void processusBras_gereEnModeManuel(void)
{
char boutonInferieureVersSuperieure;
char boutonSuperieureVersInferieure;
  processusBras.etatDuModule = PROCESSUSBRAS_MODULE_EN_MODE_MANUEL;
  boutonInferieureVersSuperieure = serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_SUPERIEURE];
  boutonSuperieureVersInferieure = serviceManette.valeurLue[PROCESSUSBRAS_BOUTON_POSITION_INFERIEURE];
  if (boutonInferieureVersSuperieure == boutonSuperieureVersInferieure)
  {
    processusBras_valeurEnCours = 0;
    interfaceVEXBras_metALArret();
    return;
  }
  if (boutonInferieureVersSuperieure == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_SUPERIEURE;
    interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_INFERIEURE_VERS_SUPERIEURE);
    return;
  }
  processusBras_valeurEnCours = PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE;
  interfaceVEXBras_metA(PROCESSUSBRAS_VALEUR_POUR_SUPERIEURE_VERS_INFERIEURE);
}

//Definitions de variables publiques:
PROCESSUSBRAS processusBras;

//Definitions de fonctions publiques:
void processusBras_initialise(void)
{
  processusBras.statut = PROCESSUSBRAS_PAS_D_ERREUR;
  processusBras.etatDuModule = PROCESSUSBRAS_MODULE_PAS_EN_FONCTION;
  processusBras_valeurEnCours = 0;
  interfaceVEXBras_metALArret();
  processusBras_execute = processusBras_attendQueLesLecturesDeSWSSoientValides;
  serviceBaseDeTemps_execute[PROCESSUSBRAS_PHASE] = processusBras_gere;
}
