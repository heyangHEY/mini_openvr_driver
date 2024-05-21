#!/bin/bash

# 默认构建类型为 Debug，除非通过命令行参数指定为 Release
BUILD_TYPE=Debug

# 检查命令行参数
if [ "$1" == "Release" ]; then
    BUILD_TYPE=Release
fi

# 删除旧的构建目录
rm -rf ./build/

# 配置项目
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=./install -DBUILD_TYPE=$BUILD_TYPE

# 构建项目
cmake --build build --config $BUILD_TYPE

# 安装项目
cmake --install build --config $BUILD_TYPE

# # 如何使用该脚本
# chmod +x build_project.sh
# ./build_project.sh Release