import random

def shuffle_lines(input_file, output_file):
    # 打开输入文件并读取所有行
    with open(input_file, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    # 随机排列行
    random.shuffle(lines)
    
    # 将排列后的行写入输出文件
    with open(output_file, 'w', encoding='utf-8') as file:
        file.writelines(lines)

# 使用方法
input_file_path = 'C:\Users\11421\Desktop\learn-word\learn-word\input.txt'  # 替换为你的输入文件路径
output_file_path = 'C:\Users\11421\Desktop\learn-word\learn-word\output.txt'  # 替换为你的输出文件路径
shuffle_lines(input_file_path, output_file_path)
