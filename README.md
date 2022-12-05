# C++で画像処理を行い、Opencvの関数を自作する。
内容は５回分で、各ファイル内はcpp,hppと資料があります

## 具体例
* メディアンフィルタ

```
Opencv C++

cv::medianBlur(src, median, filtersize);
```

```
自作
void median(const cv::Mat1b& src, cv::Mat1b& dst)
{
	dst = src.clone();
	cv::Mat1b temp;
	copyPadding(src, temp, 1);
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
```

* リサイズ関数
```
Opencv3 C++

cv::resize(入力画像、出力画像、Size（）,拡大率、拡大率)
```

```
自作

void resize(const cv::Mat3b& src, cv::Mat3b& dst, const cv::Size& a)
{
	dst = cv::Mat3b(a.height, a.width);
	cv::Mat3b temp;
	copyPadding(src, temp, 1);
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
```

* ラベリング

```
Opencv C++

retval, labels = cv2.connectedComponents(image, labels, connectivity, ltype)
```

```
自作

void labeling(const cv::Mat1b& src, cv::Mat1i& dst)
{
	cv::Mat1b temp1;
	zeroPadding(src, temp1, 1);
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
	for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {	
				dst(y - 1, x - 1) = temp3(y, x);
		}
	}
}
```

