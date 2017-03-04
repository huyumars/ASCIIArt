#include "CharToImg.h"
#include "ImgUtil.h"


CharToImg::CharToImg(cv::Size sampleSize)
	:outputCache(cv::Mat(cv::Size((sampleSize.width*CharWidth), (sampleSize.height*CharHeight)), CV_8U))
{
}

cv::Mat & CharToImg::charToImg(std::vector<std::string>& output)
{
	ImgUtil::initWithColor<uchar>(outputCache, 255);
	int count = 0;
	for (auto str : output) {
		int offset = 0;
		for (char ch : str) {
			ImgUtil::printCharToImg(ch, outputCache, cvPoint(offset * CharWidth, count*CharHeight));
			offset++;
		}
		count++;
	}
	return outputCache;
}


CharToImg::~CharToImg()
{
}
