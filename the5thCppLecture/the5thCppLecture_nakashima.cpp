#include "the5thCppLecture_nakashima.hpp"

void nakashima::t5cl::labeling(const cv::Mat1b& src, cv::Mat1i& dst)
{
	cv::Mat1b temp1;
	nakashima::t3cl::zeroPadding(src, temp1, 1);
	cv::Mat1i temp2;
	dst = cv::Mat1i::zeros(src.rows, src.cols);
	temp2 = cv::Mat1i::zeros(temp1.rows, temp1.cols);
	cv::Mat1i temp3;
	temp3 = cv::Mat1i::zeros(temp1.rows, temp1.cols);
	for (int y = 0; y < temp1.rows; ++y) {
		for (int x = 0; x < temp1.cols; ++x) {
			if (temp1(y, x) == 255) {
				temp1(y, x) = 1;
			}
		}
	}

	long A[256];
	for (long i = 1; i < 256; i++) {
		A[i] = i;
	}
	A[0] = 0;

	//一次スキャン
	int a = 1;
	for (int y = 1; y < temp2.rows - 1; ++y) {
		for (int x = 1; x < temp2.cols - 1; ++x) {
			int min[9];
			min[0] = temp2(y - 1, x - 1);
			min[1] = temp2(y - 1, x);
			min[2] = temp2(y - 1, x + 1);
			min[3] = temp2(y, x - 1);
			int b = 256;
			for (int i = 0; i < 4; ++i) {

				if (min[i] != 0) {
					if (min[i] < b) b = min[i];
				}
			}
			if (temp1(y, x) == 1) {
				if (min[0] == 0 && min[1] == 0 && min[2] == 0&& min[3] == 0) {

					temp2(y, x) = a;
					a++;
				}
				else if (temp2(y - 1, x - 1) > 0 || temp2(y, x - 1) > 0 || temp2(y - 1, x) > 0 || temp2(y - 1, x + 1) > 0) {
					temp2(y, x) = b;
					if (temp2(y - 1, x - 1) != 1) {	
						A[temp2(y - 1, x - 1)] = b;
						temp2(y - 1, x - 1) = b;
					}
					if (temp2(y, x - 1) != 1) {
						A[temp2(y, x - 1)] = b;
						temp2(y, x - 1) = b;
					}
					/*if (temp2(y-1, x ) != 1) {
						
						A[temp2(y-1, x )] = b;
						temp2(y-1, x ) = b;
					}*/
					/*if (temp2(y-1, x + 1) != 1) {
						
						A[temp2(y-1, x + 1)] = b;
						temp2(y-1, x + 1) = b;
					}*/
				}

			}
		}
	}


	
	
	//
	for (int d = 0; d < 1; ++d) {
		for (int y = temp2.rows - 2; y > 0; --y) {
			for (int x = temp2.cols - 2; x > 0; --x) {
				int min[4];

				min[0] = temp2(y + 1, x - 1);
				min[1] = temp2(y + 1, x);
				min[2] = temp2(y + 1, x + 1);
				min[3] = temp2(y, x + 1);

				int b = 256;
				for (int i = 0; i < 4; ++i) {
					if (min[i] != 0) {
						if (min[i] < b) b = min[i];
					}
				}

				if (temp2(y, x) > 0) {
					if (min[0] != 0 || min[1] != 0 || min[2] != 0 || min[3] != 0) {
						A[temp2(y , x )] = b;
						temp2(y , x ) = b;
						/*if (temp2(y + 1, x - 1) > b) {
							A[temp2(y + 1, x - 1)] = b;
							temp2(y + 1, x - 1) = b;

						}
						if (temp2(y + 1, x) > b) {
							A[temp2(y + 1, x)] = b;
							temp2(y + 1, x) = b;

						}*/
						if (temp2(y + 1, x + 1) > b) {

							A[temp2(y + 1, x + 1)] = b;
							temp2(y + 1, x + 1) = b;
						}
						if (temp2(y, x + 1) > b) {

							A[temp2(y, x + 1)] = b;
							temp2(y, x + 1) = b;
						}
					}
				}
			}

		}

	}

	//重複した値を統合
	for (int y = 1; y < temp2.rows - 1; ++y) {
		for (int x = 1; x < temp2.cols - 1; ++x) {
			for (int i = 1; i < 256; i++) {
				if (temp2(y, x) == i) {
					temp3(y, x) = A[i];
				}
			}
		}
	}
	
	
	//ラベルの値を調整
	long C[1024];
	int v = 0;
	int wid = 1;
	/*for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {
			for (int i = 1; i < 256; i++) {
				if (temp3(y, x) == i && temp3(y - 1, x - 1) == 0 && temp3(y - 1, x) == 0 && temp3(y - 1, x + 1) == 0 && temp3(y, x - 1) == 0) {
					C[v] = i;
					v = v + wid;
				}
			}
		}
	}*/

	for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {
	
				dst(y - 1, x - 1) = temp3(y, x);
			
		}
	}

	//出力画像
	/*int D[50];
	int d = 0;
	for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {
			for (int i = 0; i < 512; i) {
				if (temp3(y, x) == C[i]) dst(y - 1, x - 1) = i + wid;
				i = i + wid;
				
				D[d] = i;
				d++;
			}
		}
	}
	for (int i = 0; i < 40; i++) {
		std::cout << D[i] << std::endl;
	}*/
}

void nakashima::t5cl::coloring(const cv::Mat1i& src, cv::Mat3b& dst) {
	CV_Assert(!src.empty());
	dst = cv::Mat3b::zeros(src.rows, src.cols);

	int numLabel = 0;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (numLabel < src(y, x)) {
				numLabel = src(y, x);
			}
		}
	}

	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) != 0) {
				int hue = 180 * (src(y, x) - 1) / numLabel;
				dst(y, x) = cv::Vec3b(hue, 255, 255);
			}
		}
	}
	cv::cvtColor(dst, dst, cv::COLOR_HSV2BGR);
}

void nakashima::t5cl::run(const int num, const std::string& imagePath, const std::string& hirakawaPath)
{
	const cv::Mat3b lena(cv::imread(imagePath, cv::IMREAD_COLOR));
	CV_Assert(!lena.empty());
	const cv::Mat1b hirakawa(cv::imread(hirakawaPath, cv::IMREAD_GRAYSCALE));
	CV_Assert(!hirakawa.empty());

	switch (num) {
	default:
	case 1:
		std::cout << "run labeling ";
		{
			cv::Mat1i labeled;
			t5cl::labeling(hirakawa, labeled);

			cv::Mat3b colored;
			t5cl::coloring(labeled, colored);
			t3cl::imshow("labeling", colored);
		}
		std::cout << "\r" << "complete labeling" << std::endl;
		if (num != 0) break;
		//case 2:
		//    std::cout << "run shallowConvolution ";
		//    {
		//        cv::Mat3b conv;
		//        // 設計したフィルタ可視化用の出力
		//        std::vector<cv::Mat1f> outputCreatedFilters_1st, outputCreatedFilters_2nd;
		//        t5cl::shallowConvolution(lena, conv, outputCreatedFilters_1st, outputCreatedFilters_2nd);
		//        t3cl::imshow("conv", conv);
		//    }
		//    std::cout << "\r" << "complete shallowConvolution" << std::endl;
		//    if (num != 0) break;
	}
}
