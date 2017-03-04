#pragma once


#include  "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <map>
#include <iostream>
#include <vector>
#include <memory>





class GrayMap
{
public:	
	~GrayMap();
	static char charOfGray(uchar grey);
private:
	std::map<char, double> greyMap;
	std::map<uchar, char> greyIndex;
	GrayMap();
	static GrayMap * _instance ;
};


class ImgToChar
{
public:
	typedef  std::vector<std::string> ResultType;
	ResultType & getResultString(cv::Mat& img);
	ImgToChar(cv::Size imgSize,cv::Size sampleSize);
	~ImgToChar();
private:
	cv::Size orgSize;
	cv::Size sampleSize;
	cv::Mat greyMatCache;
	cv::Mat resizedMatCache;
	ResultType outputCache;
};

