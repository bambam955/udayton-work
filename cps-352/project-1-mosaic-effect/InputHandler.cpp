#include "InputHandler.h"

using namespace cv;

InputHandler::InputHandler(Renderer* renderer)
{
    m_renderer = renderer;
    // Set the callback as the static function to fit the argument type (*).
    // Pass in this object to be returned in the callback later.
    cv::setMouseCallback(renderer->windowName(), InputHandler::onMouse, this);
}

void InputHandler::onMouse(int event, int x, int y, int flag, void* data)
{
    // Cast the data pointer to this object, then call the real handler.
    InputHandler* self = static_cast<InputHandler*>(data);
    self->mouseHandler(event, x, y, flag);
}

void InputHandler::mouseHandler(int event, int x, int y, int flag)
{
    switch (event)
    {
    case cv::MouseEventTypes::EVENT_LBUTTONDOWN:
    {
        // Save the top left point and set status variables.
        m_renderer->saveTopLeft(x, y);
        m_isDrawing = true;
        m_hasMouseMovedSinceClick = false;
        printf("drawing is on\n");
        break;
    }
    case cv::MouseEventTypes::EVENT_LBUTTONUP:
    {
        // Once the mouse is released, reset the image if it hasn't moved since being pressed.
        // That means it was clicked. TODO: use duration checker to further validate this...
        // If it has moved, then save the rectangle.
        if (m_hasMouseMovedSinceClick)
            m_renderer->saveCurrentRect();
        else
            m_renderer->resetImage();

        m_isDrawing = false;
        printf("drawing is off\n");
        break;
    }
    case cv::MouseEventTypes::EVENT_MOUSEMOVE:
    {
        // Set the flag so we know for the future.
        m_hasMouseMovedSinceClick = true;
        break;
    }
    default:
        break;
    }

    if (m_isDrawing)
    {
        m_renderer->redrawCurrentRect(x, y);
    }
}

bool InputHandler::handleKeyPresses()
{
    const char c = cv::waitKey(100);

    switch (c)
    {
    case 27: // ASCII for Esc key
    case 'x':
    case 'X':
        return false; // Exits the application
    case 'i':
    case 'I':
        m_renderer->increaseBlurDegree();
        break;
    case 'd':
    case 'D':
        m_renderer->decreaseBlurDegree();
        break;
    case 'r':
    case 'R':
        m_renderer->resetImage();
        break;
    case 's':
    case 'S':
        if (m_isDrawing)
            break;
        m_renderer->saveImageToFiles();
        break;
    default:
        break;
    }
}
