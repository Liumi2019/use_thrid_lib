#ifndef TEST_CODE_H
#define TEST_CODE_H

#include <iostream>

// 定义一个纯虚基类，删除赋值构造函数
class MyBase {
public:
    MyBase() {;}
    MyBase(const MyBase& mybase) = delete;
    MyBase& operator=(const MyBase& mybase) = delete;
    virtual ~MyBase() {;};
};

class MyDerive : public MyBase {
public:
    MyDerive() {;}
    static void printMassage() {
        std::cout << "hello" << std::endl;
    }
    ~MyDerive() {;}
};

void test_MyBase();

#endif