

#include "ImgUtil.h"
#include "CharImgHelper.h"

int main(int argc, char* argv[])
{


	cv::VideoCapture capture("1.mp4");//要读取的视频文件  
										  // check if video successfully opened  
	if (!capture.isOpened())
		return 1;
	// Get the frame rate  
	double rate = capture.get(CV_CAP_PROP_FPS);
	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	bool stop(false);
	cv::Mat frame; // current video frame  
	cv::namedWindow("Extracted Frame");
	// Delay between each frame in ms  
	// corresponds to video frame rate  
	CharImgHelper cih(cv::Size(frameWidth,frameHeight), 2);
	int delay = 1000 / rate;
	// for all frames in video  
	while (!stop) {
		// read next frame if any  
		if (!capture.read(frame))
			break;
		cv::Mat & result = cih.processImg(frame);
		cv::imshow("Extracted Frame", result);
		// introduce a delay  
		// or press key to stop  
		//if (cv::waitKey(delay) >= 0)
			//stop = true;
		cv::waitKey(delay);
	}
	// Close the video file.  
	// Not required since called by destructor  
	capture.release();



	/*
	const char* imagename = "1.jpg";

	
	//从文件中读入图像
	cv::Mat img = cv::imread(imagename);

	//如果读入图像失败
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}

	int scale = 5;
	CharImgHelper cih(ImgUtil::ImgSizeOf(img), 5);
	cv::Mat result = cih.processImg(img);

	cv::imshow("123", result);
	cv::waitKey();
	*/
	return 0;
}