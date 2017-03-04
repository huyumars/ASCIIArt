#pragma once
#include  "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

const cv::Size CharSize = cv::Size(25, 40);
const unsigned int CharHeight = CharSize.height;
const unsigned int CharWidth = CharSize.width;

class ImgUtil
{
public:
	static inline cv::Size ImgSizeOf(cv::Mat & img) { return cv::Size(img.cols, img.rows); }
	template<class ColorType>
	static void initWithColor(cv::Mat &img, ColorType color) {
		for (int j = 0; j<img.rows; ++j)
		{
			uchar *data = img.ptr<ColorType>(j);//.ptr<uchar>得到的是一个行的指针
			for (int i = 0; i<img.cols; ++i)
			{
				data[i] = color;
			}
		}
	}
	static void  printCharToImg(char& ch, cv::Mat &charImg, cv::Point&& position);
	template<class ColorType>
	static double calGrey(cv::Mat & img) {
		long sum = 0;
		for (int j = 0; j<img.rows; ++j)
		{
			uchar *data = img.ptr<ColorType>(j);//.ptr<uchar>得到的是一个行的指针
			for (int i = 0; i<img.cols; ++i)
			{
				sum += data[i];
			}
		}
		return sum / (double)(img.cols*img.rows);
	}
private:
	ImgUtil() {};
	~ImgUtil() {};
};

