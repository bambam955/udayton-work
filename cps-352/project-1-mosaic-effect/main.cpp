#pragma once

#include "InputHandler.h"
#include "Renderer.h"

int main(int argc, char** argv)
{   
    // Create the image renderer and input handler.
    // The renderer will take care of drawing everything, while the input handler will
    // handle all the keyboard and mouse input.
    Renderer renderer("My Mosaic Project", "scene.jpg");
    InputHandler inputHandler(&renderer);
    
    // Begin the main render loop.
    while(1)
    {
        // Display the current image in the window.
        renderer.displayImage();
        
        // Handle keyboard input. If a keypress tells us to exit the application then do so.
        // Otherwise loop around again.
        const bool continueLooping = inputHandler.handleKeyPresses();
        if (!continueLooping)
            break;
    }
    
    return 0;
}
