#!/bin/bash

# 删除旧的
rm -rf build/*

# 编译静态库
g++ -c ./myMath/add.cpp -o ./build/add.o
ar rcs ./build/libmymath.a ./build/add.o

# 编译可执行文件 链接静态库
g++ tests/myMath/addTest.cpp \
    -o ./build/testRun \
    -I ./myMath \
    -L ./build \
    -l gtest -l gtest_main -l mymath

# 执行可执行文件
./build/testRun