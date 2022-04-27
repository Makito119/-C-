#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#include<thread>
namespace nakashima {
    namespace t2cl {
        // 2�������W�C(x1, y1)�C(x2, y2)����͂��C2�_�Ԃ̋��������߂�֐�
        double calcTheDistanceBetween(const int coordinateX1, const int coordinateY1, const int coordinateX2, const int coordinateY2);
        // ���ax[m]�̋��̕\�ʐςƑ̐ς����߂�֐�
        // �~������PI���g������
        constexpr double PI = 3.14;
        double calcSphereVolume(const double radius);
        double calcSphereSurfaceArea(const double radius);
        //list�����
       
        void swap(int *i,int *j);
        // bubble sort�i�l�̓���ւ��ɂ͑�1��ۑ�ō쐬����swap�֐����g�p����j
        void bubbleSort(std::vector<int>& list);
        // quick sort
        int partition(std::vector<int>& list, const int left, const int right);
        void quickSort(std::vector<int>& list, const int left, const int right);
        //maerge sort
        void mergeSort(std::vector<int>& list, const int left, const int right);
        // sort3��̎��s���Ԃ̌v���Ɣ�r������
        void comparisonOfSortingMethods(const std::string& filepath);
        void run(int num = 0); //�w�b�_�ł͂��̂悤�ɐ錾���邱��
    }
}