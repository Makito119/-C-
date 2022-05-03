#ifndef HEADER_HPP
#define HEADER_HPP

#define _CRT_SECURE_NO_WARNINGS // ひとまずおまじない
#include <iostream>
#include <string>
#include<cmath>
#include<vector>
#include<fstream>
#include<chrono>
#include<thread>
#include<algorithm>//max,min
#include <opencv2/opencv.hpp> // opencv 用インクルードファイル

#endif

namespace nakashima {
    namespace t3cl {
        void confirmHSV(const cv::Mat& orgBGR, cv::Mat& yourHSV);
        void bgr2gray(const cv::Mat3b& src, cv::Mat1b& dst);
        void contrastStretching(const cv::Mat1b& src, cv::Mat1b& dst);
        void imshow(const std::string& path, cv::Mat& image);
        void binarization(const cv::Mat1b& src,cv::Mat1b& dst, int thresh);
        int max(double a, double b, double c);
        int min(double a, double b, double c);
        void bgr2hsv(const cv::Mat3b& src, cv::Mat3b& dst);
        void zeroPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth);
        void zeroPadding(const cv::Mat3b& src, cv::Mat3b& dst, int paddingWidth);
        void copyPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth);
        void copyPadding(const cv::Mat3b& src, cv::Mat3b& dst, int paddingWidth);
        void dilate(const cv::Mat1b& src, cv::Mat1b& dst, int th);
        void erode(const cv::Mat1b& src, cv::Mat1b& dst, int th);
        void sobel(const cv::Mat1b& src, cv::Mat1b& dst, bool th);
        void prewitt(const cv::Mat1b& src, cv::Mat1b& dst, bool th);
        void median(const cv::Mat1b& src, cv::Mat1b& dst);
        void bubbleSort(std::vector<int>& list);
        void gaussian(const cv::Mat1b& src, cv::Mat1b& dst, int size, int sigma);
        void run(const int num = 0, const std::string& imagePath = "sample_images/lena.bmp");
    }
}
