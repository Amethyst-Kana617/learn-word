#include <iostream>    // 包含输入输出流库，用于控制台输入输出
#include <vector>      // 包含向量库，用于存储动态数组
#include <algorithm>   // 包含算法库，用于使用标准算法
#include <string>      // 包含字符串库，用于处理字符串
#include <ctime>       // 包含时间库，用于生成随机数种子
#include <cstdlib>     // 包含标准库中的通用函数，如rand和srand
#include <map>         // 包含映射库，用于存储键值对
#include <cctype>      // 包含字符处理库，用于字符转换函数
#include <fstream>     // 包含文件流库，用于文件读写
#include <sstream>     // 包含字符串流库，用于字符串和流之间的转换
#include <windows.h>  // 包含Windows API库，用于设置控制台编码
#include <chrono>      // 包含时间库，用于获取更高精度的时间戳
#include <random>      // 包含随机数库，用于生成随机数种子
#include <locale>      // 包含locale库，用于设置locale
#include <codecvt>     // 包含codecvt库，用于字符编码转换（C++14 及更早版本）

using namespace std;   // 使用标准命名空间，简化代码

// 从文件加载单词集
map<wstring, wstring> loadWordSet(const string& filename) {
    map<wstring, wstring> wordSet; // 声明一个映射来存储单词及其对应的中文意思
    ifstream inFile(filename);      // 打开文件，准备进行读取

    if (!inFile) { // 如果文件无法打开
        wcerr << L"错误：无法打开文件 '" << filename << L"'" << endl; // 输出错误信息
        wcerr << L"请确保文件存在且路径正确。" << endl; // 提示用户检查文件路径
        exit(1); // 文件加载失败直接退出程序
    }

    string line; // 声明一个字符串来存储文件的每一行
    while (getline(inFile, line)) { // 逐行读取文件内容
        size_t delimiterPos = line.find('|'); // 查找'|'字符的位置
        if (delimiterPos != string::npos) { // 如果找到了'|'字符
            string english = line.substr(0, delimiterPos); // 提取'|'字符前的部分作为英文单词
            string chinese = line.substr(delimiterPos + 1); // 提取'|'字符后的部分作为中文意思
            
            // 使用 wstring_convert 进行窄字符串到宽字符串的转换
            wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
            wstring wide_english = converter.from_bytes(english);
            wstring wide_chinese = converter.from_bytes(chinese);
            
            wordSet[wide_english] = wide_chinese; // 将英文单词和中文意思存储到映射中
        }
    }

    if (wordSet.empty()) { // 如果映射中没有有效的单词数据
        wcerr << L"错误：文件 '" << filename << L"' 中没有有效的单词数据" << endl; // 输出错误信息
        wcerr << L"请确保文件格式为：英文单词|中文意思" << endl; // 提示用户检查文件格式
        exit(1); // 文件加载失败直接退出程序
    }

    wcout << L"成功加载 " << wordSet.size() << L" 个单词" << endl; // 输出成功加载的单词数量
    return wordSet; // 返回加载的单词集
}

// 单词拼写练习
void wordSpellingPractice(map<wstring, wstring>& wordSet) {
    // 设置控制台输出编码为UTF-8，以便正确显示中文字符
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<wstring> words; // 声明一个向量来存储单词列表
    for (const auto& pair : wordSet) { // 遍历映射中的每一个键值对
        words.push_back(pair.first); // 将英文单词存储到向量中
    }

    // 使用更高精度的时间戳和 random_device 生成随机数种子
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    default_random_engine rng(seed);

    // 使用 std::shuffle 打乱单词向量中的顺序
    shuffle(words.begin(), words.end(), rng);

    const int totalWords = static_cast<int>(words.size()); // 获取单词总数，并存储为整数

    wcout << L"\n开始单词拼写练习！输入'q'可随时退出。" << endl; // 输出练习开始信息
    wcout << L"共有 " << totalWords << L" 个单词需要拼写。" << endl << endl; // 输出总共需要拼写的单词数量

    while (!words.empty()) { // 当单词向量不为空时，继续练习
        wstring currentWord = words.back(); // 获取向量中最后一个单词
        wstring chineseMeaning = wordSet[currentWord]; // 获取该单词的中文意思

        wcout << L"中文意思: " << chineseMeaning << endl; // 输出中文意思
        wcout << L"请拼写对应的英文单词: "; // 提示用户输入英文单词
        wstring userInput; // 声明一个宽字符串来存储用户输入
        getline(wcin, userInput); // 获取用户输入的英文单词

        if (userInput == L"q") { // 如果用户输入的是'q'
            wcout << L"\n练习结束。" << endl; // 输出练习结束信息
            return; // 结束函数，返回主函数
        }

        if (userInput == currentWord) { // 如果用户输入的单词与当前单词匹配（区分大小写）
            wcout << L"正确！" << endl << endl; // 输出正确信息
            words.pop_back(); // 从向量中移除当前单词
        } else { // 如果用户输入的单词不匹配
            wcout << L"不正确。正确的拼写是: " << currentWord << endl << endl; // 输出不正确信息及正确拼写
            if (words.size() > 1) { // 如果向量中还有其他单词
                uniform_int_distribution<int> dist(0, words.size() - 2);
                int randomPos = dist(rng); // 生成一个随机位置
                swap(words[randomPos], words.back()); // 将随机位置的单词与当前单词交换位置
            }
        }
    }

    wcout << L"\n恭喜！你已正确拼写所有 " << totalWords << L" 个单词！" << endl; // 输出恭喜信息，表示所有单词拼写正确
}

int main() {
    // 设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    wcout << L"单词拼写练习程序" << endl; // 输出程序标题
    wcout << wstring(30, L'=') << endl; // 输出分隔线，用于美化输出
    wcout << L"注意：请准备一个文本文件，格式为：英文单词|中文意思" << endl; // 提示用户准备一个格式正确的文件
    wcout << L"示例文件内容：" << endl; // 输出文件内容示例的提示
    wcout << L"apple|アップル" << endl; // 输出示例英文单词及其对应的中文意思
    wcout << L"banana|バナナ" << endl << endl; // 输出另一个示例英文单词及其对应的中文意思

    wstring filename; // 声明一个宽字符串变量来存储文件路径
    wcout << L"请输入单词集文件路径（如 wordset.txt）: "; // 提示用户输入文件路径
    getline(wcin, filename); // 获取用户输入的文件路径

    // 加载单词集文件，将文件路径转换为窄字符串
    map<wstring, wstring> wordSet = loadWordSet(wstring_convert<codecvt_utf8_utf16<wchar_t>>().to_bytes(filename));

    // 开始单词拼写练习
    wordSpellingPractice(wordSet);

    // 等待用户输入，防止调试界面立即关闭
    wcout << L"按回车键退出程序..." << endl;
    wcin.get(); // 等待用户按下回车键

    return 0; // 返回0，表示程序成功结束
}
