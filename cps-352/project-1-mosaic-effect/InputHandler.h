#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "Renderer.h"

class InputHandler
{
public:
	explicit InputHandler(Renderer* renderer);

	// Wait for any keyboard input.
	bool handleKeyPresses();
private:
	// Handle mouse events using a callback function.
	// We need a static function because the openCV argument doesn't accept class members.
	// However, the "data" argument can be set to contain the pointer to this object so that we can call members of it.
	static void onMouse(int event, int x, int y, int flag, void* data);
	void mouseHandler(int event, int x, int y, int flag);

	// Store the renderer object passed in from the constructor.
	Renderer* m_renderer = nullptr;
	// Whether we are currently drawing another rectangle or not.
	bool m_isDrawing = false;

	// Whether the mouse has moved since it was pressed down.
	// If it hasn't been, we'll consider it a click, and then we'll reset the image on mouse release.
	// Otherwise, we'll start drawing a new rectangle.
	bool m_hasMouseMovedSinceClick = false;
};
