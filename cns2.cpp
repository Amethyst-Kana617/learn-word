#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    // 设置随机数种子以确保每次运行程序时句子不同
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 古诗短句列表
    std::vector<std::string> gushi = {
        "人生若只如初见。",
        "明月几时有。",
        "海内存知己，天涯若比邻。",
        "落花人独立，微雨燕双飞。",
        "白日依山尽，黄河入海流。"
    };

    // 随机选择一个句子
    int index = std::rand() % gushi.size();
    std::string selectedSentence = gushi[index];

    // 提示用户背诵
    std::cout << "请背诵以下古诗短句：" << selectedSentence << std::endl;

    // 获取用户输入
    std::string userInput;
    std::cout << "请输入你记住的句子：" << std::endl;
    std::getline(std::cin, userInput);

    // 使用if语句对比用户输入和正确的句子
    if (userInput == selectedSentence) {
        std::cout << "恭喜你，背诵正确！" << std::endl;
    } else {
        std::cout << "很遗憾，你背诵的句子不正确。正确的句子是：" << selectedSentence << std::endl;
    }

    return 0;
}
