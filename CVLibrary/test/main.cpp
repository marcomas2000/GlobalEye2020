/**
 * @file main.cpp
 * @brief Background subtraction tutorial sample code (input first videocamera)
 * @author Domenico D. Bloisi / modyfied by Marco Mascioli
 */

 //C++
#include <iostream>
#include <sstream>

#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "Camera.h"
#include "Frame.h"
/**
 * @function main
 */
int main(int argc, char* argv[])
{

	//input data coming from a video
	CVLibrary::Camera cam(0);
	bool isCameraOpen = cam.openCaptureCamera();
	if (isCameraOpen == true)
	{
		//create Background Subtractor objects
		cv::Ptr<cv::BackgroundSubtractor> pSub = cv::createBackgroundSubtractorMOG2();

		CVLibrary::Frame capturedFrame;
		capturedFrame.setBgSubtractor(pSub);

		bool captureEnded = cam.startCapture(capturedFrame);
		if (captureEnded == true)
		{
			cam.stopCapture(captureEnded);
		}
		//destroy GUI windows
		cv::destroyAllWindows();
	}

	return EXIT_SUCCESS;
}

