#pragma once

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Renderer
{
public:
	explicit Renderer(const String& windowName, const String &imgName);

	String windowName() const;
	
	void displayImage();

private:
	String m_windowName = "";
	String m_imgName = "";
};
