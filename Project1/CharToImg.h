#pragma once

#include  "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <memory>
#include "ThreadPool.h"


class CharToImg
{
public:
	CharToImg(cv::Size sampleSize);
	cv::Mat &  charToImg(std::vector<std::string> &output, cv::Mat &colorMap);
	~CharToImg();
public:
	cv::Mat outputCache; 
	ThreadPool processPool;
};

