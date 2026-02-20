//==============================================================================
// ROBOT_ACTIONS_CTRL.CPP - Robot Actions Control
//==============================================================================
#include "main.h"
#include "manette.h"
#include "robot_actions_ctrl.h"
#include "grabber_encoder.h"


//===================== BUTTON MAPPINGS =======================//
// controller button mappings
#define BTN_ELEVATOR_UP manette.r1      // R1 bumper - move elevator up
#define BTN_ELEVATOR_DOWN manette.l1    // L1 bumper - move elevator down
#define BTN_GRABBER_TOGGLE manette.b    // B button - toggle grabbers open/close
#define BTN_ARM_TOP manette.y           // Y button - arm to top position
#define BTN_ARM_MIDDLE manette.x        // X button - arm to middle position
#define BTN_ARM_BOTTOM manette.a        // A button - arm to bottom position

// Limit switch pins (LS = Limit Switch)
// elevator
#define LS_ELEVATOR_BOTTOM CRC_DIG_1    // Bottom elevator     
#define LS_ELEVATOR_TOP CRC_DIG_2       // Top elevator        
// arm pos
#define LS_ARM_TOP CRC_DIG_10            // Top arm position    
#define LS_ARM_MIDDLE CRC_DIG_11         // Middle arm position 
#define LS_ARM_BOTTOM CRC_DIG_12         // Bottom arm position 
#define TOP 0
#define HALFWAY 1
#define BOTTOM 2
// grabbers
#define LS_GRABBER_OPEN CRC_DIG_6       // Grabbers open       
#define LS_GRABBER_CLOSED CRC_DIG_7     // Grabbers closed     
#define OPEN 1
#define CLOSED 0
#define CLOSING_TIME 1200  // ammound of time (in ms) to close befor it start forcing less


//=========================== VARIABLES ========================//
// elevator
int8_t elevateurSpeed = 0;
bool topLimit = false;
bool bottomLimit = false;
// grabbers - armSpeed and grabberSpeed are defined in main.cpp
bool Grabbering = false;
bool openLimit = false;
bool closedLimit = false;
int LastGrabberState = OPEN;
bool currentBtn = false;
bool prevGrabberBtn = false;
uint32_t closing_tmr = 0;  // now stores a millis() timestamp instead of a counter

// arm
bool upwards = false;
bool halfways = false;
bool downwards = false;
int TargetArmState = BOTTOM;
int LastArmState = BOTTOM;
uint32_t arm_damp_tmr = 0;  // timestamp of when arm arrived at a position
bool armArrived = false;     // true once target switch has been hit, enables dampers


//===================== FUNCTION POINTERS =======================//
void (*actionElevateur)() = initElevateur;
void (*actionGrabber)() = initGrabber;
void (*actionArm)() = controlArm;


//======================== ELEVATOR CTRL =======================//
void initElevateur() {
    topLimit = CrcLib::GetDigitalInput(LS_ELEVATOR_TOP);
    
    if (!topLimit) {
        // move up until top limit is reached
        elevateurSpeed = -75;
    } else {
        elevateurSpeed = 0;
        actionElevateur = controlElevateur;
    }
}

void controlElevateur() {
    topLimit = CrcLib::GetDigitalInput(LS_ELEVATOR_TOP);
    bottomLimit = CrcLib::GetDigitalInput(LS_ELEVATOR_BOTTOM);
    
    // Elevator control logic
    if (BTN_ELEVATOR_UP && !topLimit) {
        elevateurSpeed = -75; // move up
    }
    else if (BTN_ELEVATOR_DOWN && !bottomLimit) {
        elevateurSpeed = 50; // move down
    }
    else {
        elevateurSpeed = -10; // notihn
    }
}


//===================== GRABBERS ====================//
// open/closes with button B, uses 2 limit swtich
// idea: when toggle mode is switched to close, close it but the keep the motor engave at alow speed 
// unless closed limit switche is pressed (cause it need to make sure its holding the barrels)
// this is to prevent the motors from bruning and forcing too much
void initGrabber() {
    closedLimit = CrcLib::GetDigitalInput(LS_GRABBER_CLOSED);
    
    if (!closedLimit) {
        // close grabbers until closed limit is reached
        grabberSpeed = -50;
    } else {
        // at closed position - reset encoder
        LastGrabberState = CLOSED;
        grabberSpeed = 0;
        actionGrabber = controlGrabber;
    }
}

void controlGrabber() {
    openLimit   = CrcLib::GetDigitalInput(LS_GRABBER_OPEN);
    closedLimit = CrcLib::GetDigitalInput(LS_GRABBER_CLOSED);

    // Button debouncing
    currentBtn = BTN_GRABBER_TOGGLE;
    if (currentBtn && !prevGrabberBtn) {
        // Toggle state
        LastGrabberState = (LastGrabberState == OPEN) ? CLOSED : OPEN;
        Grabbering = true;
        closing_tmr = millis();
    }
    prevGrabberBtn = currentBtn;

    if (Grabbering) {
        // Closing
        if (LastGrabberState == CLOSED) {
            // and the holding function
            if (!closedLimit) {
                if (millis() - closing_tmr <= CLOSING_TIME) {
                    grabberSpeed = -75;
                } else {
                    grabberSpeed = -5;
                }
            } else {
                Grabbering = false;
                grabberSpeed = 0;
                closing_tmr = 0;
            }
        } 
        // Opening
        else {
            if (!openLimit) {
                grabberSpeed = 75;
            } 
            else {
                Grabbering = false;
                grabberSpeed = 0;
            }
        }
    }


}   


//===================== ARM ROTATION ====================//
// there is 3 modes mapped on 3 buttons:
// Y for the arm to go to the top position
// X for the arm to go to the middle position
// A for the arm to go to the bottom position
// physical rotation order (positive = forward): BOTTOM(0deg) -> TOP(180deg) -> HALFWAY(270deg)

void initArm() {
    downwards = CrcLib::GetDigitalInput(LS_ARM_BOTTOM);
    if (!downwards) {
        // move down until bottom limit is reached
        armSpeed = 50;
    } else {
        armSpeed = 0;
        actionArm = controlArm;
    }
}

void controlArm() {
    upwards = CrcLib::GetDigitalInput(LS_ARM_TOP);
    halfways = CrcLib::GetDigitalInput(LS_ARM_MIDDLE);
    downwards = CrcLib::GetDigitalInput(LS_ARM_BOTTOM);
    
    // check for button presses to set target arm state
    // if all buttons are pressed, do nothing (or you could set a default state)
    if (BTN_ARM_TOP) {
        if (TargetArmState != TOP) { armArrived = false; }
        TargetArmState = TOP;
    }
    else if (BTN_ARM_MIDDLE) {
        if (TargetArmState != HALFWAY) { armArrived = false; }
        TargetArmState = HALFWAY;
    }
    else if (BTN_ARM_BOTTOM) {
        if (TargetArmState != BOTTOM) { armArrived = false; }
        TargetArmState = BOTTOM;
    }


    // always update LastArmState when any limit switch is hit, regardless of target
    // this catches mid-travel hits and keeps state consistent
    // arm passed top, start 500ms countdown for dampers
    if (upwards && LastArmState != TOP) { 
        LastArmState = TOP; 
        arm_damp_tmr = millis();
    }  
    // arm reached halway
    if (halfways && LastArmState != HALFWAY) { 
        LastArmState = HALFWAY;
        armArrived = true;
    }
    // arm reached bottom
    if (downwards && LastArmState != BOTTOM) { 
        LastArmState = BOTTOM;
        armArrived = true;
    }


    // determine current arm port and move accordingly
    armSpeed = 0;
    switch (TargetArmState) {
        // move to top position (no damping)
        case TOP:
            if (LastArmState == TOP) { break; }
            if (!upwards) {
                armSpeed = (LastArmState == TOP) ? -75 : 75;
            }
        break;

        // move to middle position (270deg)
        // full speed until TOP switch hit, keep full speed for 500ms, then damp at 15 until HALFWAY reached
        case HALFWAY:
            if (LastArmState == HALFWAY) { break; }
            if (halfways) {
                armSpeed = 0;
            }
            // activates the dampers once target was reached, bounced back through TOP, and 750ms passed
            else if (armArrived && LastArmState == TOP && millis() - arm_damp_tmr > 150) {
                armSpeed = 10;                                          
            }
            else {
                armSpeed = -100;  // still traveling at full speed
            }
        break;
        
        // move to bottom position (0deg)
        // full speed until TOP switch hit, keep full speed for 500ms, then damp at -15 until BOTTOM reached
        case BOTTOM:
            if (LastArmState == BOTTOM) { break; }
            if (downwards) {
                armSpeed = 0;
            }
            // activates the dampers once target was reached, bounced back through TOP, and 750ms passed
            else if (armArrived && LastArmState == TOP && millis() - arm_damp_tmr > 150) {
                armSpeed = -10; 
            }
            else {
                armSpeed = 100;  // still traveling at full speed
            }
        break;
    }
}