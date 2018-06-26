#pragma once

#include "ImgToChar.h"
#include "CharToImg.h"

class CharImgHelper
{
public:
	CharImgHelper(cv::Size imgSize, int sampleRate);
	~CharImgHelper();
	cv::Mat & processImg(cv::Mat & img);
private:
	cv::Size sampleSize;
	ImgToChar imgToCharHelper;
	CharToImg charToimgHelper;
	cv::Mat outImg;
	cv::Mat colorMap;
};

