#include "CharToImg.h"
#include "ImgUtil.h"
#include "ThreadPool.h"

CharToImg::CharToImg(cv::Size sampleSize)
	:outputCache(cv::Mat(cv::Size((sampleSize.width*CharWidth), (sampleSize.height*CharHeight)), CV_8UC3)),
	 processPool(8)
{
}

cv::Mat & CharToImg::charToImg(std::vector<std::string> &output, cv::Mat& colorMap)
{
	ImgUtil::initWithColor<cv::Vec3b>(outputCache, cv::Vec3b(255,255,255));
	std::vector<std::future<int>> resultlist;
	for (int count = 0; count < output.size(); count++) {
		const std::string& str = output[count];
		processPool.runTask([&str,&colorMap,this,count]() {
			int offset = 0;
			cv::Vec3b *data = colorMap.ptr<cv::Vec3b>(count);
			for (int i = 0; i < str.size(); ++i) {
				cv::Scalar color = data[i];
				ImgUtil::printCharToImg('@',outputCache, cvPoint(offset * CharWidth, count*CharHeight),color);
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
