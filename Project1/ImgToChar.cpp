#include "ImgToChar.h"
#include"ImgUtil.h"

GrayMap* GrayMap::_instance = new GrayMap();

uchar mapToColor(double max, double min, double value) {
	return ((value - min) / (max - min)) * 255;
}

GrayMap::GrayMap() {
	cv::Mat charImg = cv::Mat(CharSize, CV_8U);
	double maxv, minv;
	maxv = 0; minv = 256;
	for (char ch = 0; ch < 127; ch++) {
		ImgUtil::initWithColor<uchar>(charImg, 255);
		ImgUtil::printCharToImg(ch, charImg, cvPoint(0, charImg.rows - 10));
		double val = ImgUtil::calGrey<uchar>(charImg);
		greyMap[ch] = val;
		std::cout << "finish " << val << " " << (int)ch << std::endl;
		maxv = std::max(maxv, val);
		minv = std::min(minv, val);
	}
	for (auto pair : greyMap) {
		greyIndex[mapToColor(maxv, minv, pair.second)] = pair.first;
	}
}


GrayMap::~GrayMap() {

}

char GrayMap::charOfGray(uchar grey)
{
	auto chI = _instance->greyIndex.lower_bound(grey);
	return chI->second;
	
}

ImgToChar::ResultType& ImgToChar::getResultString(cv::Mat & img)
{
	cv::cvtColor(img, greyMatCache, cv::COLOR_BGR2GRAY);
	cv::resize(greyMatCache, resizedMatCache, sampleSize,0,0, cv::INTER_AREA);

	int nl = resizedMatCache.rows;
	int nc = resizedMatCache.cols * resizedMatCache.channels();

	//遍历图像的每个像素
	for (int j = 0; j<nl; ++j)
	{
		uchar *data = resizedMatCache.ptr<uchar>(j);//.ptr<uchar>得到的是一个行的指针
		for (int i = 0; i<nc; ++i)
		{
			outputCache[j][i] = GrayMap::charOfGray(data[i]);
		}
	}
	return outputCache;
}



ImgToChar::ImgToChar(cv::Size imgSize, cv::Size _sampleSize):
	orgSize(imgSize),
	sampleSize(_sampleSize),
	greyMatCache(cv::Mat(imgSize, CV_8U)),
	resizedMatCache(cv::Mat(sampleSize, CV_8U)),
	outputCache(sampleSize.height, std::string(sampleSize.width, ' '))
{
}


ImgToChar::~ImgToChar()
{
}
