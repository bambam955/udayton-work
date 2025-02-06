#pragma once

#include <opencv2/core/core.hpp>

using namespace cv;

class Renderer
{
public:
	// When a renderer is created, pass in the name of the window to be created and the name of the image file.
	explicit Renderer(const String& windowName, const String &imgName);

	// Get the name of the window.
	String windowName() const;
	
	void resetImage();
	void displayImage() const;

	// Save the point at the given coordinates as the top left corner of the current drawing rectangle.
	void saveTopLeft(int x, int y);
	// Redraw the current rectangle using the saved top left corner and the new bottom right corner.
	void redrawCurrentRect(int x, int y);
	// Save the current top left and bottom right corners as a new rectangle.
	// Update the last image to statically include this rectangle in future renderings.
	void saveCurrentRect();

	// Increase/Decrease the level of mosaic blurring inside the rectangles.
	// Changes by 1 from degrees 1-5 and by 5 for degrees 5 and above.
	void increaseBlurDegree();
	void decreaseBlurDegree();

	// Save the edited image to the file location.
	void saveImageToFiles();

private:
	String m_windowName = "";
	String m_imgName = "";

	// We save three versions of the image at all times.
	// original - image that was initially read from the file. This is what we reset to if needed.
	// last     - image that contains all the blurred rectangles except for the currently drawing one.
	// current  - image that contains all the rectangles of the last image, plus the one that is
	//			  currently being drawn.
	Mat m_originalImg;
	Mat m_lastImg;
	Mat m_currentImg;

	// Save the points of the rectangle that is currently being drawn.
	Point m_currentTopLeft = Point(-1, -1);
	Point m_currentBottomRight = Point(-1, -1);

	// The level of blurring to add inside each rectangle.
	unsigned int m_blurDegree = 5;
};
