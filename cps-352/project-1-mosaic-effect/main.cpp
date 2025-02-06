#pragma once

#include "InputHandler.h"
#include "Renderer.h"

int main(int argc, char** argv)
{   
    Renderer renderer("My Mosaic Project", "scene.jpg");
    InputHandler inputHandler(&renderer);
    
    while(1)
    {
        renderer.displayImage();
        
        const bool continueLooping = inputHandler.handleKeyPresses();
        if (!continueLooping)
            break;
    }
    
    return 0;
}
