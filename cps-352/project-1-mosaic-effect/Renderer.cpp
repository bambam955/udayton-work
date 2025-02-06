#include "Renderer.h"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

Renderer::Renderer(const String& windowName, const String& imgName)
{
	m_windowName = windowName;
	m_imgName = imgName;

	// Read the image from the name argument. Debug if there is an error.
	m_originalImg = imread(m_imgName);
	if (m_originalImg.empty())
	{
		fprintf(stderr, "Could not load image %s!\n", m_imgName.c_str());
		return;
	}

	// Set the points and other images to their initial states.
	resetImage();

	// Create the window to display the image in.
	namedWindow(m_windowName);
}

String Renderer::windowName() const
{
	return m_windowName;
}

void Renderer::resetImage()
{
	// Bring everything back to the original image.
	m_originalImg.copyTo(m_currentImg);
	m_originalImg.copyTo(m_lastImg);
	// Reset the points back to defaults.
	m_currentTopLeft = m_currentBottomRight = Point(-1, -1);
}

void Renderer::displayImage() const
{
	imshow(m_windowName, m_currentImg);
}

void Renderer::saveTopLeft(int x, int y)
{
	// Set the top left corner of the current rectangle.
	m_currentTopLeft = Point(x, y);
	// Create a little circle at the point's location.
	circle(m_currentImg, m_currentTopLeft, 1, Scalar(0, 255, 255), 3);
}

void Renderer::redrawCurrentRect(int x, int y)
{
	// Do not try to redraw if the top left corner is invalid.
	if (m_currentTopLeft.x < 0 || m_currentTopLeft.y < 0)
		return;

	// Remove the previous current rectangle so that we can redraw it with the new bottom right corner.
	m_lastImg.copyTo(m_currentImg);
	m_currentBottomRight = Point(x, y);
	// Redraw the rectangle.
	rectangle(m_currentImg, m_currentTopLeft, m_currentBottomRight, Scalar(0, 255, 255));
}

void Renderer::saveCurrentRect()
{
	// Add the current rectangle to the last image so that it won't be erased during future redrawing.
	rectangle(m_lastImg, m_currentTopLeft, m_currentBottomRight, Scalar(0, 255, 255));
	m_lastImg.copyTo(m_currentImg);

	// Reset the points to be invalid until we start drawing again.
	m_currentTopLeft = m_currentBottomRight = Point(-1, -1);
}

void Renderer::increaseBlurDegree()
{
	if (m_blurDegree < 5)
		++m_blurDegree;
	else
		m_blurDegree += 5;

	printf("New blur degree: %d\n", m_blurDegree);
}

void Renderer::decreaseBlurDegree()
{
	// Make sure we can't go below 1.
	if (m_blurDegree <= 1)
		return;

	if (m_blurDegree <= 5)
		--m_blurDegree;
	else
		m_blurDegree -= 5;

	printf("New blur degree: %d\n", m_blurDegree);
}

void Renderer::saveImageToFiles()
{
	// Write the current image back to the file it was read from. Debug if an error occurs.
	if (imwrite(m_imgName, m_currentImg))
	{
		printf("Saved image %s successfully.\n", m_imgName.c_str());
	}
	else
	{
		fprintf(stderr, "Failed to save image %s!!\n", m_imgName.c_str());
	}
}
