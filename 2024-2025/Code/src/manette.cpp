//
// Created by clovis on 3/19/24.
//

#include "main.h"
#include "manette.h"
#include "elevateur.h"

void initManette() {
    manette.a = false;
    manette.b = false;
    manette.x = false;
    manette.y = false;
    manette.up = false;
    manette.down = false;
    manette.left = false;
    manette.right = false;
    manette.select = false;
    manette.start = false;
    manette.l1 = false;
    manette.r1 = false;
    manette.l2 = false;
    manette.r2 = false;
    manette.xbox = false;
    manette.leftJoystick.x = 0;
    manette.leftJoystick.y = 0;
    manette.rightJoystick.x = 0;
    manette.rightJoystick.y = 0;
    manette.leftTrigger = 0;
    manette.rightTrigger = 0;
}

void readManette() {
    // Mettre en commentaire les boutons non utilisés pour économiser des ressources.
    manette.a = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);
    //manette.b = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
    manette.x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
    //manette.y = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
    manette.up = CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP);
    manette.down = CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN);
    manette.left = CrcLib::ReadDigitalChannel(BUTTON::ARROW_LEFT);
    manette.right = CrcLib::ReadDigitalChannel(BUTTON::ARROW_RIGHT);
    //manette.select = CrcLib::ReadDigitalChannel(BUTTON::SELECT);
    //manette.start = CrcLib::ReadDigitalChannel(BUTTON::START);
    manette.l1 = CrcLib::ReadDigitalChannel(BUTTON::L1);
    manette.r1 = CrcLib::ReadDigitalChannel(BUTTON::R1);
    //manette.l2 = CrcLib::ReadDigitalChannel(BUTTON::HATL);
    //manette.r2 = CrcLib::ReadDigitalChannel(BUTTON::HATR);
    //manette.xbox = CrcLib::ReadDigitalChannel(BUTTON::LOGO);
    manette.leftJoystick.x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
    manette.leftJoystick.y = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
    manette.rightJoystick.x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);
    manette.rightJoystick.y = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);
    manette.leftTrigger = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
    manette.rightTrigger = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);
}

// La variable elevateurDirectionCommandee va gentiment demander à la machine à états dans elevateur.cpp de monter,
// descendre ou ne pas bouger. C'est la machine à états qui décidera quoi faire de cette demande.
void verifieCommandeElevateurAuto() {
    if (manette.l1 && manette.l2) {
        elevateurDirectionCommandee = 0;
    } else if (manette.l1) {
        elevateurDirectionCommandee = 1;
    } else if (manette.r1) {
        elevateurDirectionCommandee = -1;
    }
}

// Contrôle manuel de l'élévateur. Peut être utile pour faire des tests ou en cas de problème.
void verifieCommandeElevateurManuel() {
    // Les gâchettes sont = -128 lorsqu'elles ne sont pas appuyés et 127 lorsqu'elles sont 100% enfonçées
    if (manette.leftTrigger > -118 && manette.rightTrigger < -118) {
        elevateurSpeed = (int8_t)map(manette.leftTrigger, -128, 127, 0, -30);
    } else if (manette.rightTrigger > -118 && manette.leftTrigger < -118) {
        elevateurSpeed = (int8_t)map(manette.rightTrigger, -128, 127, 0, 30);
    }
}

// Vérifier la position du joystick gauche et appliquer la valeur correspondante à driveSpeed
void verifieCommandeDriveJoy() {
    if ((abs(manette.leftJoystick.x) > 10 || abs(manette.leftJoystick.y) > 10)) {
        if (manette.a) { // Crawl mode
            driveSpeed.x = (int8_t)(-(manette.leftJoystick.x / 2));
            driveSpeed.y = (int8_t)(-(manette.leftJoystick.y / 5)); // Ça prend plus de jus pour tourner
        }
        else {
            if (manette.leftJoystick.x == -128) {
                driveSpeed.x = 127; // Pour éviter que ça overflow
            } else if (manette.leftJoystick.x == 127) {
                driveSpeed.x = -128;
            } else {
                driveSpeed.x = -manette.leftJoystick.x;
            }

            if (manette.leftJoystick.y == -128) {
                driveSpeed.y = 127; // Pour éviter que ça overflow
            } else if (manette.leftJoystick.y == 127) {
                driveSpeed.y = -128;
            } else {
                driveSpeed.y = -manette.leftJoystick.y;
            }
        }
    }
}

// Même chose que verifieCommandeDrive, mais avec le DPad. Sert à rouler ben lentement.
void verifieCommandeDriveDPad() {
    if (manette.up) {
        driveSpeed.x = 0;
        driveSpeed.y = 25;
    }

    if (manette.up && manette.right) {
        driveSpeed.x = -25;
        driveSpeed.y = 12;
    }

    if (manette.right && !manette.up) {
        driveSpeed.x = -50;
        driveSpeed.y = 0;
    }

    if (manette.right && manette.down) {
        driveSpeed.x = -25;
        driveSpeed.y = -12;
    }

    if (manette.down && !manette.right) {
        driveSpeed.x = 0;
        driveSpeed.y = -25;
    }

    if (manette.down && manette.left) {
        driveSpeed.x = 25;
        driveSpeed.y = -12;
    }

    if (manette.left && !manette.down) {
        driveSpeed.x = 50;
        driveSpeed.y = 0;
    }

    if (manette.left && manette.up) {
        driveSpeed.x = 25;
        driveSpeed.y = 12;
    }
}

void verifieCommandeLanceur() {
    if (manette.x) {
        lanceurSpeed = 127;
    } else {
        lanceurSpeed = 0;
    }
}