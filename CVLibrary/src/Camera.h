#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <iostream>
#include <sstream>

#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

#include "Frame.h"

/***************************
class Camera
{
public:
	Camera(int numCamera);

	virtual ~Camera();

	bool openCaptureCamera();

	bool startCapture(Frame& capturedFrame);

	bool stopCapture(bool captureEndedCorrectly);
private:
	void subtractBackground(Frame& capturedFrame);
	void sobelBorders(Frame& capturedFrame);
	void fastSobel(Frame& capturedFrame);
	void cannyBorders(Frame& capturedFrame);
	void drawFrameContours(Frame& capturedFrame);
	void connectedComponents(Frame& capturedFrame);

	cv::VideoCapture * m_capture;
	//bool m_captureSwitch;
	int m_camera;
};
************************************/
namespace CVLibrary
{
	class Camera
	{
private:
		/**
		 * bool m_captureSwitch;
		 */
		int m_camera;
		cv::VideoCapture* m_capture;


	public:
		Camera();
		virtual ~Camera();
		Camera(int numCamera);
		bool openCaptureCamera();
		bool startCapture(Frame& capturedFrame);
		bool stopCapture(bool captureEndedCorrectly);

	
private:
		void cannyBorders(Frame& capturedFrame);
		void connectedComponents(Frame& capturedFrame);
		void drawFrameContours(Frame& capturedFrame);
		void fastSobel(Frame& capturedFrame);
		void sobelBorders(Frame& capturedFrame);
		void subtractBackground(Frame& capturedFrame);
};

}

#endif // _CAMERA_H_
