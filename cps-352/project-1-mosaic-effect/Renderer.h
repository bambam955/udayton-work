#pragma once

#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>

class Renderer
{
public:
	// When a renderer is created, pass in the name of the window to be created and the name of the image file.
	explicit Renderer(const cv::String& windowName, const cv::String &imgName);

	// Get the name of the window.
	cv::String windowName() const;
	
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
	struct Corners {
		cv::Point p1;
		cv::Point p2;

		Corners() {}
		Corners(const cv::Point& _p1, const cv::Point& _p2)
		{
			p1 = _p1;
			p2 = _p2;
			finalize();
		}

		// Re-initialize the points so that p1 is the top left and p2 is the bottom right.
		void finalize() {
			// This is effectively a swap function so we need to save a temporary point.
			cv::Point temp = p1;
			p1 = cv::Point(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
			p2 = cv::Point(std::max(temp.x, p2.x), std::max(temp.y, p2.y));
		}
		void clear() { p1 = p2 = cv::Point(-1, -1); }
	};

	void blurRegion(cv::Mat& img, const Corners& corners) const;
	void updateAllBlurredRegions();

	cv::String m_windowName = "";
	cv::String m_imgName = "";

	// We save three versions of the image at all times.
	// original - image that was initially read from the file. This is what we reset to if needed.
	// last     - image that contains all the blurred rectangles except for the currently drawing one.
	// current  - image that contains all the rectangles of the last image, plus the one that is
	//			  currently being drawn.
	cv::Mat m_originalImg;
	cv::Mat m_lastImg;
	cv::Mat m_currentImg;

	// Save the points of the rectangle that is currently being drawn.
	Corners m_currPoints;
	// Save the entire history of points in pairs of points.
	std::vector<Corners> m_rectHistory;

	// The level of blurring to add inside each rectangle.
	unsigned int m_blurDegree = 5;

};
