#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <locale>
#include <codecvt>

using namespace std;

// 从文件加载单词集
map<string, string> loadWordSet(const string& filename) {
    map<string, string> wordSet; // 声明一个映射来存储单词及其对应的中文意思
    ifstream inFile(filename);      // 打开文件，准备进行读取

    if (!inFile) { // 如果文件无法打开
        cerr << "错误：无法打开文件 '" << filename << "'" << endl; // 输出错误信息
        cerr << "请确保文件存在且路径正确。" << endl; // 提示用户检查文件路径
        exit(1); // 文件加载失败直接退出程序
    }

    string line; // 声明一个字符串来存储文件的每一行
    while (getline(inFile, line)) { // 逐行读取文件内容
        size_t delimiterPos = line.find(' '); // 查找'|'字符的位置
        if (delimiterPos != string::npos) { // 如果找到了'|'字符
            string english = line.substr(0, delimiterPos); // 提取'|'字符前的部分作为单词
            string chinese = line.substr(delimiterPos + 1); // 提取'|'字符后的部分作为中文
            wordSet[english] = chinese; // 将单词及其意思存储到映射中
        }
    }

    inFile.close(); // 关闭文件

    return wordSet; // 返回加载的单词集
}

int main() {
    string filename; // 声明一个字符串变量来存储文件路径
    cout << "请输入单词集文件路径（如 wordset.txt）: "; // 提示用户输入文件路径
    getline(cin, filename); // 获取用户输入的文件路径

    // 加载单词集文件
    map<string, string> wordSet = loadWordSet(filename);

    int correctCount = 0; // 正确的单词数量计数器
    int remainingWords = wordSet.size(); // 剩余单词数量计数器

    // 开始单词拼写练习
    for (const auto& entry : wordSet) {
        cout << "剩余单词数量: " << remainingWords << endl; // 显示剩余单词数量
        cout << "中文意思: " << entry.second << endl; // 显示中文意思
        string userAnswer;
        cout << "请输入对应的单词: "; // 提示用户输入单词
        getline(cin, userAnswer); // 获取用户输入

        // 检查用户输入是否正确
        if (userAnswer == entry.first) {
            cout << "正确！" << endl;
            cout << "-----------------------" << endl;
            correctCount++; // 正确答案计数器加1
        } else {
            cout << "错误！正确的单词是: " << entry.first << endl;
            cout << "-----------------------" << endl;
        }
        remainingWords--; // 剩余单词数量计数器减1
    }

    cout << "所有单词已经循环完一遍。" << endl;
    cout << "你总共答对了 " << correctCount << " 个单词。" << endl;

    return 0; // 返回0，表示程序成功结束
}
