#include "InputHandler.h"

InputHandler::InputHandler(Renderer* renderer)
{
    m_renderer = renderer;
    cv::setMouseCallback(renderer->windowName(), InputHandler::onMouse, this);
}

void InputHandler::onMouse(int event, int x, int y, int flag, void* data)
{
    InputHandler* self = static_cast<InputHandler*>(data);
    self->mouseHandler(event, x, y, flag);
}

void InputHandler::mouseHandler(int event, int x, int y, int flag)
{
    if (event == cv::MouseEventTypes::EVENT_LBUTTONDOWN)
    {
        // TODO: draw the point that the mouse clicks
        //Draw the point that the mouse click
        //circle(img2, Point(x, y), 1, Scalar(0, 255, 255), 3);

        //pt = Point(x, y);
        m_isDrawing = true;
        printf("drawing is on\n");

    }
    else if (event == cv::MouseEventTypes::EVENT_LBUTTONUP)
    {
        m_isDrawing = false;
        printf("drawing is off\n");
    }

    // TODO: handle single click to remove blurring


    if (m_isDrawing)
    {
        // TODO: draw a rectangle from point of first click to point of drag
        //img_original.copyTo(img2);
        //rectangle(img2, pt, Point(x, y), Scalar(0, 255, 255));
    }
}

bool InputHandler::handleKeyPresses()
{
    const char c = cv::waitKey(100);

    switch (c)
    {
    case 27:
    case 'x':
    case 'X':
        return false; // Exit the application
    case 'i':
    case 'I':
        // TODO: increase the mosaic blur size
        break;
    case 'd':
    case 'D':
        // TODO: decrease the mosaic blur size
        break;
    case 'r':
    case 'R':
        // TODO: remove blur effect
        break;
    case 's':
    case 'S':
        // TODO: save the image
        break;
    default:
        break;
    }
}
