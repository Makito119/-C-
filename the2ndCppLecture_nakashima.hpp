#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#include<thread>
namespace nakashima {
    namespace t2cl {
        // 2次元座標，(x1, y1)，(x2, y2)を入力し，2点間の距離を求める関数
        double calcTheDistanceBetween(const int coordinateX1, const int coordinateY1, const int coordinateX2, const int coordinateY2);
        // 半径x[m]の球の表面積と体積を求める関数
        // 円周率はPIを使うこと
        constexpr double PI = 3.14;
        double calcSphereVolume(const double radius);
        double calcSphereSurfaceArea(const double radius);
        //listを作る
       
        void swap(int *i,int *j);
        // bubble sort（値の入れ替えには第1回課題で作成したswap関数を使用せよ）
        void bubbleSort(std::vector<int>& list);
        // quick sort
        int partition(std::vector<int>& list, const int left, const int right);
        void quickSort(std::vector<int>& list, const int left, const int right);
        //maerge sort
        void mergeSort(std::vector<int>& list, const int left, const int right);
        // sort3種の実行時間の計測と比較をせよ
        void comparisonOfSortingMethods(const std::string& filepath);
        void run(int num = 0); //ヘッダではこのように宣言すること
    }
}