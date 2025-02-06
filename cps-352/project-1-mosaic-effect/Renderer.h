#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Renderer
{
public:
	explicit Renderer(const String& windowName, const String &imgName);

	String windowName() const;
	
	void displayImage() const;

	void saveTopLeft(int x, int y);
	void redrawCurrentRect(int x, int y);
	void saveCurrentRect();

	void increaseBlurDegree();
	void decreaseBlurDegree();

	void saveImageToFiles();

private:
	String m_windowName = "";
	String m_imgName = "";

	Mat m_originalImg;
	Mat m_lastImg;
	Mat m_currentImg;

	Point m_currentTopLeft = Point(-1, -1);
	Point m_currentBottomRight = Point(-1, -1);

	unsigned int m_blurDegree = 5;
};
