#!/bin/bash

# 获取当前文件的目录
current_file="$1"
output_file="${current_file%.*}"

# 查找所有子模块的 include 文件夹
include_dirs=$(find . -type d -name "include" | sed 's/^/-I/')

# 生成编译命令
echo "g++ -g "$current_file" -o "$output_file" $include_dirs"
