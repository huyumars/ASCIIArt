#include "ImgUtil.h"



 void ImgUtil::printCharToImg(char & ch, cv::Mat & charImg, cv::Point && position)
{
		cv::String str(1, ch);
		cv::putText(charImg, str, position, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 2);
}
