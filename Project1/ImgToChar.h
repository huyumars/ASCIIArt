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
	static std::shared_ptr<GrayMap> instancePtr;
};


template<typename T=std::vector<std::string> >
class ImgToChar
{
public:
	typedef T  ResultType;
	ResultType & getResultString(cv::Mat& img, cv::Mat &  colorMap) {
		processImg(img, colorMap);
		int nl = greyMatCache.rows;
		int nc = greyMatCache.cols * greyMatCache.channels();
		//遍历图像的每个像素
		for (int j = 0; j<nl; j++)
		{
			uchar *data = greyMatCache.ptr<uchar>(j);//.ptr<uchar>得到的是一个行的指针
			for (int i = 0; i<nc; i++)
			{
				setCache( j, i, GrayMap::charOfGray(data[i]));
			}
		}
		return outputCache;
	}
	ImgToChar(cv::Size imgSize, cv::Size _sampleSize) :
		orgSize(imgSize),
		sampleSize(_sampleSize),
		greyMatCache(cv::Mat(sampleSize, CV_8U)),
		resizedMatCache(cv::Mat(sampleSize, CV_8U)){
		initOutputCache(sampleSize.height, sampleSize.width);
	}
	~ImgToChar() {};
private:
	cv::Size orgSize;
	cv::Size sampleSize;
	cv::Mat greyMatCache;
	cv::Mat resizedMatCache;
	ResultType outputCache;
	void processImg(cv::Mat& img, cv::Mat & colorMap);
	void initOutputCache(size_t height, size_t width) {}
	inline void setCache(int i, int j, const char & value) {}
};



