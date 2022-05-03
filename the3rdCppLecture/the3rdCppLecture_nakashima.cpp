/*#include "the3rdCppLecture_nakashima.hpp"




void nakashima::t3cl::confirmHSV(const cv::Mat& orgBGR, cv::Mat& yourHSV)
{
	auto _orgBGR = orgBGR.clone();
	cv::Mat orgHSV;
	cv::cvtColor(_orgBGR, orgHSV, cv::COLOR_BGR2HSV);
	std::vector<cv::Mat> separatedOrg(3), separatedHSV(3);
	cv::split(orgHSV, separatedOrg);
	cv::split(yourHSV, separatedHSV);
	int windowX = 100;
	int windowY = 100;
	for (int i = 0; i < 3; ++i)
	{
		cv::imshow("orgHSV channel " + std::to_string(i), separatedOrg[i]);
		cv::imshow("yourHSV channel " + std::to_string(i), separatedHSV[i]);
		cv::moveWindow("orgHSV channel " + std::to_string(i), windowX, windowY);
		cv::moveWindow("yourHSV channel " + std::to_string(i), windowX, windowY + _orgBGR.rows);
		windowX += _orgBGR.cols;
	}
	cv::waitKey();
	cv::destroyAllWindows();
}

void nakashima::t3cl::imshow(const std::string& path, cv::Mat& image)
{
	cv::imshow(path, image);
	cv::moveWindow(path, 100, 100);
	cv::waitKey();
	cv::destroyAllWindows();
}

//カラー画像をグレースケールに変換
void nakashima::t3cl::bgr2gray(const cv::Mat3b& src, cv::Mat1b& dst)
{
	dst = cv::Mat1b(src.size());
	// dst = cv::Mat1b(src.rows, src.cols); //こっちでも可

	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			dst(y, x) = static_cast<uchar>(std::floor(0.114 * src(y, x)[0] + 0.587 * src(y, x)[1] + 0.299 * src(y, x)[2]));
		}
	}
}

//２値化する
void nakashima::t3cl::binarization(const cv::Mat1b& src, cv::Mat1b& dst, int thresh)
{
	dst = cv::Mat1b(src.size());
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) < thresh) dst(y, x) = 0;
			else dst(y, x) = 255;
		}
	}
}

//濃度階調変換
void nakashima::t3cl::contrastStretching(const cv::Mat1b& src, cv::Mat1b& dst)
{
	int max = 0;
	int min = 255;
	dst = src.clone();
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) >= max) max = src(y, x);
			if (src(y, x) <= min) min = src(y, x);
		}

	}
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) < min) dst(y, x) = 0;
			else if (src(y, x) > max) dst(y, x) = 255;
			else dst(y, x) = 255 * (src(y, x) - min) / (max - min);
		}
	}

}
//３つの数比較
int nakashima::t3cl::max(double a, double b, double c) {
	int max = a;
	if (b >= max) max = b;

	if (c >= max) max = c;

	return max;
}
int nakashima::t3cl::min(double a, double b, double c) {
	int min = a;
	if (b <= min) min = b;

	if (c <= min) min = c;

	return min;
}

//HSV変換
void nakashima::t3cl::bgr2hsv(const cv::Mat3b& src, cv::Mat3b& dst) {
	dst = src.clone();
	double max = 255.0;
	double min = 0.0;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x)[0] == src(y, x)[1] == src(y, x)[2]) dst(y, x)[0] = 0.0;
			else {
				max = nakashima::t3cl::max(src(y, x)[0], src(y, x)[1], src(y, x)[2]);
				min = nakashima::t3cl::min(src(y, x)[0], src(y, x)[1], src(y, x)[2]);

				if (max == src(y, x)[2]) dst(y, x)[0] = 60.0 * (src(y, x)[1] - src(y, x)[0]) / (max - min);
				else if (max == src(y, x)[1]) dst(y, x)[0] = (60.0 * (src(y, x)[0] - src(y, x)[2]) / (max - min)) + 120.0;
				else if (max == src(y, x)[0])dst(y, x)[0] = (60.0 * (src(y, x)[2] - src(y, x)[1]) / (max - min)) + 240.0;

			}
			dst(y, x)[2] = max;
			dst(y, x)[1] = ((max - min) * 255.0 / max);
			if (dst(y, x)[0] < 0) dst(y, x)[0] += 360.0;

		}
	}
}

//ゼロパディング
void nakashima::t3cl::zeroPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth)
{
	dst = cv::Mat1b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);

	for (int y = paddingWidth; y < (src.rows) + paddingWidth; ++y) {
		for (int x = paddingWidth; x < (src.cols) + paddingWidth; ++x) {
			dst(y, x) = src(y - paddingWidth, x - paddingWidth);
		}
	}
}

//ゼロパディング(カラー)
void nakashima::t3cl::zeroPadding(const cv::Mat3b& src, cv::Mat3b& dst, int paddingWidth)
{
	dst = cv::Mat3b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);
	for (int i = 0; i < 3; ++i) {
		for (int y = paddingWidth; y < (src.rows) + paddingWidth; ++y) {
			for (int x = paddingWidth; x < (src.cols) + paddingWidth; ++x) {
				dst(y, x)[i] = src(y - paddingWidth, x - paddingWidth)[i];
			}
		}
	}

}

//コピーパディング
void nakashima::t3cl::copyPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth)
{
	dst = cv::Mat1b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);
	for (int y = 0; y < src.rows + paddingWidth * 2; ++y) {
		for (int x = 0; x < (src.cols) + paddingWidth * 2; ++x) {
			if (y >= 0 && y < paddingWidth) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(0, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(0, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(0, src.cols - 1);
				}
			}
			else if (y >= paddingWidth && y < src.rows + paddingWidth) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(y - paddingWidth, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(y - paddingWidth, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(y - paddingWidth, src.cols - 1);
				}
			}
			else if (y >= src.rows + paddingWidth && y < src.rows + paddingWidth * 2) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(src.rows - 1, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(src.rows - 1, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(src.rows - 1, src.cols - 1);
				}
			}
		}
	}
}

//コピーパディング(カラー)
void nakashima::t3cl::copyPadding(const cv::Mat3b& src, cv::Mat3b& dst, int paddingWidth)
{
	dst = cv::Mat3b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);
	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < src.rows + paddingWidth * 2; ++y) {
			for (int x = 0; x < (src.cols) + paddingWidth * 2; ++x) {
				if (y >= 0 && y < paddingWidth) {
					if (0 <= x && x < paddingWidth)dst(y, x)[i] = src(0, 0)[i];
					else if (paddingWidth <= x && x < src.cols + paddingWidth) {
						dst(y, x)[i] = src(0, x - paddingWidth)[i];
					}
					else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
						dst(y, x)[i] = src(0, src.cols - 1)[i];
					}
				}
				else if (y >= paddingWidth && y < src.rows + paddingWidth) {
					if (0 <= x && x < paddingWidth)dst(y, x)[i] = src(y - paddingWidth, 0)[i];
					else if (paddingWidth <= x && x < src.cols + paddingWidth) {
						dst(y, x)[i] = src(y - paddingWidth, x - paddingWidth)[i];
					}
					else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
						dst(y, x)[i] = src(y - paddingWidth, src.cols - 1)[i];
					}
				}
				else if (y >= src.rows + paddingWidth && y < src.rows + paddingWidth * 2) {
					if (0 <= x && x < paddingWidth)dst(y, x)[i] = src(src.rows - 1, 0)[i];
					else if (paddingWidth <= x && x < src.cols + paddingWidth) {
						dst(y, x)[i] = src(src.rows - 1, x - paddingWidth)[i];
					}
					else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
						dst(y, x)[i] = src(src.rows - 1, src.cols - 1)[i];
					}
				}
			}
		}
	}
}

//膨張
void nakashima::t3cl::dilate(const cv::Mat1b& src, cv::Mat1b& dst, int th)
{
	dst = src.clone();
	cv::Mat1b temp;
	nakashima::t3cl::zeroPadding(src, temp, 1);

	switch (th) {
	default:

	case 4:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 0 && (temp(y, x + 1) == 255 || temp(y + 1, x) == 255 || temp(y, x - 1) == 255 || temp(y - 1, x) == 255)) {
					dst(y - 1, x - 1) = 255;
				}
			}
		}
	}
	if (th != 0) break;

	case 8:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 0 && (temp(y, x + 1) == 255 || temp(y + 1, x) == 255 || temp(y, x - 1) == 255 || temp(y - 1, x) == 255 || temp(y - 1, x - 1) == 255 || temp(y - 1, x + 1) == 255 || temp(y + 1, x - 1) == 255 || temp(y + 1, x + 1) == 255)) {
					dst(y - 1, x - 1) = 255;
				}
			}
		}
	}
	if (th != 0) break;
	}
}

//収縮
void nakashima::t3cl::erode(const cv::Mat1b& src, cv::Mat1b& dst, int th)
{
	dst = src.clone();
	cv::Mat1b temp;
	nakashima::t3cl::zeroPadding(src, temp, 1);

	for (int y = 0; y < temp.rows; ++y) {
		temp(y, 0) = 255;
		temp(y, temp.cols - 1) = 255;
	}
	for (int x = 0; x < temp.cols; ++x) {
		temp(0, x) = 255;
		temp(temp.rows - 1, x) = 255;
	}

	switch (th) {
	default:

	case 4:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 255 && (temp(y, x + 1) == 0 || temp(y + 1, x) == 0 || temp(y, x - 1) == 0 || temp(y - 1, x) == 0)) {
					dst(y - 1, x - 1) = 0;
				}
			}
		}
	}
	if (th != 0) break;

	case 8:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 255 && (temp(y, x + 1) == 0 || temp(y + 1, x) == 0 || temp(y, x - 1) == 0 || temp(y - 1, x) == 0 || temp(y - 1, x - 1) == 0 || temp(y - 1, x + 1) == 0 || temp(y + 1, x - 1) == 0 || temp(y + 1, x + 1) == 0)) {
					dst(y - 1, x - 1) = 0;
				}
			}
		}
	}
	if (th != 0) break;
	}
}

//ソーベルフィルタ
void nakashima::t3cl::sobel(const cv::Mat1b& src, cv::Mat1b& dst, bool th)
{
	dst = src.clone();
	cv::Mat1b temp;
	nakashima::t3cl::zeroPadding(src, temp, 1);

	cv::Mat1i filx = (cv::Mat1i(3, 3) <<
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1);
	cv::Mat1i fily = (cv::Mat1i(3, 3) <<
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1);

	switch (th) {
	default:

	case false:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				dst(y - 1, x - 1) = abs(temp(y - 1, x - 1) * filx(0, 0) + temp(y - 1, x) * filx(0, 1) + temp(y - 1, x + 1) * filx(0, 2)
					+ temp(y, x - 1) * filx(1, 0) + temp(y, x) * filx(1, 1) + temp(y, x + 1) * filx(1, 2)
					+ temp(y + 1, x - 1) * filx(2, 0) + temp(y + 1, x) * filx(2, 1) + temp(y + 1, x + 1) * filx(2, 2));
			}
		}
	}

	if (th != 2) break;

	case true:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				dst(y - 1, x - 1) = abs(temp(y - 1, x - 1) * fily(0, 0) + temp(y - 1, x) * fily(0, 1) + temp(y - 1, x + 1) * fily(0, 2)
					+ temp(y, x - 1) * fily(1, 0) + temp(y, x) * fily(1, 1) + temp(y, x + 1) * fily(1, 2)
					+ temp(y + 1, x - 1) * fily(2, 0) + temp(y + 1, x) * fily(2, 1) + temp(y + 1, x + 1) * fily(2, 2));
				//if (dst(y - 1, x - 1) > 255) dst(y - 1, x - 1) = 255;
			}

		}
	}
	if (th != 2) break;
	}
}

//プリューウィットフィルタ
void nakashima::t3cl::prewitt(const cv::Mat1b& src, cv::Mat1b& dst, bool th)
{
	dst = src.clone();
	cv::Mat1b temp;
	nakashima::t3cl::zeroPadding(src, temp, 1);

	cv::Mat1i filx = (cv::Mat1i(3, 3) <<
		-1, 0, 1,
		-1, 0, 1,
		-1, 0, 1);
	cv::Mat1i fily = (cv::Mat1i(3, 3) <<
		-1, -1, -1,
		0, 0, 0,
		1, 1, 1);

	switch (th) {
	default:

	case false:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				dst(y - 1, x - 1) = abs(temp(y - 1, x - 1) * filx(0, 0) + temp(y - 1, x) * filx(0, 1) + temp(y - 1, x + 1) * filx(0, 2)
					+ temp(y, x - 1) * filx(1, 0) + temp(y, x) * filx(1, 1) + temp(y, x + 1) * filx(1, 2)
					+ temp(y + 1, x - 1) * filx(2, 0) + temp(y + 1, x) * filx(2, 1) + temp(y + 1, x + 1) * filx(2, 2));
			}
		}
	}

	if (th != 2) break;

	case true:
	{
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				dst(y - 1, x - 1) = abs(temp(y - 1, x - 1) * fily(0, 0) + temp(y - 1, x) * fily(0, 1) + temp(y - 1, x + 1) * fily(0, 2)
					+ temp(y, x - 1) * fily(1, 0) + temp(y, x) * fily(1, 1) + temp(y, x + 1) * fily(1, 2)
					+ temp(y + 1, x - 1) * fily(2, 0) + temp(y + 1, x) * fily(2, 1) + temp(y + 1, x + 1) * fily(2, 2));
				//if (dst(y - 1, x - 1) > 255) dst(y - 1, x - 1) = 255;
			}

		}
	}
	if (th != 2) break;
	}
}

void nakashima::t3cl::bubbleSort(std::vector<int>& list)
{


	for (int i = 0; i < (list.size() - 1); i++) {
		for (int j = (list.size() - 1); j > i; j--) {
			if (list[j] < list[j - 1]) {
				int k = list[j];
				list[j] = list[j - 1];
				list[j - 1] = k;
			}
		}
	}
}

void nakashima::t3cl::median(const cv::Mat1b& src, cv::Mat1b& dst)
{
	dst = src.clone();
	cv::Mat1b temp;
	nakashima::t3cl::copyPadding(src, temp, 1);
	std::vector<int> mid(9);
	for (int y = 1; y < temp.rows - 1; ++y) {
		for (int x = 1; x < temp.cols - 1; ++x) {

			mid[0] = temp(y - 1, x - 1);
			mid[1] = temp(y - 1, x);
			mid[2] = temp(y - 1, x + 1);
			mid[3] = temp(y, x - 1);
			mid[4] = temp(y, x);
			mid[5] = temp(y, x + 1);
			mid[6] = temp(y + 1, x - 1);
			mid[7] = temp(y + 1, x);
			mid[8] = temp(y + 1, x + 1);
			bubbleSort(mid);
			dst(y - 1, x - 1) = mid[4];
		}
	}
}

void nakashima::t3cl::gaussian(const cv::Mat1b& src, cv::Mat1b& dst, int size, int sigma)
{
	dst = src.clone();
	cv::Mat1b temp;
	int width = (size - 1) / 2;
	double PI = 3.14;
	nakashima::t3cl::copyPadding(src, temp, width);
	cv::Mat1d filter(size, size);
	double sum = 0;
	//ガウシアンフィルタをつくる
	for (int y = -width; y <= width; ++y) {
		for (int x = -width; x <= width; ++x) {

			filter(y + width, x + width) = 1 / sqrt(2 * PI * sigma * sigma) * exp(-(x * x + y * y) / (2 * sigma * sigma));
			sum += filter(y + width, x + width);
		}
	}


	//演算
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			filter(j, i) = filter(j, i) / sum;
		}
	}
	double num = 0;
	for (int y = width; y < temp.rows - width; ++y) {
		for (int x = width; x < temp.cols - width; ++x) {
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					num += filter(i, j) * temp(y - width + i, x - width + j);
				}
			}
			dst(y - width, x - width) = num;
			num = 0;
		}
	}

}

void nakashima::t3cl::run(const int num, const std::string& imagePath)
{
	const cv::Mat3b lena(cv::imread(imagePath, cv::IMREAD_COLOR));
	CV_Assert(!lena.empty());

	cv::Mat1b gray, binary;
	t3cl::bgr2gray(lena, gray);

	switch (num) {
	default:

	case 1:
		std::cout << "run binarization";
		{
			// src dst th
			t3cl::binarization(gray, binary, 120);
			t3cl::imshow("binary", binary);
		}
		std::cout << "\r" << "complete binarization" << std::endl;
		if (num != 0) break;
	case 2:
		std::cout << "run contrastStretching";
		{
			cv::Mat1b stretched;
			t3cl::contrastStretching(gray, stretched);
			t3cl::imshow("stretched", stretched);
		}
		std::cout << "\r" << "complete contrastStretching" << std::endl;
		if (num != 0) break;
	case 3:
		std::cout << "run bgr2hsv";
		{
			cv::Mat3b hsv;
			t3cl::bgr2hsv(lena, hsv);
			t3cl::confirmHSV(lena, hsv);
		}
		std::cout << "\r" << "complete bgr2hsv" << std::endl;
		if (num != 0) break;
	case 4:
		std::cout << "run zeroPadding";
		{
			cv::Mat1b zeroPadded;
			t3cl::zeroPadding(gray, zeroPadded, 5);
			t3cl::imshow("zeroPadded", zeroPadded);
		}
		std::cout << "\r" << "complete zeroPadding" << std::endl;
		if (num != 0) break;
	case 5:
		std::cout << "run copyPadding";
		{
			cv::Mat1b copyPadded;
			t3cl::copyPadding(gray, copyPadded, 5);
			t3cl::imshow("copyPadded", copyPadded);
		}
		std::cout << "\r" << "complete copyPadding" << std::endl;
		if (num != 0) break;
	case 6:
		std::cout << "run dilate";
		{
			cv::Mat1b dilated4, dilated8;
			t3cl::binarization(gray, binary, 120);
			// src dst th
			//cv::imshow("binary",binary);
			t3cl::dilate(binary, dilated4, 4);
			cv::imshow("dilated 4", dilated4);
			cv::moveWindow("dilated 4", 100 + dilated4.cols, 100);
			t3cl::dilate(binary, dilated8, 8);
			t3cl::imshow("dilated 8", dilated8);
		}
		std::cout << "\r" << "complete dilate" << std::endl;
		if (num != 0) break;
	case 7:
		std::cout << "run erode";
		{
			cv::Mat1b eroded4, eroded8;
			t3cl::binarization(gray, binary, 120);
			//cv::imshow("binary", binary);
			t3cl::erode(binary, eroded4, 4);
			cv::imshow("eroded 4", eroded4);
			cv::moveWindow("eroded 4", 100 + eroded4.cols, 100);
			t3cl::erode(binary, eroded8, 8);
			t3cl::imshow("eroded 8", eroded8);
		}
		std::cout << "\r" << "complete erode" << std::endl;
		if (num != 0) break;
	case 8:
		std::cout << "run sobel";
		{
			cv::Mat1b sobelVer, sobelHori;
			t3cl::sobel(gray, sobelVer, true);
			cv::imshow("sobelVer", sobelVer);
			cv::moveWindow("sobelVer", 100 + sobelVer.cols, 100);
			t3cl::sobel(gray, sobelHori, false);
			t3cl::imshow("sobelHori", sobelHori);
		}
		std::cout << "\r" << "complete sobel" << std::endl;
		if (num != 0) break;
	case 9:
		std::cout << "run prewitt";
		{
			cv::Mat1b prewittVer, prewittHori;
			t3cl::prewitt(gray, prewittVer, true);
			cv::imshow("prewittVer", prewittVer);
			cv::moveWindow("prewittVer", 100 + prewittVer.cols, 100);
			t3cl::prewitt(gray, prewittHori, false);
			t3cl::imshow("prewittHori", prewittHori);
		}
		std::cout << "\r" << "complete prewitt" << std::endl;
		if (num != 0) break;
	case 10:
		std::cout << "run median";
		{
			cv::Mat1b medianImg;
			t3cl::median(gray, medianImg);
			t3cl::imshow("median", medianImg);
		}
		std::cout << "\r" << "complete median" << std::endl;
		if (num != 0) break;
	case 11:
		std::cout << "run gaussian";
		{
			cv::Mat1b gaussianImg;
			// src dst kernelsize variance
			t3cl::gaussian(gray, gaussianImg, 3, 2);
			t3cl::imshow("gaussian", gaussianImg);
		}
		std::cout << "\r" << "complete gaussian" << std::endl;
		if (num != 0) break;
	}
}*/
