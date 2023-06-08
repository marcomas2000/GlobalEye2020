#ifndef _FRAME_H_
#define _FRAME_H_

#include <string>

#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>


/**************************
class Frame
{
public:	
	Frame();

	Frame(cv::Mat& rawFrame);

	virtual ~Frame();

	//update the background model
	void subtractBackground(cv::Mat& foregroundFrame);
	// Sobel filter compatible with the one from GlobalEye
	void fastSobel(cv::Mat& foregroundFrame);
	// Sobel Edges Finder
	void sobelBorders(cv::Mat& foregroundFrame);
	// Canny Edges Finder
	void cannyBorders(cv::Mat& foregroundFrame);
	// Find contours
	void findFrameContours(cv::Mat& contoursImg);
	// Find components
	void findConnectedComponents(cv::Mat& connectedComponentsImg);

	void setRawFrame(cv::Mat& rawFrame);
	cv::Mat& getRawFrame();

	void setBgSubtractor(cv::Ptr<cv::BackgroundSubtractor> pBGSub);

	void showFrame(cv::String windowName, cv::Mat& frameData);

	void writeFrameInfo(cv::Mat& frameData, cv::String frameInfo);

	//create GUI windows
	void createOutputWindow(cv::String name);

private:
	cv::Ptr<cv::BackgroundSubtractor> m_bgSubtractor;
	cv::Mat m_rawFrame;
};
**************************/
namespace CVLibrary
{
	class Frame
	{
private:
		cv::Ptr<cv::BackgroundSubtractor> m_bgSubtractor;
		cv::Mat m_rawFrame;


	public:
		Frame();
		virtual ~Frame();
		Frame(cv::Mat& rawFrame);
		/**
		 * Canny Edges Finder
		 */
		void cannyBorders(cv::Mat& foregroundFrame);
		/**
		 * create GUI windows
		 */
		void createOutputWindow(cv::String name);
		/**
		 * Sobel filter compatible with the one from GlobalEye
		 */
		void fastSobel(cv::Mat& foregroundFrame);
		/**
		 * Find components
		 */
		void findConnectedComponents(cv::Mat& connectedComponentsImg);
		/**
		 * Find contours
		 */
		void findFrameContours(cv::Mat& contoursImg);
		inline cv::Mat& getRawFrame(){

			return m_rawFrame;
		}
		void setBgSubtractor(cv::Ptr<cv::BackgroundSubtractor> pBGSub);
		void setRawFrame(cv::Mat& rawFrame);
		void showFrame(cv::String windowName, cv::Mat& frameData);
		/**
		 * Sobel Edges Finder
		 */
		void sobelBorders(cv::Mat& foregroundFrame);
		/**
		 * update the background model
		 */
		void subtractBackground(cv::Mat& foregroundFrame);
		void writeFrameInfo(cv::Mat& frameData, cv::String frameInfo);

	};

}

#endif // _FRAME_H_
