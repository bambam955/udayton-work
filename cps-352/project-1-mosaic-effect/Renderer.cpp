#include "Renderer.h"

#include <opencv2/imgproc/imgproc.hpp>

Renderer::Renderer(const String& windowName, const String& imgName)
{
	m_windowName = windowName;
	m_imgName = imgName;

	m_originalImg = imread(m_imgName);

	if (m_originalImg.empty())
	{
		std::cerr << "Could not load image " << m_imgName;
		return;
	}

	m_originalImg.copyTo(m_currentImg);
	m_originalImg.copyTo(m_lastImg);

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
	m_currentTopLeft = Point(x, y);
	circle(m_currentImg, m_currentTopLeft, 1, Scalar(0, 255, 255), 3);
}

void Renderer::redrawCurrentRect(int x, int y)
{
	if (m_currentTopLeft.x < 0 || m_currentTopLeft.y < 0)
		return;

	m_lastImg.copyTo(m_currentImg);
	m_currentBottomRight = Point(x, y);
	rectangle(m_currentImg, m_currentTopLeft, m_currentBottomRight, Scalar(0, 255, 255));
}

void Renderer::saveCurrentRect()
{
	rectangle(m_lastImg, m_currentTopLeft, m_currentBottomRight, Scalar(0, 255, 255));
	m_lastImg.copyTo(m_currentImg);

	m_currentTopLeft = Point(-1, -1);
	m_currentBottomRight = Point(-1, -1);
}

void Renderer::saveImageToFiles()
{
	bool success = imwrite(m_imgName, m_currentImg);
	if (success)
	{
		std::cout << "Successfully saved image " << m_imgName;
	}
	else
	{
		std::cerr << "Failed to save image " << m_imgName;
	}
}
