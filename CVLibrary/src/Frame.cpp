#include <opencv2/imgproc.hpp>
#include "Frame.h"

#include <vector>

namespace CVLibrary
{

	Frame::Frame() : m_rawFrame()
	{
	}

	Frame::Frame(cv::Mat& rawFrame) : m_rawFrame(rawFrame)
	{
	}

	Frame::~Frame()
	{
	}

/**
 * update the background model
 */
	void Frame::subtractBackground(cv::Mat& foregroundFrame)
	{
		m_bgSubtractor->apply(m_rawFrame, foregroundFrame);
	}

/**
 * Sobel filter compatible with the one from GlobalEye
 */
	void Frame::fastSobel(cv::Mat& borderImg)
	{
		cv::Mat colorImageBlurred;
		cv::Mat colorImageBlurredGray;
		cv::Mat grad_x, grad_y;
		cv::Mat abs_grad_x, abs_grad_y, module_grad;

		int ksize = 1;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;

		// blur image
		cv::GaussianBlur(m_rawFrame, colorImageBlurred, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

		// Convert image to grayscale.
		cv::cvtColor(colorImageBlurred, colorImageBlurredGray, cv::COLOR_BGR2GRAY);

		Sobel(colorImageBlurredGray, grad_x, ddepth, 1, 0);
		Sobel(colorImageBlurredGray, grad_y, ddepth, 0, 1);

		// converting back to CV_8U
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, module_grad);
		// THRESH_TRIANGLE makes the function find, use and return the optimal value for the threshold.
		double optimumThresh = threshold(module_grad, borderImg, 50.0, 255, cv::THRESH_BINARY | cv::THRESH_TRIANGLE);
	}


/**
 * Sobel Edges Finder
 */
	void Frame::sobelBorders(cv::Mat& borderImg)
	{
		cv::Mat colorImageBlurred;
		cv::Mat colorImageBlurredGray;
		cv::Mat grad_x, grad_y;
		cv::Mat abs_grad_x, abs_grad_y;

		int ksize = 1;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;

		// blur image
		cv::GaussianBlur(m_rawFrame, colorImageBlurred, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

		// Convert image to grayscale.
		cv::cvtColor(colorImageBlurred, colorImageBlurredGray, cv::COLOR_BGR2GRAY);

		Sobel(colorImageBlurredGray, grad_x, ddepth, 1, 0);
		Sobel(colorImageBlurredGray, grad_y, ddepth, 0, 1);

		// converting back to CV_8U
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, borderImg);
	}

/**
 * Canny Edges Finder
 */
	void Frame::cannyBorders(cv::Mat& borderImg)
	{
		cv::Mat colorImageBlurredGray;
		cv::Mat detectedEdges;

		int lowThreshold = 0;
		const int max_lowThreshold = 100;
		const int ratio = 3;
		const int kernel_size = 3;

		// Convert image to grayscale.
		cv::cvtColor(m_rawFrame, colorImageBlurredGray, cv::COLOR_BGR2GRAY);

		// blur image
		cv::blur(colorImageBlurredGray, detectedEdges, cv::Size(3, 3));

		Canny(detectedEdges, borderImg, lowThreshold, max_lowThreshold * ratio, kernel_size);
	}

/**
 * Find contours
 */
	void Frame::findFrameContours(cv::Mat& contoursImg)
	{
		cv::Mat detectedEdges;
		cv::Mat img_gray;
		cv::Mat result;
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;

		// Convert image to grayscale.
		cv::cvtColor(m_rawFrame, img_gray, cv::COLOR_BGR2GRAY);

		// check for edges
		cannyBorders(detectedEdges);

		cv::findContours(detectedEdges, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
		img_gray = cv::Scalar::all(0);
		cv::drawContours(img_gray, contours, -1, cv::Scalar(255, 255, 255));
		contoursImg = img_gray;
	}

/**
 * Find components
 */
	void Frame::findConnectedComponents(cv::Mat& connectedComponentsImg)
	{
		cv::Mat detectedEdges;
		cv::Mat img_gray;
		cv::Mat img_color;
		cv::Mat	stats;

		// Convert image to grayscale.
		cv::cvtColor(m_rawFrame, img_gray, cv::COLOR_BGR2GRAY);

		// threshold
		//cannyBorders(detectedEdges);
		cv::threshold(img_gray, detectedEdges, 50, 255, cv::THRESH_BINARY);

		cv::Mat labelImage(img_gray.size(), CV_32S);
		int nccomps = cv::connectedComponents(detectedEdges, labelImage, 8);
		std::vector<cv::Vec3b> colors(nccomps);

		colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black.
		for (int label = 1; label < nccomps; ++label)
		{
			colors[label] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
		}

		cv::Mat result(img_gray.size(), CV_8UC3);
		for (int r = 0; r < result.rows; ++r)
		{
			for (int c = 0; c < result.cols; ++c)
			{
				int label = labelImage.at<int>(r, c);
				cv::Vec3b& pixel = result.at<cv::Vec3b>(r, c);
				pixel = colors[label];
			}
		}
		connectedComponentsImg = result;
	}

	void Frame::setRawFrame(cv::Mat& rawFrame)
	{
		m_rawFrame = rawFrame;
	}

	void Frame::setBgSubtractor(cv::Ptr<cv::BackgroundSubtractor> pBGSub)
	{
		m_bgSubtractor = pBGSub;
	}

	void Frame::showFrame(cv::String windowName, cv::Mat& frameData)
	{
		cv::imshow(windowName, frameData);
	}

	void Frame::writeFrameInfo(cv::Mat& frameData, cv::String frameInfo)
	{
		cv::rectangle(frameData, cv::Point(10, 2), cv::Point(100, 20),
			cv::Scalar(255, 255, 255), -1);
		cv::putText(frameData, frameInfo.c_str(), cv::Point(15, 15),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
	}

/**
 * create GUI windows
 */
	void Frame::createOutputWindow(cv::String name)
	{
		cv::namedWindow(name);
	}

}