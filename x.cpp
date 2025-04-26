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

using namespace std;

// 转换为小写比较（不区分大小写）
bool equalsIgnoreCase(const string& a, const string& b) {
    if (a.length() != b.length()) return false;
    
    for (size_t i = 0; i < a.length(); ++i) {
        if (tolower(a[i]) != tolower(b[i])) {
            return false;
        }
    }
    
    return true;
}

// 从文件加载单词集
map<string, string> loadWordSet(const string& filename) {
    map<string, string> wordSet;
    ifstream inFile(filename);
    
    if (!inFile) {
        cerr << "错误：无法打开文件 '" << filename << "'" << endl;
        cerr << "请确保文件存在且路径正确。" << endl;
        exit(1); // 文件加载失败直接退出程序
    }
    
    string line;
    while (getline(inFile, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            string english = line.substr(0, delimiterPos);
            string chinese = line.substr(delimiterPos + 1);
            wordSet[english] = chinese;
        }
    }
    
    if (wordSet.empty()) {
        cerr << "错误：文件 '" << filename << "' 中没有有效的单词数据" << endl;
        cerr << "请确保文件格式为：英文单词|中文意思" << endl;
        exit(1);
    }
    
    cout << "成功加载 " << wordSet.size() << " 个单词" << endl;
    return wordSet;
}

// 单词拼写练习
void wordSpellingPractice(map<string, string>& wordSet) {
    vector<string> words;
    for (const auto& pair : wordSet) {
        words.push_back(pair.first);
    }

    random_shuffle(words.begin(), words.end());

    cout << "\n开始单词拼写练习！输入'q'可随时退出。" << endl;
    cout << "共有 " << words.size() << " 个单词需要拼写。" << endl << endl;

    while (!words.empty()) {
        string currentWord = words.back();
        string chineseMeaning = wordSet[currentWord];

        cout << "中文意思: " << chineseMeaning << endl;
        cout << "请拼写对应的英文单词: ";
        string userInput;
        getline(cin, userInput);

        if (userInput == "q") {
            cout << "\n练习结束。" << endl;
            return;
        }

        if (equalsIgnoreCase(userInput, currentWord)) {
            cout << "正确！" << endl << endl;
            words.pop_back();
        } else {
            cout << "不正确。正确的拼写是: " << currentWord << endl;
            if (words.size() > 1) {
                // 将错误的单词放在随机位置，但不是末尾
                int randomPos = rand() % (words.size() - 1);
                swap(words[randomPos], words.back());
            }
            // 提示剩余单词数量
            cout << "剩余 " << words.size() << " 个单词需要拼写。" << endl << endl;
        }
    }

    cout << "\n恭喜！你已正确拼写所有单词！" << endl;
}

int main() {
    cout << "单词拼写练习程序" << endl;
    cout << string(30, '=') << endl;
    cout << "注意：请准备一个文本文件，格式为：英文单词|中文意思" << endl;
    cout << "示例文件内容：" << endl;
    cout << "apple|苹果" << endl;
    cout << "banana|香蕉" << endl << endl;
    
    string filename;
    cout << "请输入单词集文件路径（如 wordset.txt）: ";
    getline(cin, filename);
    
    // 加载单词集
    map<string, string> wordSet = loadWordSet(filename);
    
    // 开始练习
    wordSpellingPractice(wordSet);
    
    return 0;
}