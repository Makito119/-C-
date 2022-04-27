#include "the3rdCppLecture_nakashima.hpp"

namespace nakashima {
    namespace t4cl {
        int discriminantAnalysis(const cv::Mat1b src);
        void resize(const cv::Mat3b& src, cv::Mat3b& dst, const cv::Size& a);
        void resize1(const cv::Mat1b& src, cv::Mat1b& dst,double a, double b);
        void confirmAffine(const cv::Mat1b& src, const cv::Mat1b& yourAffine,
            const double scaleX, const double scaleY,
            const double transX, const double transY, const double deg);
        void affineTransform(const cv::Mat1b& src,cv::Mat1b& dst,
            const double scaleX, const double scaleY,
            const double transX, const double transY, const double deg);
        void templateMatching(const cv::Mat1b& src, cv::Mat1b& dst,cv::Rect& a);
        void drawRect(const cv::Mat1b& src, cv::Mat1b& dst, cv::Rect& a, uchar color);
        void labeling(const cv::Mat1b& src, cv::Mat1i& dst);
        void run(const int num=0, const std::string& imagePathconst="sample_images/lena.bmp", const std::string& hirakawaPath = "sample_images/hirakawa.bmp");
    }
}