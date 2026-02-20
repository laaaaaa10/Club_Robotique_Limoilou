//processusMotorisation:
//Historique: 
// 2025-11-24, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceVEXGauche.h"
#include "xinterfaceVEXDroit.h"
#include "xserviceBaseDeTemps.h"
#include "xserviceManette.h"
#include "xprocessusMotorisation.h"

#if PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE >= PROCESSUSMOTORISATION_VALEUR_MAXIMALE
  #error "PROCESSUSMOTORISATION: valeur reduite maximale >= valeur maximale
#endif
#if PROCESSUSMOTORISATION_SEUIL_DE_DETECTION >= PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE
  #error "PROCESSUSMOTORISATION: seuil de detection >= valeur_reduite_maximale
#endif
#if PROCESSUSMOTORISATION_SEUIL_DE_DETECTION < 0
  #error "PROCESSUSMOTORISATION: seuil de detection negatif
#endif 

//Definitions privees
//pas de definitions privees
   
//Declarations de fonctions privees:
char processusMotorisation_trouveLaLimite(void);
char processusMotorisation_pondereLaValeur(char Valeur);
char processusMotorisation_valideLaValeur(char Valeur, char Limite);
void processusMotorisation_gere(void);

//Definitions de variables privees:
char processusMotorisation_X;
char processusMotorisation_Y;
char processusMotorisation_limite;

//Definitions de fonctions privees:
char processusMotorisation_trouveLaLimite(void)
{
  if (serviceManette.valeurLue[PROCESSUSMOTORISATION_BOUTON_JOYSTICK] == SERVICEMANETTE_VALEUR_ACTIVE)
  {
    return PROCESSUSMOTORISATION_VALEUR_REDUITE_MAXIMALE;
  }
  return PROCESSUSMOTORISATION_VALEUR_MAXIMALE;
}

char processusMotorisation_pondereLaValeur(char Valeur)
{ //pour implementer y=sgn(x)*(2abs(x)−(x^2)/128​)pour x∈[−128,127] qui monte la sensibilite aux petits deplacements du joystick
unsigned int outil;
unsigned int absValeur;
  absValeur = (unsigned int)abs(Valeur);
  outil = (absValeur *(256 - absValeur))/128;
  if (Valeur < 0)
  {
    return (char)(-outil);
  }
  return (char)outil;
}

char processusMotorisation_valideLaValeur(char Valeur, char Limite)
{
  if (Valeur >= Limite)
  {
    return Limite;
  }
  if (Valeur > PROCESSUSMOTORISATION_SEUIL_DE_DETECTION)
  {
    return Valeur;
  }
  if (Valeur >= -PROCESSUSMOTORISATION_SEUIL_DE_DETECTION)
  {
    return 0;
  }
  if (Valeur >= -Limite)
  {
    return Valeur; 
  }
  return -Limite;
}
  
void processusMotorisation_gere(void)
{
  if (serviceManette.etatDuModule != SERVICEMANETTE_MODULE_EN_FONCTION)
  {
    interfaceVEXGauche_metALArret();
    interfaceVEXDroit_metALArret();
    processusMotorisation.etatDuModule = PROCESSUSMOTORISATION_MODULE_PAS_EN_FONCTION;
    return;
  }
  processusMotorisation.etatDuModule = PROCESSUSMOTORISATION_MODULE_EN_FONCTION;
  processusMotorisation_limite = processusMotorisation_trouveLaLimite();
  processusMotorisation_Y = serviceManette.valeurLue[PROCESSUSMOTORISATION_JOYSTICK_Y];
  processusMotorisation_Y = processusMotorisation_pondereLaValeur(processusMotorisation_Y);
  processusMotorisation_Y = processusMotorisation_valideLaValeur(processusMotorisation_Y, processusMotorisation_limite);
  processusMotorisation_X = serviceManette.valeurLue[PROCESSUSMOTORISATION_JOYSTICK_X];  
  processusMotorisation_X = processusMotorisation_pondereLaValeur(processusMotorisation_X);
  processusMotorisation_X = processusMotorisation_valideLaValeur(processusMotorisation_X, processusMotorisation_limite - abs(processusMotorisation_Y));
  interfaceVEXGauche_metA(processusMotorisation_Y - processusMotorisation_X);
  interfaceVEXDroit_metA(processusMotorisation_Y + processusMotorisation_X);
}

//Definitions de variables publiques:
PROCESSUSMOTORISATION processusMotorisation;

//Definitions de fonctions publiques:
void processusMotorisation_initialise(void)
{
  processusMotorisation.etatDuModule = PROCESSUSMOTORISATION_MODULE_PAS_EN_FONCTION;  
  interfaceVEXGauche_metALArret();
  interfaceVEXDroit_metALArret();  
  serviceBaseDeTemps_execute[PROCESSUSMOTORISATION_PHASE] = processusMotorisation_gere;
}
