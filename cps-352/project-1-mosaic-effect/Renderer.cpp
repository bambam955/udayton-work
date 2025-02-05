#include "Renderer.h"

Renderer::Renderer(const cv::String& windowName, const cv::String& imgName)
{
	m_windowName = windowName;
	m_imgName = imgName;
}

cv::String Renderer::windowName() const
{
	return m_windowName;
}

void Renderer::displayImage()
{
}
