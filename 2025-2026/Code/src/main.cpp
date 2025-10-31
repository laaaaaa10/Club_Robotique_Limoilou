//
// ░▀█▀░░░▀█▀░░░▀█▀░░░█▀█░░░█▀█░░░█▀▄░░░█▀█░░░▀█▀
// ░░█░░░░░█░░░░░█░░░░█▀█░░░█░█░░░█▀▄░░░█░█░░░░█░
// ░░▀░░░░▀▀▀░░░░▀░░░░▀░▀░░░▀░▀░░░▀▀░░░░▀▀▀░░░░▀░
//
// TitanBot 2024

#include "main.h"
#include "elevateur.h"
#include "manette.h"

#define ELEVATEUR_MOTOR CRC_PWM_1
#define DRIVE_MOTOR_L CRC_PWM_4
#define DRIVE_MOTOR_R CRC_PWM_2
#define LANCEUR_MOTOR CRC_PWM_3

#ifdef DEBUG_LOG

void debugLog();

#endif

void actionManetteConnectee();
void actionManettePasConnectee();
void updateMoteurs();

coords driveSpeed;

manette_s manette;

int8_t elevateurDirectionCommandee = 0; // 0, 1 ou -1
int8_t lanceurSpeed = 0;

void setup() {
    Serial.begin(9600);

    initManette();

    CrcLib::Initialize();

    CrcLib::InitializePwmOutput(ELEVATEUR_MOTOR);
    CrcLib::InitializePwmOutput(DRIVE_MOTOR_L);
    CrcLib::InitializePwmOutput(DRIVE_MOTOR_R);
    CrcLib::InitializePwmOutput(LANCEUR_MOTOR);
}

void loop() {
    CrcLib::Update();
    readManette();

    if (CrcLib::IsCommValid()) {
        actionManetteConnectee();
    }
    else {
        actionManettePasConnectee(); // Très important!!! Ne pas enlever!
    }

    updateMoteurs();

#ifdef DEBUG_LOG

    debugLog();

#endif
}

// Cette fonction est appelée à chaque itération de la boucle principale tant que la manette est connectée
void actionManetteConnectee() {
    actionElevateur();

    driveSpeed.x = 0;
    driveSpeed.y = 0;

    verifieCommandeDriveJoy();  // Le DPad a priorité sur le joystick gauche, donc on s'occupe du DPad après le joystick
    verifieCommandeDriveDPad(); // pour overwrite le joystick si c'est nécessaire.

    verifieCommandeElevateurAuto();   // Le contrôle manuel a priorité sur le contrôle automatique. Si il y a une commande
    verifieCommandeElevateurManuel(); // manuelle, elle va overwrite la commande automatique.

    verifieCommandeLanceur();
}

// Cette fonction est appelée à chaque itération de la boucle principale tant que la manette n'est pas connectée.
// Ne surtout pas changer ce comportement! Sans ça, lorsque la manette est déconnectée, les moteurs pourraient tous
// partir à puissance maximale, à la grande surprise de la prochaine personne qui allumera le robot.
void actionManettePasConnectee() {
    driveSpeed.x = 0;
    driveSpeed.y = 0;

    lanceurSpeed = 0;
    elevateurSpeed = 0;
}

void updateMoteurs() {
    CrcLib::MoveArcade(driveSpeed.x, driveSpeed.y, DRIVE_MOTOR_L, DRIVE_MOTOR_R);
    CrcLib::SetPwmOutput(ELEVATEUR_MOTOR, elevateurSpeed);
    CrcLib::SetPwmOutput(LANCEUR_MOTOR, lanceurSpeed);
}

#ifdef DEBUG_LOG

void debugLog() {
    char buffer[100];
    sprintf(buffer, "elevateur dc: %d, elevateur speed: %d, l1: %d, r1: %d, aimant: %d\n", elevateurDirectionCommandee,
            elevateurSpeed, manette.l1, manette.r1, aimantAligne);
    Serial.print(buffer);
}

#endif