#include "CharToImg.h"
#include "ImgUtil.h"
#include "ThreadPool.h"

CharToImg::CharToImg(cv::Size sampleSize)
	:outputCache(cv::Mat(cv::Size((sampleSize.width*CharWidth), (sampleSize.height*CharHeight)), CV_8U)),
	 processPool(8)
{
}

cv::Mat & CharToImg::charToImg(std::vector<std::string>& output)
{
	ImgUtil::initWithColor<uchar>(outputCache, 255);
	std::vector<std::future<int>> resultlist;
	for (int count = 0; count < output.size(); count++) {
		const std::string& str = output[count];
		processPool.runTask([&str,this,count]() {
			int offset = 0;
			for (char ch : str) {
				ImgUtil::printCharToImg(ch, outputCache, cvPoint(offset * CharWidth, count*CharHeight));
				offset++;
			}	
		});
	}
	processPool.join();
	return outputCache;
}


CharToImg::~CharToImg()
{
}
