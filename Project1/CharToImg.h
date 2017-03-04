#pragma once

#include  "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class CharToImg
{
public:
	CharToImg(cv::Size sampleSize);
	cv::Mat &  charToImg(std::vector<std::string> &output);
	~CharToImg();
public:
	cv::Mat outputCache;
};

