//Historique: 
// 2025-11-19, Yves Roy, creation

//INCLUSIONS
#include "CrcLib.h"
#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceCRCConnect.h"


//Definitions privees
#define INTERFACECRCCONNECT_COMMUNICATION_PAS_ETABLIE 0

//Declarations de fonctions privees:
void interfaceCRCConnect_invalideLesValeursLues(void);
void interfaceCRCConnect_gereDansLoop(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void interfaceCRCConnect_invalideLesValeursLues(void)
{
unsigned char indice;
  for (indice = 0; indice < INTERFACECRCCONNECT_NOMBRE_DE_VALEURS; indice++)
  {
    interfaceCRCConnect.valeurLue[indice] = INTERFACECRCCONNECT_VALEUR_INVALIDE;
  }
}

void interfaceCRCConnect_gereDansLoop(void)
{
  if (interfaceCRCConnect.information == INTERFACECRCCONNECT_INFORMATION_DISPONIBLE)
  {
    return;
  }
  if (CrcLib::IsCommValid() == INTERFACECRCCONNECT_COMMUNICATION_PAS_ETABLIE)
  {
    interfaceCRCConnect_invalideLesValeursLues();
    interfaceCRCConnect.etatDuModule = INTERFACECRCCONNECT_MODULE_PAS_EN_FONCTION;
    interfaceCRCConnect.information = INTERFACECRCCONNECT_INFORMATION_TRAITEE;
    return;
  }
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_BACK] = CrcLib::ReadDigitalChannel(BUTTON::SELECT);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_START] = CrcLib::ReadDigitalChannel(BUTTON::START);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_GAUCHE] = CrcLib::ReadDigitalChannel(BUTTON::L1);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_DROIT] = CrcLib::ReadDigitalChannel(BUTTON::R1);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_JOYSTICK_GAUCHE] = CrcLib::ReadDigitalChannel(BUTTON::HATL);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_JOYSTICK_DROIT] = CrcLib::ReadDigitalChannel(BUTTON::HATR);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_LOGO] = CrcLib::ReadDigitalChannel(BUTTON::LOGO);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_FLECHE_DROITE] = CrcLib::ReadDigitalChannel(BUTTON::ARROW_RIGHT);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_FLECHE_HAUTE] = CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_FLECHE_GAUCHE] = CrcLib::ReadDigitalChannel(BUTTON::ARROW_LEFT);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_FLECHE_BASSE] = CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_B] = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_Y] = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_X] = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_BOUTON_A] = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_JOYSTICK_GAUCHE_X] = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_JOYSTICK_GAUCHE_Y] = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_JOYSTICK_DROIT_X] = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_JOYSTICK_DROIT_Y] = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_GACHETTE_GAUCHE] = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
  interfaceCRCConnect.valeurLue[INTERFACECRCCONNECT_GACHETTE_DROITE] = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);
  interfaceCRCConnect.etatDuModule = INTERFACECRCCONNECT_MODULE_EN_FONCTION;
  interfaceCRCConnect.information = INTERFACECRCCONNECT_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACECRCCONNECT interfaceCRCConnect;

//Definitions de fonctions publiques:
void interfaceCRCConnect_initialise(void)
{
  interfaceCRCConnect_invalideLesValeursLues();  
  interfaceCRCConnect.etatDuModule = INTERFACECRCCONNECT_MODULE_PAS_EN_FONCTION;
  interfaceCRCConnect.information = INTERFACECRCCONNECT_INFORMATION_TRAITEE;
  serviceBaseDeTemps_executeDansLoop[INTERFACECRCCONNECT_PHASE_DANS_LOOP] = interfaceCRCConnect_gereDansLoop;
}
