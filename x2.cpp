#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <windows.h> // 添加这行以使用SetConsoleOutputCP

using namespace std;

// 转换为小写比较（不区分大小写）
bool equalsIgnoreCase(const wstring& a, const wstring& b) {
    if (a.length() != b.length()) return false;
    
    for (size_t i = 0; i < a.length(); ++i) {
        if (towlower(a[i]) != towlower(b[i])) {
            return false;
        }
    }
    
    return true;
}

// 从文件加载单词集
map<wstring, wstring> loadWordSet(const string& filename) {
    map<wstring, wstring> wordSet;
    wifstream inFile(filename);
    
    if (!inFile) {
        wcerr << L"错误：无法打开文件 '" << filename << L"'" << endl;
        wcerr << L"请确保文件存在且路径正确。" << endl;
        exit(1); // 文件加载失败直接退出程序
    }
    
    wstring line;
    while (getline(inFile, line)) {
        size_t delimiterPos = line.find(L'|');
        if (delimiterPos != wstring::npos) {
            wstring english = line.substr(0, delimiterPos);
            wstring chinese = line.substr(delimiterPos + 1);
            wordSet[english] = chinese;
        }
    }
    
    if (wordSet.empty()) {
        wcerr << L"错误：文件 '" << filename << L"' 中没有有效的单词数据" << endl;
        wcerr << L"请确保文件格式为：英文单词|中文意思" << endl;
        exit(1);
    }
    
    wcout << L"成功加载 " << wordSet.size() << L" 个单词" << endl;
    return wordSet;
}

// 单词拼写练习
void wordSpellingPractice(map<wstring, wstring>& wordSet) {
    // 设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<wstring> words;
    for (const auto& pair : wordSet) {
        words.push_back(pair.first);
    }
    
    srand(static_cast<unsigned int>(time(nullptr)));
    random_shuffle(words.begin(), words.end());
    
    const int totalWords = static_cast<int>(words.size());
    
    wcout << L"\n开始单词拼写练习！输入'q'可随时退出。" << endl;
    wcout << L"共有 " << totalWords << L" 个单词需要拼写。" << endl << endl;
    
    while (!words.empty()) {
        wstring currentWord = words.back();
        wstring chineseMeaning = wordSet[currentWord];
        
        wcout << L"中文意思: " << chineseMeaning << endl;
        wcout << L"请拼写对应的英文单词: ";
        wstring userInput;
        getline(wcin, userInput);
        
        if (userInput == L"q") {
            wcout << L"\n练习结束。" << endl;
            return;
        }
        
        if (equalsIgnoreCase(userInput, currentWord)) {
            wcout << L"正确！" << endl << endl;
            words.pop_back();
        } else {
            wcout << L"不正确。正确的拼写是: " << currentWord << endl << endl;
            if (words.size() > 1) {
                int randomPos = rand() % (words.size() - 1);
                swap(words[randomPos], words.back());
            }
        }
    }
    
    wcout << L"\n恭喜！你已正确拼写所有 " << totalWords << L" 个单词！" << endl;
}

int main() {
    // 设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    wcout << L"单词拼写练习程序" << endl;
    wcout << wstring(30, L'=') << endl;
    wcout << L"注意：请准备一个文本文件，格式为：英文单词|中文意思" << endl;
    wcout << L"示例文件内容：" << endl;
    wcout << L"apple|苹果" << endl;
    wcout << L"banana|香蕉" << endl << endl;
    
    wstring filename;
    wcout << L"请输入单词集文件路径（如 wordset.txt）: ";
    getline(wcin, filename);
    
    // 加载单词集
    map<wstring, wstring> wordSet = loadWordSet(wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(filename));
    
    // 开始练习
    wordSpellingPractice(wordSet);
    
    // 等待用户输入，防止调试界面立即关闭
    wcout << L"按回车键退出程序..." << endl;
    wcin.get();
    
    return 0;
}

