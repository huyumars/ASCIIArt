#include "CharImgHelper.h"
#include "ImgUtil.h"
#include <fstream>


std::ofstream out("ouput.txt");
std::ofstream colorfile("color.txt");
unsigned char   RGBto256(cv::Vec3b bgr) {
	int b = bgr[0]/42.7;
	int g = bgr[1]/42.7;
	int r = bgr[2]/42.7;
	return 16 + 36 * r + 6 * g + b;

}

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
	
	ImgToChar<>::ResultType & output = imgToCharHelper.getResultString(img,colorMap);
	//cv::imshow("color", colorMap);
	cv::Mat& result = charToimgHelper.charToImg(output,colorMap);

	for (int j = 0; j<output.size(); ++j)
	{
		cv::Vec3b *data = colorMap.ptr<cv::Vec3b>(j);//.ptr<uchar>得到的是一个行的指针
		for (int i = 0; i<output[0].size(); ++i)
		{
			unsigned char color = RGBto256( data[i]);
			colorfile << color;
		}
	}

	for (std::string & str : output)
		out << str << std::endl;
	out << "----"<<std::endl;

	cv::resize(result, outImg, cv::Size(img.cols, img.rows), 0, 0, cv::INTER_AREA);
	return outImg;
}
