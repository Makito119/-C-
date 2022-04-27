//#include "the2ndCppLecture_nakashima.hpp"
//
//std::vector<int> list= { 7,6,13,56,77,22,89,234,66,27,677,2,666,5,4,54,3,2,11,1 };
//double nakashima::t2cl::calcTheDistanceBetween(const int X1, const int Y1, const int X2, const int Y2)
//{
//    return sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
//}
//double nakashima::t2cl::calcSphereVolume(const double radius)
//{
//    return 4.0/3.0*PI*radius*radius*radius;
//}
//double nakashima::t2cl::calcSphereSurfaceArea(const double radius)
//{
//    return 4.0 * PI * radius * radius;
//}
//
//void nakashima::t2cl::swap(int *i,int *j)
//{
//
//    int temp = *i;
//    *i = *j;
//    *j = temp;
//}
//void nakashima::t2cl::bubbleSort(std::vector<int> &list)
//{
//    
//   
//    for (int i = 0; i < (list.size()-1); i++) {
//        for (int j = (list.size() - 1); j > i; j--) {
//            if (list[j] < list[j - 1]) {
//                swap(&list[j], &list[j-1]);
//                /*int k = list[j];
//                list[j] = list[j - 1];
//                list[j - 1] = k;*/
//            }
//        }
//        for (int i = 0; i < list.size(); i++) {
//            std::cout << list[i] << "\t";
//        } 
//        
//        std::cout << std::endl;
//    }
//    
//    
//}
//int nakashima::t2cl::partition(std::vector<int>& list, int left, int right)
//{
//    int pivot = list[right];
//    int i = left - 1;
//    for (int j = left; j < right; j++) {
//        if (list[j] <= pivot) {
//            i++;
//            swap(&list[i], &list[j]);
//        }
//    }
//    swap(&list[i + 1], &list[right]);
//    return i + 1;
//}
//void nakashima::t2cl::quickSort(std::vector<int>& list, const int left, const int right)
//{
//    
//    if (left < right) {
//        int mid = partition(list, left, right);
//
//        for (int i = 0; i < list.size(); i++) {
//            std::cout << list[i] << "\t";
//        }
//        std::cout << std::endl;
//
//        quickSort(list, left, mid - 1);
//
//        quickSort(list, mid + 1, right);
//
//    }
//    
//}
//void nakashima::t2cl::mergeSort(std::vector<int>& list, const int left, const int right)
//{
//    
//    /*配列の要素が一つならリターン*/
//    if (left >= right){
//        return;
//        }
//    int mid = (left + right)/2;  
//    mergeSort(list, left, mid);
//    mergeSort(list, mid + 1, right);
//    /*左部分を作業領域にコピー*/
//    std::vector<int> temp(list.size());
//    int i, j;
//    for (i = left; i <= mid; i++) {
//        temp[i] = list[i];
//    }
//    /*右部分を作業領域にコピー*/
//    for (i = mid + 1, j = right; i <= right; i++, j--) {
//        temp[i] = list[j];
//    }
//    i = left;
//    j = right;
//
//    for (int k = left; k <= right; k++) {
//        if (temp[i] <= temp[j]) {
//            list[k] = temp[i++];
//        }
//        else {
//            list[k] = temp[j--];
//        }
//       
//    } 
//    for (int i = 0; i < list.size(); i++) {
//            std::cout << list[i] << "\t";
//        }
//        std::cout << std::endl;
//}
//
//
//
//void nakashima::t2cl::comparisonOfSortingMethods(const std::string& filepath)
//{
//    std::string outputFilepath=filepath;
//    // std::string outputFilepath = "%userprofile%/documents/output.txt"; // こちらのパスに変えてみよう
//    std::ofstream ofs(outputFilepath);
//    ofs << "実行する配列list：" <<"\n";
//    for (int i = 0; i < list.size(); i++) {
//        ofs << list[i] << "\t";
//    }
//    ofs << "\n";
//    std::vector<int> bubble(list.size());
//    std::vector<int> quick(list.size());
//    std::vector<int> merge(list.size());
//    for (int i = 0; i < list.size(); i++) {
//        bubble[i] = list[i];
//        quick[i] = list[i];
//        merge[i] = list[i];
//    }
//    using clock = std::chrono::steady_clock;
//    using time_resolution = std::chrono::microseconds;
//    clock::time_point begin = clock::now();
//    clock::time_point end = clock::now();
//    time_resolution elapsed_time = std::chrono::duration_cast<time_resolution>(end - begin);
//    int Bubbletime, Quicktime, Mergetime;
//    for (int i = 0; i < 3; i++) {
//        if (i == 0) {
//            begin = clock::now();
//            std::cout << "Bubblesortを実行します" << std::endl;
//            ofs << "Bubblesortを実行します" << std::endl;
//            nakashima::t2cl::bubbleSort(bubble);
//            end = clock::now();
//            elapsed_time = std::chrono::duration_cast<time_resolution>(end - begin);
//            ofs << elapsed_time.count() << "microseconds" << std::endl;
//            Bubbletime = elapsed_time.count();
//        }
//        else if (i == 1) {
//
//            begin = clock::now();
//            std::cout << "Quicksortを実行します" << std::endl;
//            ofs << "Quicksortを実行します" << std::endl;
//            nakashima::t2cl::quickSort(quick, 0, quick.size()-1);
//            end = clock::now();
//            elapsed_time = std::chrono::duration_cast<time_resolution>(end - begin);
//            ofs << elapsed_time.count() << "microseconds" << std::endl;
//            Quicktime = elapsed_time.count();
//        }
//        else if (i == 2) {
//            begin = clock::now();
//            std:: cout<<"Mergesortを実行します" << std::endl;
//            ofs << "Mergesortを実行します" << std::endl;
//            nakashima::t2cl::mergeSort(merge, 0, merge.size()-1);
//            end = clock::now();
//            elapsed_time = std::chrono::duration_cast<time_resolution>(end - begin);
//            ofs << elapsed_time.count() << "microseconds" << std::endl;
//            Mergetime = elapsed_time.count();
//        }
//    }
//   
//      if (Bubbletime < Quicktime) {
//         if (Mergetime < Bubbletime) {
//             std::cout << "計測時間はQuicksort>Bubblesort>Mergesort" << std::endl;
//             ofs << "計測時間はQuicksort>Bubblesort>Mergesort";
//         }
//         else if (Mergetime > Quicktime) {
//             std::cout << "計測時間はMergesort>Quicksort>Bubblesort" << std::endl;
//             ofs << "計測時間はQuicksort>Bubblesort>Mergesort";
//         }
//         else {
//             std::cout << "計測時間はQuicksort>Mergesort>Bubblesort" << std::endl;
//             ofs << "計測時間はQuicksort>Mergesort>Bubblesort";
//         }
//     }
//     else {
//          if (Mergetime < Quicktime) {
//              std::cout << "計測時間はBubblesort>Quicksort>Mergesort" << std::endl;
//              ofs << "計測時間はBubblesort>Quicksort>Mergesort";
//          }
//          else if (Mergetime > Bubbletime) {
//             std::cout << "計測時間はMergesort>Bubblesort>Quicksort" << std::endl;
//             ofs << "計測時間はMergesort>Bubblesort>Quicksort";
//         }
//         else {
//             std::cout << "計測時間はBubblesort>Mergesort>Quicksort" << std::endl;
//             ofs << "計測時間はBubblesort>Mergesort>Quicksort";
//         }
//     }
//       
//}
//  
//    
//
// 
// 
//
//void nakashima::t2cl::run(int num)
//{
//    switch (num) {
//    default:
//    case 1:
//        std::cout << "run calcTheDistanceBetween" << std::endl;
//        std::cout << t2cl::calcTheDistanceBetween(1, 1, 5, 4) << std::endl;
//        if (num != 0) break;
//    case 2:
//        std::cout << "run calcSphereVolume" << std::endl;
//        std::cout << t2cl::calcSphereVolume(10) << std::endl;
//        if (num != 0) break;
//    case 3:
//        std::cout << "run calcSphereSurfaceArea" << std::endl;
//        std::cout << t2cl::calcSphereSurfaceArea(10) << std::endl;
//        if (num != 0) break;
//    case 4:
//        std::cout << "run comparisonOfSortingMethods" << std::endl;
//        t2cl::comparisonOfSortingMethods("output.txt");
//        if (num != 0) break;
//        
//    }
//}
//
//
//
