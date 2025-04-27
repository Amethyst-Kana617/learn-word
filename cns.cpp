#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <locale>

using namespace std;

// 从文件加载古诗短句集
map<string, string> loadPoetrySet(const string& filename) {
    map<string, string> poetrySet; // 声明一个映射来存储古诗短句及其对应的答案
    ifstream inFile(filename);        // 打开文件，准备进行读取

    if (!inFile) { // 如果文件无法打开
        cerr << "错误：无法打开文件 '" << filename << "'" << endl; // 输出错误信息
        cerr << "请确保文件存在且路径正确。" << endl; // 提示用户检查文件路径
        exit(1); // 文件加载失败直接退出程序
    }

    string line; // 声明一个字符串来存储文件的每一行
    while (getline(inFile, line)) { // 逐行读取文件内容
        size_t delimiterPos = line.find(' '); // 查找' '字符的位置
        if (delimiterPos != string::npos) { // 如果找到了' '字符
            string poetry = line.substr(0, delimiterPos); // 提取' '字符前的部分作为古诗短句
            string answer = line.substr(delimiterPos + 1); // 提取' '字符后的部分作为答案
            poetrySet[poetry] = answer; // 将古诗短句及其答案存储到映射中
        }
    }

    inFile.close(); // 关闭文件

    return poetrySet; // 返回加载的古诗短句集
}

int main() {
    string filename; // 声明一个字符串变量来存储文件路径
    cout << "请输入古诗短句文件路径（如 poetry.txt）: "; // 提示用户输入文件路径
    getline(cin, filename); // 获取用户输入的文件路径

    // 加载古诗短句文件
    map<string, string> poetrySet = loadPoetrySet(filename);

    int correctCount = 0; // 正确的答案数量计数器
    int remainingPoetries = poetrySet.size(); // 剩余古诗短句数量计数器

    // 开始古诗短句练习
    for (const auto& entry : poetrySet) {
        cout << "剩余古诗短句数量: " << remainingPoetries << endl; // 显示剩余古诗短句数量
        cout << "古诗短句: " << entry.first << endl; // 显示古诗短句
        string userAnswer;
        cout << "请输入对应的答案: "; // 提示用户输入答案
        getline(cin, userAnswer); // 获取用户输入

        // 检查用户输入是否正确
        if (userAnswer == entry.second) {
            cout << "正确！" << endl;
            cout << "-----------------------" << endl;
            correctCount++; // 正确答案计数器加1
        } else {
            cout << "错误！正确的答案是: " << entry.second << endl;
            cout << "-----------------------" << endl;
        }
        remainingPoetries--; // 剩余古诗短句数量计数器减1
    }

    cout << "所有古诗短句已经循环完一遍。" << endl;
    cout << "你总共答对了 " << correctCount << " 个古诗短句。" << endl;

    return 0; // 返回0，表示程序成功结束
}
