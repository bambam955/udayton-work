#include <stdio.h>
#include <iostream>

//Include OpenCV header files to recognize "Mat"
#include <opencv2/core/core.hpp>  //Define the most important class/structure
#include <opencv2/highgui/highgui.hpp> //provide input/output functions
#include <opencv2/imgproc/imgproc.hpp> //provide image processing functions

#include "InputHandler.h"
#include "Renderer.h"

using namespace cv;
using namespace std; //cout or cin for c++

Mat img2;  //Mat is the most important class in opencv
          //"matrix" is considered as an image holder
Mat img_original;  //This image is holding the original values

Point pt = Point(-1, -1);  //Represent previous point

int main(int argc, char** argv)
{

    img2 = imread("scene.jpg"); //load image file into RAM and store it as "img" variable
    img2.copyTo(img_original);  //In the beginning, image_original is identical as img2
    
    namedWindow("My Window"); //Create a window called "My Window"
                              // This line is optional if you just display an image in the window
                              //But if you need the window receive mouse event, you have to declare this window first
    
    Renderer renderer("My Mosaic Project", "scene.jpg");
    InputHandler inputHandler(&renderer);
    
    
    while(1)
    {
        imshow("My Window", img2); //OpenCV create a window called "My Window"
        // display the img within the "My Window"
        
        
        //Using keyboard to stop the while loop
        const bool continueLooping = inputHandler.handleKeyPresses();
        if (!continueLooping)
            break;
    }
    
    return 0;
}
