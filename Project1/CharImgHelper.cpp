#include "CharImgHelper.h"
#include "ImgUtil.h"

class A {
public:
	~A() { std::cout << "I am out" << std::endl; }
};

A a;





CharImgHelper::CharImgHelper(cv::Size imgSize, int sampleRate):
	sampleSize(cv::Size(imgSize.width*sampleRate / CharWidth, imgSize.height*sampleRate / CharHeight)),
	imgToCharHelper(imgSize, sampleSize),
	charToimgHelper(sampleSize),
	outImg(imgSize, CV_8UC3),
	colorMap(sampleSize, CV_8UC3)
{
	 
}

CharImgHelper::~CharImgHelper()
{
}

cv::Mat & CharImgHelper::processImg(cv::Mat & img)
{
	
	ImgToChar::ResultType & output = imgToCharHelper.getResultString(img,colorMap);
	//cv::imshow("color", colorMap);
	cv::Mat& result = charToimgHelper.charToImg(output,colorMap);
	cv::resize(result, outImg, cv::Size(img.cols, img.rows), 0, 0, cv::INTER_AREA);
	return outImg;
}
