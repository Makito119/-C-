#include "the1stCppLecture_nakashima.hpp"

// 課題1
void nakashima::t1cl::helloWorld()
{
    std::cout << "Hello, World!\n";//1,std::を入れる,2,""を入れる,3,:を;に変更
}

// 課題2
void nakashima::t1cl::typeExample()
{
    std::cout << "整数を入力してください" << std::endl;//std::を入れる
    int num;
    std::cin >> num;//<<を>>に変更
    if (num > 0)
    {
        std::cout << "numは正の数です\n";
    }
    else if (num == 0)//1,=を==に変更 2,ifをelse ifに変更
    {
        std::cout << "numは0です\n";
    }
    else
    {
        std::cout << "numは負の数です\n";
    }
}

// 課題3
void nakashima::t1cl::ifExample()
{
    std::cout << "一つ目の整数を入力してください" << std::endl;
    int max;
    std::cin >> max;
    std::cout << "二つ目の整数を入力してください" << std::endl;
    int min;
    std::cin >> min;
    if (max < min)
    {
        int temp = min;//tempを追加
        min = max;
        max = temp;
    }
    std::cout << "max:" << max << "\tmin:" << min << std::endl;//"を追加
}

// 課題4
void nakashima::t1cl::forExample()
{
    for (int i=0; i < 10; ++i)//1,,を;に変更,2,;を削除 3,i=0
    {
        std::cout << i << std::endl;
    }
}

// 課題5
void nakashima::t1cl::vectorExample()
{
    std::vector<int> ary(10);//<int>を入力
    for (std::size_t i = 0; i < ary.size(); ++i) {//std::size_tを追加し、intを削除
        ary[i] = i;
    }
    for (std::size_t i = 0; i < ary.size(); ++i) {//60行目と同じく
        std::cout << ary[i] <<std::endl;//()を[]に変更
    }
}
// 課題6
void nakashima::t1cl::swap(std::vector<int> &num)//&を追加
{
    int temp = num[1];
    num[1] = num[0];
    num[0] = temp;
}
void nakashima::t1cl::funcExample()
{
    std::vector<int> num(2);

    std::cout << "一つ目の整数を入力してください" << std::endl;
    std::cin >> num[0];

    std::cout << "二つ目の整数を入力してください" << std::endl;
    std::cin >> num[1];
    if (num[0] < num[1]) {
    swap(num);//[]を削除
}
    std::cout << "max:" << num[0] << "\tmin:" << num[1] << std::endl;
}

// 課題7
void nakashima::t1cl::foutPathExample()
{//{を追加する
    std::string outputFilepath = "output";//''を""に変更
    std::ofstream ofs(outputFilepath);
    for (int i = 0; i < 10; ++i)//1,==を=に変更 2,;を削除
    {
        ofs << i << "\n";
     }
}

// void name::t1cl::run(int num = 0); //ヘッダではこのように宣言すること
// run関数は課題対象ではないです
void nakashima::t1cl::run(int num)
{
    switch (num) {
    default:
    case 1:
        std::cout << "run helloWorld" << std::endl;
        t1cl::helloWorld();
        if (num != 0) break;
    case 2:
        std::cout << "run typeTest" << std::endl;
        t1cl::typeExample();
        if (num != 0) break;
    case 3:
        std::cout << "run ifTest" << std::endl;
        t1cl::ifExample();
        if (num != 0) break;
    case 4:
        std::cout << "run forTest" << std::endl;
        t1cl::forExample();
        if (num != 0) break;
    case 5:
        std::cout << "run vectorTest" << std::endl;
        t1cl::vectorExample();
        if (num != 0) break;
    case 6:
        std::cout << "run funcTest" << std::endl;
        t1cl::funcExample();
        if (num != 0) break;
    case 7:
        std::cout << "run foutPathTest" << std::endl;
        t1cl::foutPathExample();
    }
}  //}を入れる
