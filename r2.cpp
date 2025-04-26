#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

int main() {
    std::string inputFilePath;
    std::cout << "请输入输入文件的路径: ";
    std::cin >> inputFilePath; // 从终端获取输入文件路径

    std::ifstream inputFile(inputFilePath); // 使用用户指定的输入文件路径
    if (!inputFile.is_open()) {
        std::cerr << "无法打开输入文件: " << inputFilePath << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    // 使用当前时间作为随机数生成器的种子
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(lines.begin(), lines.end(), rng);

    std::string outputFilePath;
    std::cout << "请输入输出文件的路径: ";
    std::cin >> outputFilePath; // 从终端获取输出文件路径

    std::ofstream outputFile(outputFilePath); // 使用用户指定的输出文件路径
    if (!outputFile.is_open()) {
        std::cerr << "无法打开输出文件: " << outputFilePath << std::endl;
        return 1;
    }

    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }
    outputFile.close();

    std::cout << "行顺序已打乱，并保存到 " << outputFilePath << " 文件中" << std::endl;
    std::cout << "操作已完成" << std::endl; // 添加完成消息

    return 0;
}
