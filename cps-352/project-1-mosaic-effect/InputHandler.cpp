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
        m_renderer->saveTopLeft(x, y);

        m_isDrawing = true;
        printf("drawing is on\n");

    }
    else if (event == cv::MouseEventTypes::EVENT_LBUTTONUP)
    {
        m_renderer->saveCurrentRect();

        m_isDrawing = false;
        printf("drawing is off\n");
    }

    // TODO: handle single click to remove blurring

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
    case 27:
    case 'x':
    case 'X':
        return false; // Exit the application
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
        // TODO: remove blur effect
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
