#include "Renderer.h"

Renderer::Renderer(const cv::String& windowName, const cv::String& imgName)
{
	m_windowName = windowName;
	m_imgName = imgName;

	m_originalImg = imread(m_imgName);
	m_originalImg.copyTo(m_currentImg);

	namedWindow(m_windowName);
}

cv::String Renderer::windowName() const
{
	return m_windowName;
}

void Renderer::displayImage()
{
	imshow(m_windowName, m_currentImg);
}
