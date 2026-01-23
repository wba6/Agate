//
// Created by william on 11/3/22.
//

#ifndef AGATE_INPUTPULLING_H
#define AGATE_INPUTPULLING_H

#include "Agate/Core/keyCodes.h"

/**
 * @brief Provides static accessors to read the state
 *        of inputs
 */
class InputPulling {
public:

    /**
     * @brief Reads the input status of the specified key
     * 
     * @param keycode Code for target key
     * 
     * @return True if target key is pressed
     */
    static bool IsKeyPressed(unsigned int keycode);

    /**
     * @brief Reads the X coordinate of the mouse
     * 
     * @return X coordinate of the mouse position
     */
    static double GetXMousePos();

    /**
     * @brief Reads the Y coordinate of the mouse
     * 
     * @return Y coordinate of the mouse position
     */
    static double GetYMousePos();

private:
    InputPulling();
};


#endif//AGATE_INPUTPULLING_H
