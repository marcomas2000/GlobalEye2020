#include "Camera.h"
#include "Frame.h"

#include <opencv2/highgui.hpp>

namespace CVLibrary
{

	Camera::Camera(int numCamera) : m_camera(numCamera),
		m_capture(0)
	{
	}

	Camera::~Camera()
	{
	};

	bool Camera::openCaptureCamera()
	{
		bool ret = false;
		//create the capture object
		m_capture = new cv::VideoCapture(m_camera);
		if (m_capture->isOpened() == true)
		{
			ret = true;
		}
		else
		{
			//error in opening the video input
			std::cerr << "Unable to open videocamera" << std::endl;
			ret = false;
		}
		return ret;
	}

	bool Camera::startCapture(Frame& capturedFrame)
	{
		bool ret = false;
		char keyboard; //input from keyboard

		cv::Mat rawFrame; //current frame

		bool m_captureSwitch = true;
		while (m_captureSwitch == true)
		{
			//read the current frame
			if (m_capture->read(rawFrame) == false)
			{
				std::cerr << "Unable to read next frame." << std::endl;
				std::cerr << "Exiting..." << std::endl;
				m_captureSwitch = false;
				ret = false;
			}
			else
			{
				capturedFrame.setRawFrame(rawFrame);
				//subtractBackground(capturedFrame);
				//sobelBorders(capturedFrame);
				fastSobel(capturedFrame);
				//cannyBorders(capturedFrame);
				//drawFrameContours(capturedFrame);
				//connectedComponents(capturedFrame);
				keyboard = cv::waitKey(30);
				ret = true;
				if (keyboard == 27)
				{
					m_captureSwitch = false;
				}
			}
		}
		return ret;
	}

	void Camera::fastSobel(Frame& capturedFrame)
	{
		cv::Mat gaussianBlur; //fg mask 

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("Sobel Edge Detector");

		// blur the image

		capturedFrame.fastSobel(gaussianBlur);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("Sobel Edge Detector", gaussianBlur);
	}

	void Camera::sobelBorders(Frame& capturedFrame)
	{
		cv::Mat gaussianBlur; //fg mask 

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("Sobel Edge Detector");

		// blur the image
		capturedFrame.sobelBorders(gaussianBlur);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("Sobel Edge Detector", gaussianBlur);
	}

	void Camera::cannyBorders(Frame& capturedFrame)
	{
		cv::Mat gaussianBlur; //fg mask 

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("Canny Edge Detector");

		// check for edges
		capturedFrame.cannyBorders(gaussianBlur);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("Canny Edge Detector", gaussianBlur);
	}

	void Camera::drawFrameContours(Frame& capturedFrame)
	{
		cv::Mat dstImage;

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("Contour Detector");

		//// check for contours
		capturedFrame.findFrameContours(dstImage);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("Contour Detector", dstImage);
	}

	void Camera::connectedComponents(Frame& capturedFrame)
	{
		cv::Mat dstImage;

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("Contour Detector");

		//// check for contours
		capturedFrame.findConnectedComponents(dstImage);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("Contour Detector", dstImage);
	}

	void Camera::subtractBackground(Frame& capturedFrame)
	{
		cv::Mat fgMaskBGSub; //fg mask 

		capturedFrame.createOutputWindow("Frame");
		capturedFrame.createOutputWindow("FG Mask");

		//update the background model
		capturedFrame.subtractBackground(fgMaskBGSub);

		//get the frame rate and write it on the current frame
		std::stringstream ss;
		ss << m_capture->get(cv::CAP_PROP_FPS);
		std::string frameNumberString = ss.str();
		capturedFrame.writeFrameInfo(capturedFrame.getRawFrame(), frameNumberString);

		capturedFrame.showFrame("Frame", capturedFrame.getRawFrame());
		capturedFrame.showFrame("FG Mask", fgMaskBGSub);
	}

	bool Camera::stopCapture(bool captureEndedCorrectly)
	{
		if (captureEndedCorrectly == true)
		{
			//delete capture object
			m_capture->release();
		}
		return captureEndedCorrectly;
	}

}