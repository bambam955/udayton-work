#include "Renderer.h"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

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
	// Reset the current points back to defaults.
	m_currPoints.clear();
	// Clear the history.
	m_rectHistory.clear();
}

void Renderer::displayImage() const
{
	imshow(m_windowName, m_currentImg);
}

void Renderer::saveTopLeft(int x, int y)
{
	// Set the top left corner of the current rectangle.
	m_currPoints.p1 = Point(x, y);
	// Create a little circle at the point's location.
	circle(m_currentImg, m_currPoints.p1, 1, Scalar(0, 255, 255), 3);
}

void Renderer::redrawCurrentRect(int x, int y)
{
	// Do not try to redraw if the top left corner is invalid.
	if (m_currPoints.p1.x < 0 || m_currPoints.p1.y < 0)
		return;

	// Remove the previous current rectangle so that we can redraw it with the new bottom right corner.
	m_lastImg.copyTo(m_currentImg);
	m_currPoints.p2 = Point(x, y);
	// Redraw the rectangle.
	rectangle(m_currentImg, m_currPoints.p1, m_currPoints.p2, Scalar(0, 255, 255));
}

void Renderer::saveCurrentRect()
{
	// Add the current rectangle to the last image so that it won't be erased during future redrawing.
	m_currPoints.finalize();
	blurRegion(m_lastImg, m_currPoints);
	m_lastImg.copyTo(m_currentImg);
	// Add this rectangle to the history.
	m_rectHistory.push_back(Corners(m_currPoints.p1, m_currPoints.p2));
	// Reset the points to be invalid until we start drawing again.
	m_currPoints.clear();
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

void Renderer::increaseBlurDegree()
{
	if (m_blurDegree < 5)
		++m_blurDegree;
	else
		m_blurDegree += 5;

	// Re-blur all the regions that were previously selected.
	printf("New blur degree: %d\n", m_blurDegree);
	updateAllBlurredRegions();
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

	// Re-blur all the regions that were previously selected.
	printf("New blur degree: %d\n", m_blurDegree);
	updateAllBlurredRegions();
}

void Renderer::updateAllBlurredRegions()
{
	if (m_rectHistory.empty())
		return;

	// Bring everything back to the original image.
	m_originalImg.copyTo(m_currentImg);
	m_originalImg.copyTo(m_lastImg);

	// Blur the saved regions again according to the new blur degree.
	for (const Corners& corners : m_rectHistory)
	{
		printf("P1 (%d, %d), P2 (%d, %d)\n", corners.p1.x, corners.p1.y, corners.p2.x, corners.p2.y);
		blurRegion(m_lastImg, corners);
	}

	// Copy the re-blurred regions back to the current image.
	m_lastImg.copyTo(m_currentImg);
}

void Renderer::blurRegion(Mat& img, const Corners& corners) const
{
	// Create a 2D array to represent this matrix.
	// The number of rows is the number of rows in the matrix, but
	// number of columns will be columns * 3 because each pixel has three channels.
	rectangle(img, corners.p1, corners.p2, Scalar(0, 255, 255));

	unsigned char** arr2D = new unsigned char*[img.rows];
	for (int y = 0; y < img.rows; y++)
	{
		arr2D[y] = new unsigned char[img.cols * 3];
		memcpy(arr2D[y], img.data + y * img.cols * 3, img.cols * 3);
	}

	for (int y = corners.p1.y; y < corners.p2.y; y+=1)
	{
		for (int x = corners.p1.x; x < corners.p2.x; x+= 1)
		{
			arr2D[y][x * 3 + 0] *= m_blurDegree; // Blue
			arr2D[y][x * 3 + 1] *= m_blurDegree; // Green
			arr2D[y][x * 3 + 2] *= m_blurDegree; // Red
		}
	}

	for (int y = corners.p1.y; y < corners.p2.y; y++)
	{
		memcpy(img.data + y * img.cols * 3, arr2D[y], img.cols * 3);
	}

	delete[] arr2D;
}
