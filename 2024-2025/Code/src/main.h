//
// Created by clovis on 3/6/24.
//

#ifndef ROBOT2024_MAIN_H
#define ROBOT2024_MAIN_H

#include <CrcBuzz.h>
#include <CrcLib.h>
#include <CrcNeo.h>
#include <CrcRemoteState.h>
#include <CrcXbee.h>

struct coords {
    int8_t x;
    int8_t y;
};

extern coords driveSpeed;
extern int8_t lanceurSpeed;

#endif //ROBOT2024_MAIN_H
