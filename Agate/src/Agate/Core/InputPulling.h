//
// Created by william on 11/3/22.
//

#ifndef AGATE_INPUTPULLING_H
#define AGATE_INPUTPULLING_H

#include "Agate/Core/keyCodes.h"
class InputPulling {
public:
    static bool IsKeyPressed(unsigned int keycode);

private:
    InputPulling();
};


#endif//AGATE_INPUTPULLING_H
