
#include "ImgToChar.h"
#include"ImgUtil.h"


std::shared_ptr<GrayMap> GrayMap::instancePtr = std::shared_ptr<GrayMap>(new GrayMap());

uchar mapToColor(double max, double min, double value) {
	return ((value - min) / (max - min)) * 255;
}

GrayMap::GrayMap() {
	cv::Mat charImg = cv::Mat(CharSize, CV_8U);
	double maxv, minv;
	maxv = 0; minv = 256;
	for (char ch = 0; ch < 127; ch++) {
		ImgUtil::initWithColor<uchar>(charImg, 0);
		ImgUtil::printCharToImg(ch, charImg, cvPoint(0, charImg.rows - 10),cv::Scalar(255,255,255));
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
	auto chI = instancePtr->greyIndex.lower_bound(grey);
	return chI->second;
	
}


void ImgToChar<>::processImg(cv::Mat & img, cv::Mat & colorMap)
{
	cv::resize(img, resizedMatCache, sampleSize, 0, 0, cv::INTER_AREA);
	resizedMatCache.copyTo(colorMap);
	cv::cvtColor(resizedMatCache, greyMatCache, cv::COLOR_BGR2GRAY);
}

template<>
void ImgToChar<std::vector<std::string>>::initOutputCache(size_t height, size_t width) {
	outputCache = std::vector<std::string>(height, std::string(width, ' '));
}

template<>
void ImgToChar<std::vector<std::string>>::setCache(int i, int j, const char & value) {
	outputCache[i][j] = value;
}