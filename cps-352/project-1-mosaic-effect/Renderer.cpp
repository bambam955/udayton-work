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
	rectangle(m_currentImg, m_currPoints.p1, m_currPoints.p2, RECT_COLOR, RECT_THICKNESS);
}

void Renderer::saveCurrentRect()
{
	// Add the current rectangle to the last image so that it won't be erased during future redrawing.
	m_currPoints.finalize();
	rectangle(m_lastImg, m_currPoints.p1, m_currPoints.p2, RECT_COLOR, RECT_THICKNESS);

	// Debug the dimensions of the rectangle that is being drawn.
	printf("P1 (%d, %d), P2 (%d, %d)\n", m_currPoints.p1.x, m_currPoints.p1.y, m_currPoints.p2.x, m_currPoints.p2.y);

	// Blur the region inside the rectangle, then copy the results to the current image.
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
	// Increase by 1 if under 5, increase by 5 otherwise.
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

	// Decrease by 1 if at or under 5, decrease by 5 otherwise.
	// Note that because increasing works the same way, we don't have to worry about
	// going from, say, 6 to 1; the only allowable degrees above 5 are multiples of 5.
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
	// Do nothing if there are no rectangles to update.
	if (m_rectHistory.empty())
		return;

	// Bring everything back to the original image.
	m_originalImg.copyTo(m_currentImg);
	m_originalImg.copyTo(m_lastImg);

	// Blur the saved regions again according to the new blur degree.
	for (const Corners& corners : m_rectHistory)
	{
		// Re-draw the rectangle for this region.
		rectangle(m_lastImg, corners.p1, corners.p2, RECT_COLOR, RECT_THICKNESS);
		
		// Debug the dimensions of the rectangle that is being drawn.
		printf("P1 (%d, %d), P2 (%d, %d)\n", corners.p1.x, corners.p1.y, corners.p2.x, corners.p2.y);

		// Blur the region again according to the new blur degree.
		blurRegion(m_lastImg, corners);
	}

	// Copy the re-blurred regions back to the current image.
	m_lastImg.copyTo(m_currentImg);
}

void Renderer::blurRegion(Mat& img, const Corners& corners) const
{
	// Modify the region's corners to be fully inside the rectangle.
	// This way, when the rectangle is drawn, the blurred squares won't overlap with it.
	Corners insetCorners = corners;
	insetCorners.p1.x += RECT_THICKNESS;
	insetCorners.p2.x -= RECT_THICKNESS;
	insetCorners.p1.y += RECT_THICKNESS;
	insetCorners.p2.y -= RECT_THICKNESS;

	// Copy the entire image to a 2D array to make it easier to work with.
	unsigned char** arr2D = new unsigned char* [img.rows];
	for (int y = 0; y < img.rows; y++)
	{
		arr2D[y] = new unsigned char[img.cols * 3];
		memcpy(arr2D[y], img.data + y * img.cols * 3, img.cols * 3);
	}

	// This will hold the top-left point of the next square to blur. It starts at the top-left of the region.
	Point nextP1 = insetCorners.p1;



	// THIS IS WHERE THE MAGIC HAPPENS!!!

	// Iterate through the entire region inside the rectangle. Start with p1 + 1 because we shouldn't ever have a square with area 0.
	for (int x = insetCorners.p1.x + 1; x < insetCorners.p2.x; ++x)
	{
		// If this x-value doesn't mark the end of a new square, then continue on from left to right.
		if ((x - insetCorners.p1.x) % m_blurDegree != 0)
			continue;

		// But, if it does, then go from top to bottom and blur the whole column of squares one at a time.
		for (int y = insetCorners.p1.y + 1; y < insetCorners.p2.y; ++y)
		{
			// Wait until we find the vertical end of new square...
			if ((y - insetCorners.p1.y) % m_blurDegree != 0)
				continue;

			int sumBlue = 0, sumGreen = 0, sumRed = 0;
			// Sum up the red, green, and blue within the square.
			for (int y2 = nextP1.y; y2 < y; ++y2)
			{
				for (int x2 = nextP1.x; x2 < x; ++x2)
				{
					sumBlue += arr2D[y2][x2 * 3 + 0]; // Blue
					sumGreen += arr2D[y2][x2 * 3 + 1]; // Green
					sumRed += arr2D[y2][x2 * 3 + 2]; // Red
				}
			}

			// Compute the average RGB values.
			const int TOTAL_PIXELS = (y - nextP1.y) * (x - nextP1.x);
			int avgBlue = sumBlue / TOTAL_PIXELS;
			int avgGreen = sumGreen / TOTAL_PIXELS;
			int avgRed = sumRed / TOTAL_PIXELS;

			// Finally loop back through and assign each pixel to have the average RGB values for that square.
			for (int y2 = nextP1.y; y2 < y; ++y2)
			{
				for (int x2 = nextP1.x; x2 < x; ++x2)
				{
					arr2D[y2][x2 * 3 + 0] = avgBlue;
					arr2D[y2][x2 * 3 + 1] = avgGreen;
					arr2D[y2][x2 * 3 + 2] = avgRed;
				}
			}

			// Send the y-value of the next top-left point to the bottom of the current square (top of the next square).
			nextP1.y = y;
		}

		// Once we blur the whole column, the next top-left point will be at the current x-value, with y being the top of the region.
		nextP1 = Point(x, insetCorners.p1.y);
	}

	// Copy the data back to the image.
	for (int y = insetCorners.p1.y; y < insetCorners.p2.y; y++)
	{
		memcpy(img.data + y * img.cols * 3, arr2D[y], img.cols * 3);
	}

	delete[] arr2D;
}
