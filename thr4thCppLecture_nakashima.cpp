/*#include "the4thCppLecture_nakashima.hpp"


int nakashima::t4cl::discriminantAnalysis(const cv::Mat1b src)
{
	double temp = 0.0;
	double max = 0.0;
	int th = 0;
	for (int i = 0; i < 256; ++i) {
		double w1 = 0.0, w2 = 0.0;
		double m1 = 0.0, m2 = 0.0;
		for (int y = 0; y < src.rows; ++y) {
			for (int x = 0; x < src.cols; ++x) {

				if (src(y, x) < i) {
					w1 = w1 + 1.0;
					m1 += src(y, x);
				}
				else {
					w2 = w2 + 1.0;;
					m2 += src(y, x);
				}
			}
		}
		m1 = m1 / w1;
		m2 = m2 / w2;
		temp = w1 * w2 * (m1 - m2) * (m1 - m2);
		if (temp > max) {
			max = temp;
			th = i;
		}
	}
	return th;
}

void nakashima::t4cl::resize(const cv::Mat3b& src, cv::Mat3b& dst, const cv::Size& a)
{
	dst = cv::Mat3b(a.height, a.width);
	cv::Mat3b temp;

	nakashima::t3cl::copyPadding(src, temp, 1);
	double scaleY = (double)dst.rows / (double)src.rows;
	double scaleX = (double)dst.cols / (double)src.cols;
	for (int i = 0; i < 3; ++i) {
		for (int y = 0; y < dst.rows; ++y) {
			for (int x = 0; x < dst.cols; ++x) {
				double syy = (double)y / scaleY;
				double sxx = (double)x / scaleX;
				double sy = (int)syy;
				double sx = (int)sxx;
				dst(y, x)[i] = temp(sy, sx)[i] * (1.0 - syy + sy) * (1.0 - sxx + sx) + temp(sy + 1.0, sx)[i] * (syy - sy) * (1.0 - sxx + sx)
					+ temp(sy, sx + 1.0)[i] * (1.0 - syy + sy) * (sxx - sx) + temp(sy + 1.0, sx + 1.0)[i] * (sxx - sx) * (syy - sy);

			}
		}
	}
}

void nakashima::t4cl::resize1(const cv::Mat1b& src, cv::Mat1b& dst, double a, double b)
{
	dst = cv::Mat1b(a * src.rows, b * src.cols);
	cv::Mat1b temp;

	nakashima::t3cl::copyPadding(src, temp, 1);
	for (int i = 0; i < 3; ++i) {
		for (int y = 0; y < dst.rows; ++y) {
			for (int x = 0; x < dst.cols; ++x) {
				double syy = (double)y / a;
				double sxx = (double)x / b;
				double sy = (int)syy;
				double sx = (int)sxx;
				dst(y, x) = temp(sy, sx) * (1.0 - syy + sy) * (1.0 - sxx + sx) + temp(sy + 1.0, sx) * (syy - sy) * (1.0 - sxx + sx)
					+ temp(sy, sx + 1.0) * (1.0 - syy + sy) * (sxx - sx) + temp(sy + 1.0, sx + 1.0) * (sxx - sx) * (syy - sy);

			}
		}
	}
}



void nakashima::t4cl::affineTransform(const cv::Mat1b& src, cv::Mat1b& dst,
	const double scaleX, const double scaleY,
	const double transX, const double transY, const double deg)
{
	double size = 2.0;
	constexpr double PI = 3.1415;
	double r = deg * PI / 180.0;
	double cosine = cos(r);
	double sine = sin(r);
	cv::Mat1b temp;
	cv::Mat1d temp1 = cv::Mat1d::zeros(src.rows * size, src.cols * size);
	resize1(src, temp, scaleY, scaleX);
	dst = cv::Mat1b::zeros(src.rows * size, src.cols * size);
	double X = ((dst.cols / 2.0) - src.cols * scaleX / 2.0);
	double Y = ((dst.rows / 2.0) - src.rows * scaleY / 2.0);
	double midY = dst.rows / 2.0;
	double midX = dst.cols / 2.0;

	for (double y = 0.0; y < src.rows * scaleY; ++y) {
		for (double x = 0.0; x < src.cols * scaleX; ++x) {

			if ((y + Y) < 0.0 || (x + X) < 0.0 || (y + Y) > dst.rows || (x + X) > dst.cols) {
				;
			}
			else temp1(y + Y, x + X) = temp(y, x);


		}
	}
	for (double y = Y - midY; y < Y - midY + src.rows * scaleY; y = y + 0.1) {
		for (double x = X - midX; x < X - midX + src.cols * scaleX; x = x + 0.1) {

			double xx = cosine * (x)-sine * (y);
			double yy = sine * (x)+cosine * (y);
			double a = yy + midY + transY;
			double b = xx + midX + transX;
			if ((a > dst.rows) || (b > dst.cols) || a < 0 || b < 0) {
				;
			}

			else {
				dst(a, b) = temp1(y + midY, x + midX);
			}

		}
	}
}
void nakashima::t4cl::confirmAffine(const cv::Mat1b& src, const cv::Mat1b& yourAffine,
	const double scaleX, const double scaleY,
	const double transX, const double transY, const double deg)
{
	cv::Mat1b dst;
	const double rad = (deg * CV_PI) / 180.0;
	cv::Mat1d affineMat = (cv::Mat1d(2, 3) <<
		scaleX * std::cos(rad), -scaleX * std::sin(rad), transX,
		scaleY * std::sin(rad), scaleY * std::cos(rad), transY);
	cv::warpAffine(src, dst, affineMat, src.size() * 2);            //opencv affine
	cv::imshow("affineTransformed", yourAffine);
	cv::moveWindow("affineTransformed", 100, 100);
	cv::imshow("affineOpenCV", dst);
	cv::moveWindow("affineOpenCV", 100 + dst.cols, 100);
	cv::waitKey();
	cv::destroyAllWindows();
}

void nakashima::t4cl::templateMatching(const cv::Mat1b& src, cv::Mat1b& dst, cv::Rect& a)
{
	int width = dst.cols;
	int height = dst.rows;
	int min = 0;
	int x1 = 0;
	int y1 = 0;
	int b = 255*width*height;
	
	for (int y = 0; y < src.rows - dst.rows; ++y) {
		for (int x = 0; x < src.cols - dst.cols; ++x) {
			int sum = 0;
			for (int w = 0; w < width - 1; ++w) {
				for (int h = 0; h < height - 1; ++h) {
					min = abs(src(y + h, x + w) - dst(h, w));
					sum += min;	
				}
			}
			if (sum < b) {
				b = sum;
				x1 = x;
				y1 = y;
			}
		}
	}

	a = cv::Rect(x1, y1, dst.cols, dst.rows);
	
		
}

void nakashima::t4cl::drawRect(const cv::Mat1b& src, cv::Mat1b& dst, cv::Rect& a,const uchar color)
{
	a.y *= 2;
	a.x *= 2;
	a.width *= 2;
	a.height *= 2;
	dst = src.clone();
	for (int y = 0; y < 2; ++y) {
		for (int x = a.x; x <a.x+a.width+2; ++x) {
			dst(a.y+y, x) = color;
			dst(a.y+a.height+y,x) = color;
		}
	}
	for (int x = 0; x < 2; ++x) {
		for (int y = a.y; y < a.y + a.height; y++) {
			dst(y, a.x+x) = color;
			dst(y, a.x + a.width+x) = color;
		}
	}
}




void nakashima::t4cl::run(const int num, const std::string& imagePath, const std::string& hirakawaPath)
{
	const cv::Mat3b lena(cv::imread(imagePath, cv::IMREAD_COLOR));
	CV_Assert(!lena.empty());
	const cv::Mat1b hirakawa(cv::imread(hirakawaPath, cv::IMREAD_GRAYSCALE));
	CV_Assert(!hirakawa.empty());

	cv::Mat1b gray;
	t3cl::bgr2gray(lena, gray);

	switch (num) {
	default:
	case 1:
		std::cout << "run resize ";
		{
			cv::Mat3b resized;
			// src dst size
			t4cl::resize(lena, resized, cv::Size(600, 600));
			//t4cl::resize(lena, resized,640, 320);
			t3cl::imshow("resized", resized);
		}
		std::cout << "\r" << "complete resize" << std::endl;
		if (num != 0) break;
	case 2:
		std::cout << "run discriminantAnalysis";
		{
			cv::Mat1b binary;
			t3cl::binarization(gray, binary, discriminantAnalysis(gray));
			t3cl::imshow("discriminantAnalysis", binary);
		}
		std::cout << "\r" << "complete discriminantAnalysis" << std::endl;
		if (num != 0) break;
	case 3:
		std::cout << "run affineTransform";
		{
			cv::Mat1b affineTransformed;
			constexpr double scaleX(0.8), scaleY(0.8);
			constexpr int transX(100), transY(-50), deg(-40.0);
			// src dst scaleX yscaleY transX transY degree
			t4cl::affineTransform(gray, affineTransformed, scaleX, scaleY, transX, transY, deg);
			//opencv-affine-transform
			t4cl::confirmAffine(gray, affineTransformed, scaleX, scaleY, transX, transY, deg);
		}
		std::cout << "\r" << "complete affineTransform" << std::endl;
		if (num != 0) break;
	case 4:
		std::cout << "run templateMatching";
		{
			cv::Mat1b result, resizedGray;
			cv::resize(gray, resizedGray, resizedGray.size(), 0.5, 0.5);
			cv::Mat1b temp(resizedGray, cv::Rect(75, 75, 15, 15));
			//cv::Mat1b temp(gray, cv::Rect(75, 75, 55, 55));
			cv::Rect matchingArea;
			uchar color(0);
			// src template dstRect
			t4cl::templateMatching(resizedGray, temp, matchingArea);
			t4cl::drawRect(gray, result, matchingArea, color);
			cv::imshow("template", temp);
			cv::moveWindow("template", 100 + result.cols, 100);
			t3cl::imshow("templateMatching", result);
		}
		std::cout << "\r" << "complete templateMatching" << std::endl;
		if (num != 0) break;
		//case 5:
		//    std::cout << "run bilateral";
		//    {
		//        cv::Mat1b result, area(gray);
		//        // src dst kernelsize standardDeviation1 standardDeviation2
		//        t4cl::bilateral(gray, result, 5, 30, 30);
		//        t3cl::imshow("bilateral", result);
		//    }
		//    std::cout << "\r" << "complete bilateral" << std::endl;
		//    if (num != 0) break;
		//case 6:
		//    std::cout << "run thinning";
		//    {
		//        cv::Mat1b thinned;
		//        t4cl::thinning(hirakawa, thinned);
		//        t3cl::imshow("thinned", thinned);
		//    }
		//    std::cout << "\r" << "complete thinning" << std::endl;
		//    if (num != 0) break;
	}
}*/