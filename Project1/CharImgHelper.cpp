#include "CharImgHelper.h"
#include "ImgUtil.h"

CharImgHelper::CharImgHelper(cv::Size imgSize, int sampleRate):
	sampleSize(cv::Size(imgSize.width*sampleRate / CharWidth, imgSize.height*sampleRate / CharHeight)),
	imgToCharHelper(imgSize, sampleSize),
	charToimgHelper(sampleSize),
	outImg(imgSize, CV_8U)
{
	 
}

CharImgHelper::~CharImgHelper()
{
}

cv::Mat & CharImgHelper::processImg(cv::Mat & img)
{
	ImgToChar::ResultType & output = imgToCharHelper.getResultString(img);
	cv::Mat& result = charToimgHelper.charToImg(output);
	cv::resize(result, outImg, cv::Size(img.cols, img.rows), 0, 0, cv::INTER_AREA);
	return outImg;
}
