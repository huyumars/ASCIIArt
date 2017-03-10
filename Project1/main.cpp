#include "BackgroundWorker.h"

#include "ImgUtil.h"
#include "CharImgHelper.h"
#include "ThreadPool.h"
#include <iostream>
#include <vector>



int main(int argc, char* argv[])
{

	//ThreadPool tp(4);

	// tp.runTask([]() {std::cout << "1"; });
	// tp.runTask([]() {std::cout << "2";  });
	//tp.runTask([]() {std::cout << "3"; return 1; });
	// tp.runTask([]() {std::cout << "4"; return 1; });
	// tp.runTask([]() {std::cout << "5"; return 1; });
	// tp.runTask([]() {std::cout << "6"; return 1; });
	//
	// tp.join();

	// tp.runTask([]() {std::cout << "7"; return 1; });
	// tp.runTask([]() {std::cout << "8"; return 1; });
	// tp.runTask([]() {std::cout << "9"; return 1; });

	// tp.join();
	//return 0;


	cv::VideoCapture capture("2.mkv");//要读取的视频文件  
										  // check if video successfully opened  
	
	if (!capture.isOpened())
		return 1;
	// Get the frame rate  
	double rate = capture.get(CV_CAP_PROP_FPS);
	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	long framecnt = capture.get(CV_CAP_PROP_FRAME_COUNT);
	long cnt=0;

	// CV_FOURCC('D','I','B',' ') is lossless, but it may touch the 4GB limtation of opencv
	cv::VideoWriter  video("ouput.avi", CV_FOURCC('D','I','V','X'),
		rate, cvSize(frameWidth, frameHeight), 1);//1代表彩色视频，0代表黑白视频，即mask
	bool stop(false);
	cv::Mat frame; // current video frame  
	//cv::namedWindow("Extracted Frame");



	CharImgHelper cih(cv::Size(frameWidth,frameHeight), 5);
	int delay = 1000 / rate;
	int videoFCC = video.get(CV_CAP_PROP_FOURCC);
	while (!stop) {

		if (!capture.read(frame))
			break;
		cv::Mat & result = cih.processImg(frame);
		cv::imshow("Extracted Frame", result);
		video << result;
		// introduce a delay  
		// or press key to stop  
		//if (cv::waitKey(delay) >= 0)
			//stop = true;
		cv::waitKey(10);
		cnt++;
		if (cnt % 20) {
			std::cout <<"progress "<< 100*cnt / (float)framecnt << "%" << std::endl;		
		}
	}

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