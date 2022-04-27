#include "the1stCppLecture_nakashima.hpp"

// �ۑ�1
void nakashima::t1cl::helloWorld()
{
    std::cout << "Hello, World!\n";//1,std::������,2,""������,3,:��;�ɕύX
}

// �ۑ�2
void nakashima::t1cl::typeExample()
{
    std::cout << "��������͂��Ă�������" << std::endl;//std::������
    int num;
    std::cin >> num;//<<��>>�ɕύX
    if (num > 0)
    {
        std::cout << "num�͐��̐��ł�\n";
    }
    else if (num == 0)//1,=��==�ɕύX 2,if��else if�ɕύX
    {
        std::cout << "num��0�ł�\n";
    }
    else
    {
        std::cout << "num�͕��̐��ł�\n";
    }
}

// �ۑ�3
void nakashima::t1cl::ifExample()
{
    std::cout << "��ڂ̐�������͂��Ă�������" << std::endl;
    int max;
    std::cin >> max;
    std::cout << "��ڂ̐�������͂��Ă�������" << std::endl;
    int min;
    std::cin >> min;
    if (max < min)
    {
        int temp = min;//temp��ǉ�
        min = max;
        max = temp;
    }
    std::cout << "max:" << max << "\tmin:" << min << std::endl;//"��ǉ�
}

// �ۑ�4
void nakashima::t1cl::forExample()
{
    for (int i=0; i < 10; ++i)//1,,��;�ɕύX,2,;���폜 3,i=0
    {
        std::cout << i << std::endl;
    }
}

// �ۑ�5
void nakashima::t1cl::vectorExample()
{
    std::vector<int> ary(10);//<int>�����
    for (std::size_t i = 0; i < ary.size(); ++i) {//std::size_t��ǉ����Aint���폜
        ary[i] = i;
    }
    for (std::size_t i = 0; i < ary.size(); ++i) {//60�s�ڂƓ�����
        std::cout << ary[i] <<std::endl;//()��[]�ɕύX
    }
}
// �ۑ�6
void nakashima::t1cl::swap(std::vector<int> &num)//&��ǉ�
{
    int temp = num[1];
    num[1] = num[0];
    num[0] = temp;
}
void nakashima::t1cl::funcExample()
{
    std::vector<int> num(2);

    std::cout << "��ڂ̐�������͂��Ă�������" << std::endl;
    std::cin >> num[0];

    std::cout << "��ڂ̐�������͂��Ă�������" << std::endl;
    std::cin >> num[1];
    if (num[0] < num[1]) {
    swap(num);//[]���폜
}
    std::cout << "max:" << num[0] << "\tmin:" << num[1] << std::endl;
}

// �ۑ�7
void nakashima::t1cl::foutPathExample()
{//{��ǉ�����
    std::string outputFilepath = "output";//''��""�ɕύX
    std::ofstream ofs(outputFilepath);
    for (int i = 0; i < 10; ++i)//1,==��=�ɕύX 2,;���폜
    {
        ofs << i << "\n";
     }
}

// void name::t1cl::run(int num = 0); //�w�b�_�ł͂��̂悤�ɐ錾���邱��
// run�֐��͉ۑ�Ώۂł͂Ȃ��ł�
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
}  //}������