//==============================================================================
// BASE_CTRL.CPP - Robot Base/Drive Control
//==============================================================================
// Handles robot base movement control (joystick, DPad, Rocket League mode)
// Includes steering inversion when reversing in Rocket League mode
//==============================================================================

#include "main.h"
#include "manette.h"

// ===== MODE DE CONTRÔLE =====
// true = Mode Rocket League (triggers pour avant/arrière, joystick X pour steering)
// false = Mode Joystick classique (joystick contrôle tout)
const bool ROCKET_LEAGUE_MODE = true;

// Vérifier la position du joystick gauche et appliquer la valeur correspondante à driveSpeed
void verifieCommandeDriveJoy() {
    // Calcul du steering X (identique dans les deux modes)
    int8_t steering = 0;
    if (abs(manette.leftJoystick.x) > 10) {
        if (manette.leftJoystick.x == -128) {
            steering = -126;
        } else if (manette.leftJoystick.x == 127) {
            steering = 125;
        } else {
            steering = (manette.leftJoystick.x);
        }
    }
    
    // Calcul de l'avant/arrière Y (DIFFÉRENT selon le mode)
    int8_t forward_back = 0;
    bool reversing = false;
    
    if (ROCKET_LEAGUE_MODE) {
        // MODE ROCKET LEAGUE: Utiliser les triggers pour Y
        if (manette.rightTrigger > -118) {
            forward_back = (int8_t)map(manette.rightTrigger, -128, 127, 0, 127);
        } else if (manette.leftTrigger > -118) {
            forward_back = -(int8_t)map(manette.leftTrigger, -128, 127, 0, 127);
            reversing = true;
        }
    } else {
        // MODE NORMAL: Utiliser le joystick Y
        if (abs(manette.leftJoystick.y) > 10) {
            if (manette.leftJoystick.y == -128) {
                forward_back = 127;
            } else if (manette.leftJoystick.y == 127) {
                forward_back = -128;
            } else {
                forward_back = -manette.leftJoystick.y;
            }
        }
    }
    
    // REDUCE forward speed when turning to allow better turning
    if (abs(steering) > 30 && abs(forward_back) > 20) {
        forward_back = forward_back * 2 / 3;  // reduce to 66% when turning
    }
    
    // INVERSER le steering quand on recule
    if (reversing) {
        steering = -steering;
    }
    
    // Crawl mode pour X et Y (identique dans les deux modes)
    if (manette.l3) {
        driveSpeed.x = steering / 5;
        driveSpeed.y = forward_back / 7;
    } else {
        driveSpeed.x = steering;
        driveSpeed.y = forward_back;
    }
}

// Contrôle numérique du DPad - fonctionne comme un joystick analogique
void verifieCommandeDriveDPad() {
    // Vitesse de base pour chaque direction du DPad
    const int8_t DPAD_BASE_SPEED = 50;
    
    int8_t dpad_x = 0;
    int8_t dpad_y = 0;
    
    // Calculer la composante X
    if (manette.right) {
        dpad_x += DPAD_BASE_SPEED;
    }
    if (manette.left) {
        dpad_x -= DPAD_BASE_SPEED;
    }
    
    // Calculer la composante Y
    if (manette.up) {
        dpad_y += DPAD_BASE_SPEED;
    }
    if (manette.down) {
        dpad_y -= DPAD_BASE_SPEED;
    }
    
    // Appliquer seulement si au moins un bouton est pressé
    if (manette.up || manette.down || manette.left || manette.right) {
        driveSpeed.x = dpad_x;
        driveSpeed.y = dpad_y;
    }
}