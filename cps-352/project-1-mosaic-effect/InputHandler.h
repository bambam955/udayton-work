#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "Renderer.h"

class InputHandler
{
public:
	explicit InputHandler(Renderer* renderer);

	bool handleKeyPresses();
private:
	static void onMouse(int event, int x, int y, int flag, void* data);
	void mouseHandler(int event, int x, int y, int flag);

	Renderer* m_renderer = nullptr;
	bool m_isDrawing = false;
};
