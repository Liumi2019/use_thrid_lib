#ifndef DEBUG_INCLUDE_H
#define DEBUG_INCLUDE_H

#include <iostream>
#include <string>

template <typename T>
void printMessage(std::string TAG, T message) {
    std::cout << TAG << ": "<< message << std::endl;
}

#endif