#include "ImgUtil.h"


 void ImgUtil::printCharToImg(const char & ch, cv::Mat & charImg, cv::Point && position, cv::Scalar color )
{
		cv::String str(1, ch);
		cv::putText(charImg, str, position, cv::FONT_HERSHEY_SIMPLEX, 1,color,2);
}
