#include "Renderer.h"

#include <opencv2/imgproc/imgproc.hpp>

Renderer::Renderer(const String& windowName, const String& imgName)
{
	m_windowName = windowName;
	m_imgName = imgName;

	m_originalImg = imread(m_imgName);
	m_originalImg.copyTo(m_currentImg);

	namedWindow(m_windowName);
}

String Renderer::windowName() const
{
	return m_windowName;
}

void Renderer::displayImage()
{
	imshow(m_windowName, m_currentImg);
}

void Renderer::saveTopLeft(int x, int y)
{
	circle(m_currentImg, Point(x, y), 1, Scalar(0, 255, 255), 3);
	m_topLeft = Point(x, y);
}

void Renderer::redrawRectangle(int x, int y)
{
	if (m_topLeft.x < 0 || m_topLeft.y < 0)
		return;
	m_originalImg.copyTo(m_currentImg);
	rectangle(m_currentImg, m_topLeft, Point(x, y), Scalar(0, 255, 255));
}
