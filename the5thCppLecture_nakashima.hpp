#include "the4thCppLecture_nakashima.hpp"

namespace nakashima {
    namespace t5cl {
        void labeling(const cv::Mat1b& src, cv::Mat1i& dst);
        void coloring(const cv::Mat1i& src, cv::Mat3b& dst);
        int min(int a, int b, int c, int d);
        void bubbleSort(std::vector<int>& list);
        void run(const int num = 0, const std::string& imagePathconst = "sample_images/lena.bmp", const std::string& hirakawaPath = "sample_images/hirakawa.bmp");
    }
}