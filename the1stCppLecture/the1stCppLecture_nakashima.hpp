#pragma once
#include<iostream>
#include<vector>
#include<fstream>

namespace nakashima {     // 安川くんの場合 namespace yasukawa
    namespace t1cl {     // tanlab the 1nd cpp lecture
        void helloWorld();
        void typeExample();
        void ifExample();
        void forExample();
        void vectorExample();
        void funcExample();
        void swap(std::vector<int> &num);
        void foutPathExample();
        void run(int num = 0); //run関数のみ，ヘッダではこのように宣言すること
    }
}
