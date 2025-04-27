#include <iostream>
#include <string.h>
#include <vector>
#include <windows.h> // 添加头文件
#include <wctype.h>

// 函数将std::string转换为UTF-8编码的字节向量并打印
void printUTF8Code(const std::string& input) {
    std::cout << "输入字符串的UTF-8编码:" << std::endl;
    for (char c : input) {
        unsigned char uc = static_cast<unsigned char>(c);
        printf("%02X ", uc);
    }
    std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8

    // 设置输入字符串
    std::string input;
    std::cout << "请输入一个汉字字符串: ";
    std::getline(std::cin, input);

    // 打印输入字符串的长度
    std::cout << "输入字符串长度: " << input.length() << " 字节" << std::endl;

    // 打印UTF-8编码
    printUTF8Code(input);

    // 添加输入等待，以便查看输出结果
    std::cout << "按任意键继续..." << std::endl;
    std::cin.get();

    return 0;
}
